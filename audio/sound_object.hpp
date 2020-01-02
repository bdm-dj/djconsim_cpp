#pragma once

#include <al.h>
#include <alc.h>

#include <array>
#include <cmath>
#include <iostream>

#define _USE_MATH_DEFINES

namespace Audio
{

template <unsigned int sampling_rate>
class SoundObject
{
protected:
    ALuint buffer;
    ALuint source;

public:
    SoundObject(const std::array<unsigned short, sampling_rate / 100>& wav_data)
    {
        alGenBuffers(1, &buffer);
        alGenSources(1, &source);

        //バッファに音源データを入れる
        alBufferData(buffer, AL_FORMAT_MONO16, wav_data.data(), sampling_rate / 100 * sizeof(signed short), sampling_rate);
    }


    SoundObject()
    {
        alGenBuffers(1, &buffer);
        alGenSources(1, &source);
    }

    ~SoundObject()
    {
        // バッファの破棄
        alDeleteBuffers(1, &buffer);
        // ソースの破棄
        alDeleteSources(1, &source);
    }

    void setWave(const std::array<unsigned short, sampling_rate / 100>& wav_data)
    {
        alDeleteBuffers(1, &buffer);
        alDeleteSources(1, &source);
        alGenBuffers(1, &buffer);
        alGenSources(1, &source);
        alBufferData(buffer, AL_FORMAT_MONO16, wav_data.data(), sampling_rate / 100 * sizeof(signed short), sampling_rate);
    }


    virtual void play() const
    {
        //ソースにバッファを適用
        alSourcei(source, AL_BUFFER, buffer);
        //ループ再生をON
        alSourcei(source, AL_LOOPING, AL_TRUE);
        //ソースを再生！
        alSourcePlay(source);
    }
};


}  // namespace Audio
