/*
** EPITECH PROJECT, 2020
** B-CPP-500-NCY-5-1-babel-valentin.l-homel
** File description:
** OpusCodec
*/

#pragma once

#include <opus.h>
#include <stdexcept>
#include <type_traits>
#include <algorithm>

#include "IAudioCodec.hpp"

namespace Babel {
    template<typename T>
    class OpusCodec : public IAudioCodec<T> {
        public: enum OpusState {
            EncodeDecode,
            EncodeOnly,
            DecodeOnly
        };

        public:
            OpusCodec(size_t sampleRate=48000, size_t framePerBuffer=480, OpusState codecType=EncodeDecode)
            : maxValueOfT(0), frameCount(framePerBuffer), encoder{nullptr}, decoder{nullptr}
            {
                static_assert(std::is_arithmetic<T>::value, "Need an arithmetic type in order to create an OpusCodec.");
                if (!std::is_floating_point<T>::value) {
                    size_t v = 0;
                    for (size_t i = 0; i < sizeof(T); ++i)
                        v = v << 010 | 0xFF;
                    maxValueOfT = static_cast<long double>(v);
                } else
                    maxValueOfT = 1;

                int error = OPUS_OK;

                if (codecType != DecodeOnly) {
                    encoder = opus_encoder_create(int32_t(sampleRate), 1, OPUS_APPLICATION_VOIP, &error);
                }
                if (error != OPUS_OK)
                    throw std::runtime_error(opus_strerror(error));
                else if (encoder)
                    opus_encoder_ctl(encoder, OPUS_SET_BITRATE(sampleRate));
                if (codecType != EncodeOnly)
                    decoder = opus_decoder_create(int32_t(sampleRate), 1, &error);
                if (error != OPUS_OK) {
                    opus_encoder_destroy(encoder);
                    throw std::runtime_error(opus_strerror(error));
                }
            }
            ~OpusCodec() { opus_encoder_destroy(encoder); opus_decoder_destroy(decoder); }

            std::vector<uint8_t> encodeData(const std::vector<T> &data)
            {
                if (!encoder)
                    throw std::logic_error("OpusCodec::encodeData call with a decode only codec.");

                size_t size = data.size();
                std::vector<float> tmp(size);
                for (size_t i = 0; i != size; ++i)
                    tmp[i] = static_cast<float>(data[i] / maxValueOfT);
                
                std::vector<uint8_t> encoded(frameCount);
                int ret = opus_encode_float(encoder, tmp.data(), int(size), &encoded.front(), int32_t(frameCount));
                if (ret < 0)
                    throw std::logic_error(opus_strerror(ret));
                encoded.resize(ret);
                return encoded;
            }
            std::vector<T> decodeData(const std::vector<uint8_t> &data) {
                if (!decoder)
                    throw std::logic_error("OpusCodec::decodeData call with an encode only codec.");

                std::vector<float> tmp(frameCount);
                int ret = opus_decode_float(decoder, data.size() == 0? nullptr: data.data(), int32_t(data.size()), &tmp.front(), int(frameCount), 0);
                if (ret < 0)
                    throw std::logic_error(opus_strerror(ret));

                std::vector<T> decoded(ret);
                for (size_t i = 0; i != ret; ++i)
                    decoded[i] = static_cast<T>(std::max(std::min(tmp[i], 1.f), -1.f) * maxValueOfT);
                return decoded;
            }

        private:
            size_t frameCount;
            long double maxValueOfT;

            OpusEncoder *encoder;
            OpusDecoder *decoder;
    };
};