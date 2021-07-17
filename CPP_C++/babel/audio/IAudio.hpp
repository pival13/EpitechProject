/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** IAudio
*/

#pragma once

#include <list>
#include <string>
#include <vector>
#include <functional>

class IAudio {
    public:
        virtual ~IAudio() = default;

        ///@brief Begin sending sound receive by your input device into your output device.
        virtual void startSelfBroadcast() = 0;
        ///@brief End sending sound receive by your input device into your output device.
        virtual void endSelfBroadcast() = 0;

        ///@brief Receive and play sound.
        ///@details Receive a sound as a vector of bytes from a particular emitter. Stacks all sounds and play them as sound as possible. 
        ///@param audio A vector of bytes representing a sound.
        ///@param id The unique identifier of the emitter of the soudn.
        virtual void receiveAudio(const std::vector<uint8_t> &audio, const std::string &id) = 0;
        ///@brief Set the function to be called when inputs data are available
        ///@details The callback will be called each time sounds are perceive by the input device.
        ///@param audioReceiver Callback function, accepting a vector of bytes (sounds) as parameters.
        virtual void sendAudioCallback(const std::function<void(const std::vector<uint8_t> &)> &audioReceiver) = 0;

        ///@brief Stop emitting inputs.
        virtual void mute() = 0;
        ///@brief Resume emitting inputs.
        virtual void unmute() = 0;
        ///@brief Stop playing outputs.
        virtual void deafen() = 0;
        ///@brief Resume playing outputs.
        virtual void undeafen() = 0;

        ///@brief Set the input volume. Accept value between 0-2.
        virtual void setInputVolume(float volume) = 0;
        ///@brief Set the global output volume. Accept value between 0-2.
        virtual void setOutputVolume(float volume) = 0;
        ///@brief Set the output volume of a specific emitter. Accept value between 0-2.
        virtual void setOutputVolume(const std::string &id, float volume) = 0;
        ///@brief Get the input volume.
        virtual float getInputVolume() const = 0;
        ///@brief Get the global output volume.
        virtual float getOutputVolume() const = 0;
        ///@brief Get the output volume of a specific emitter.
        virtual float getOutputVolume(const std::string &id) const = 0;

        ///@brief Set the device use as input.
        virtual void setInputDevice(const std::string &inputDevice) = 0;
        ///@brief Set the device use as output.
        virtual void setOutputDevice(const std::string &inputDevice) = 0;
        ///@brief Get a list of input devices available. 
        virtual std::list<std::string> getInputDevices() const = 0;
        ///@brief Get a list of output devices available. 
        virtual std::list<std::string> getOutputDevices() const = 0;
};
