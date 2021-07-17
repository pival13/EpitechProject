/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** audio
*/

#pragma once

#include <opus.h>
#include <portaudio.h>
#include <map>
#include <deque>
#include <memory>
#include <iostream>
#include <mutex>
#include "IAudio.hpp"
#include "OpusCodec.hpp"

namespace Babel {
    class Audio : public IAudio {
    public:
        Audio(size_t sampleRate=48000UL, size_t framesPerBuffer=480UL);
        ~Audio();

        inline void startSelfBroadcast() { selfRecord = true; }
        inline void endSelfBroadcast() { selfRecord = false; }

        void receiveAudio(const std::vector<uint8_t> &audio, const std::string &id);
        void sendAudioCallback(const std::function<void(const std::vector<uint8_t> &)> &audioReceiver);

        inline void mute() { _mute = true; };
        inline void unmute() { _mute = false; };
        inline void deafen() { _deafen = true; };
        inline void undeafen() { _deafen = false; };

        void setInputVolume(float volume);
        void setOutputVolume(float volume);
        void setOutputVolume(const std::string &ip, float volume);
        float getInputVolume() const;
        float getOutputVolume() const;
        float getOutputVolume(const std::string &ip) const;

        void setInputDevice(const std::string &inputDevice);
        void setOutputDevice(const std::string &outputDevice);
        std::list<std::string> getInputDevices() const;
        std::list<std::string> getOutputDevices() const;

    private:
        PaStream *openNewOutputStream(const std::string &id);

    public:
        void inputCallback(const void *input, size_t frameCount);

    public: struct Output {
            Output();
            Output(PaStream *stream, size_t sampleRate, size_t framesPerBuffer);
            ~Output() = default;
            inline Output &operator=(Output &&lhs) { volume = lhs.volume; stream = lhs.stream; inputDecoder = std::move(lhs.inputDecoder); return *this; }
            void fillStream(int32_t *output, size_t frameCount);

            float volume;
            PaStream *stream;
            std::deque<int32_t> pendingAudio;
            std::mutex _mutex;
            std::unique_ptr<IAudioCodec<int32_t>> inputDecoder;
        };

    private:
        const size_t _sampleRate;
        const unsigned long _framesPerBuffer;

        bool selfRecord = false;
        bool _mute = false;
        bool _deafen = false;
        int inputVolume = 100;
        int outputVolume = 100;
        PaDeviceIndex _outputDeviceIndex;

        std::unique_ptr<IAudioCodec<int32_t>> inputEncoder;
        PaStream *inputStream;
        std::map<std::string, Output> outputs;

        std::function<void(const std::vector<uint8_t> &)> audioSender;
    };
};