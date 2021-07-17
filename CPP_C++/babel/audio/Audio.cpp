/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** audio
*/

#include "Audio.hpp"

using namespace Babel;

Audio::Output::Output()
: volume(1), stream(nullptr), inputDecoder(nullptr) {}
Audio::Output::Output(PaStream *_steam, size_t sampleRate, size_t framesPerBuffer)
: volume(1), stream(_steam)
, inputDecoder(new OpusCodec<int32_t>(sampleRate, framesPerBuffer, OpusCodec<int32_t>::DecodeOnly))
{
}

static int _inputCallback(const void *input, void *, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    static_cast<Audio*>(userData)->inputCallback(input, size_t(frameCount));
    return paContinue;
}

static int _outputCallback(const void *, void *output, unsigned long frameCount, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    static_cast<Audio::Output*>(userData)->fillStream((int32_t*)output, size_t(frameCount));
    return paContinue;
}

Audio::Audio(size_t sampleRate, size_t framesPerBuffer)
: _sampleRate(sampleRate), _framesPerBuffer(uint32_t(framesPerBuffer))
{
    int error = Pa_Initialize();
    if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));
    _outputDeviceIndex = Pa_GetDefaultOutputDevice();
    inputEncoder = std::unique_ptr<OpusCodec<int32_t>>(new OpusCodec<int32_t>(sampleRate, framesPerBuffer, OpusCodec<int32_t>::OpusState::EncodeOnly));

    error = Pa_OpenDefaultStream(&inputStream, 1, 0, paInt32, double(_sampleRate), _framesPerBuffer, &_inputCallback, this);
    if (error != paNoError) {
        Pa_Terminate();
        throw std::runtime_error(Pa_GetErrorText(error));
    }
    error = Pa_StartStream(inputStream);
    if (error != paNoError) {
        Pa_StopStream(inputStream);
        Pa_Terminate();
        throw std::runtime_error(Pa_GetErrorText(error));
    }
}

Audio::~Audio()
{
    Pa_StopStream(inputStream);
    for (auto &p : outputs)
        Pa_StopStream(p.second.stream);

    Pa_Terminate();
}

void Audio::sendAudioCallback(const std::function<void(const std::vector<uint8_t> &)> &audioReceiver)
{
    audioSender = audioReceiver;
}

void Audio::receiveAudio(const std::vector<uint8_t> &audio, const std::string &id)
{
    if (_deafen && id != "")
        return;
    if (!outputs.count(id)) {
        outputs[id]; outputs[id] = Output(openNewOutputStream(id), _sampleRate, _framesPerBuffer);
    }

    std::vector<int32_t> vOutput = outputs.at(id).inputDecoder->decodeData(audio);
    for (size_t i = 0; i != vOutput.size(); ++i)
        vOutput[i] = int32_t(vOutput[i] * (outputVolume / 100.) * outputs.at(id).volume);

    auto &audioList = outputs.at(id).pendingAudio;
    outputs.at(id)._mutex.lock();
    if (audioList.size() > _sampleRate / 2 && audioList.size() > vOutput.size())
        audioList.erase(audioList.begin(), audioList.begin() + vOutput.size());
    audioList.insert(audioList.end(), vOutput.begin(), vOutput.end());
    outputs.at(id)._mutex.unlock();
}

void Audio::inputCallback(const void *input, size_t frameCount)
{
    if ((!audioSender && !selfRecord) || _mute)
        return;

    std::vector<int32_t> vInput(frameCount);
    for (size_t i = 0; i != frameCount; ++i)
        vInput[i] = int32_t(((int32_t*)input)[i] * (inputVolume / 100.));
    auto encoded = inputEncoder->encodeData(vInput);

    if (audioSender) audioSender(encoded);
    if (selfRecord) receiveAudio(encoded, "");
}

void Audio::Output::fillStream(int32_t *output, size_t frameCount)
{
    _mutex.lock();
    for (size_t i = 0; i != frameCount; ++i)
        output[i] = i < pendingAudio.size()? pendingAudio[i]: 0;
    pendingAudio.erase(pendingAudio.begin(), frameCount < pendingAudio.size()? pendingAudio.begin()+frameCount: pendingAudio.end());
    _mutex.unlock();
}

PaStream *Audio::openNewOutputStream(const std::string &id)
{
    PaStream *stream;
    PaStreamParameters param = {_outputDeviceIndex, 1, paInt32, Pa_GetDeviceInfo(_outputDeviceIndex)->defaultLowOutputLatency, nullptr};

    int error = Pa_OpenStream(&stream, nullptr, &param, double(_sampleRate), _framesPerBuffer, paNoFlag, &_outputCallback, &outputs.at(id));
    if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));
    error = Pa_StartStream(stream);
    if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));

    return stream;
}

