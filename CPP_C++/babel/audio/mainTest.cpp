/*#include <portaudio.h>
#include "Audio.hpp"
#include <iostream>

int mainAudio(int argc, char **argv)
{
    //try {
        Babel::Audio a;
        a.startSelfBroadcast();
        //int error = Pa_Initialize();
        //if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));
        //std::cout << Pa_GetDeviceCount() << std::endl;
        //PaStream *stream;
        //error = Pa_OpenDefaultStream(&stream, 0, 1, paInt32, 44100, 480, nullptr, nullptr);
        //if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));
        std::cin.get();
        //error = Pa_CloseStream(stream);
        //if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));
        //error = Pa_Terminate();
        //if (error != paNoError) throw std::runtime_error(Pa_GetErrorText(error));
    //} catch(const std::exception &e) {
    //    std::cerr << e.what() << std::endl;
    //}
    return 0;
}

int main3(int argc, char **argv)
{
    try {
        Babel::Audio output;
        Babel::Audio input1;
        Babel::Audio input2;

        input1.deafen();
        input2.deafen();
        output.mute();

        output.outputs["input2"];
        output.outputs["input2"] = Babel::Audio::Output(output.openNewOutputStream("input2"), output._sampleRate, output._framesPerBuffer);

        input1.sendAudioCallback([&output](const std::vector<uint8_t> &data) { output.receiveAudio(data, "input1"); });
        input2.sendAudioCallback([&output](const std::vector<uint8_t> &data) { output.receiveAudio(data, "input2"); });

        output.outputs["input2"]._mutex.lock();
        output.outputs["input2"].pendingAudio.insert(output.outputs["input2"].pendingAudio.end(), output._sampleRate, 0);
        output.outputs["input2"]._mutex.unlock();

        std::cin.get();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}*/