void Audio::setInputDevice(const std::string &inputDevice)
{
    std::cout << Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->name << ", " << inputDevice << std::endl;
    int defaultHostApi = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->hostApi;
    for (int i = 0; i < Pa_GetHostApiInfo(defaultHostApi)->deviceCount; ++i) {
        PaDeviceIndex dIdx = Pa_HostApiDeviceIndexToDeviceIndex(defaultHostApi, i);
        if (Pa_GetDeviceInfo(dIdx)->maxInputChannels > 0 && inputDevice == Pa_GetDeviceInfo(dIdx)->name) {
            PaStream *stream;
            PaStreamParameters param = {dIdx, 1, paInt32, Pa_GetDeviceInfo(dIdx)->defaultLowInputLatency, nullptr};
            int error = Pa_OpenStream(&stream, &param, nullptr, double(_sampleRate), _framesPerBuffer, paNoFlag, &_inputCallback, this);
            if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));
            error = Pa_StartStream(stream);
            if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));
            
            error = Pa_StopStream(inputStream);
            if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));
            inputStream = stream;
            return;
        }
    }
    throw std::invalid_argument("Audio::setInputDevice: Unknow input device \"" + inputDevice + "\"");
}

void Audio::setOutputDevice(const std::string &outputDevice)
{
    int defaultHostApi = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->hostApi;
    for (int i = 0; i < Pa_GetHostApiInfo(defaultHostApi)->deviceCount; ++i) {
        PaDeviceIndex dIdx = Pa_HostApiDeviceIndexToDeviceIndex(defaultHostApi, i);
        if (Pa_GetDeviceInfo(dIdx)->maxOutputChannels > 0 && outputDevice == Pa_GetDeviceInfo(dIdx)->name) {
            _outputDeviceIndex = dIdx;
            int error = Pa_StopStream(outputs[""].stream);
            if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));
            outputs[""].stream = openNewOutputStream("");
            return;
        }
    }
    throw std::invalid_argument("Audio::setOutputDevice: Unknow output device \"" + outputDevice + "\"");
}

std::list<std::string> Audio::getInputDevices() const
{
    std::list<std::string> names;
    int defaultHostApi = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice())->hostApi;

    for (int i = 0; i < Pa_GetHostApiInfo(defaultHostApi)->deviceCount; ++i) {
        const PaDeviceInfo *dInfo = Pa_GetDeviceInfo(Pa_HostApiDeviceIndexToDeviceIndex(defaultHostApi, i));
        if (dInfo->maxInputChannels > 0)
            names.push_back(Pa_GetDeviceInfo(i)->name);
    }
    return names;
}

std::list<std::string> Audio::getOutputDevices() const
{
    std::list<std::string> names;
    int defaultHostApi = Pa_GetDeviceInfo(Pa_GetDefaultOutputDevice())->hostApi;

    for (int i = 0; i < Pa_GetHostApiInfo(defaultHostApi)->deviceCount; ++i) {
        const PaDeviceInfo *dInfo = Pa_GetDeviceInfo(Pa_HostApiDeviceIndexToDeviceIndex(defaultHostApi, i));
        if (dInfo->maxOutputChannels > 0)
            names.push_back(Pa_GetDeviceInfo(i)->name);
    }
    return names;
}

float Audio::getInputVolume() const { return inputVolume / 100.f; }
float Audio::getOutputVolume() const { return outputVolume / 100.f; }
float Audio::getOutputVolume(const std::string &ip) const { if (!outputs.count(ip)) throw std::invalid_argument("Unknow identifier \""+ip+"\""); return outputs.at(ip).volume; };
void Audio::setInputVolume(float volume)
{
    if (volume > 2.f || volume < 0) throw std::invalid_argument("Audio::setInputVolume accept only value between 0f and 2f.");
    inputVolume = int(volume * 100);
}
void Audio::setOutputVolume(float volume)
{
    if (volume > 2.f || volume < 0) throw std::invalid_argument("Audio::setOutputVolume accept only value between 0f and 2f.");
    outputVolume = int(volume * 100);
}
void Audio::setOutputVolume(const std::string &ip, float volume)
{
    if (volume > 2.f || volume < 0) throw std::invalid_argument("Audio::setOutputVolume accept only value between 0f and 2f.");
    if (!outputs.count(ip)) throw std::invalid_argument("Audio::setOutputVolume: Unknow identifier \"" + ip + "\"");
    outputs.at(ip).volume = volume;
}
