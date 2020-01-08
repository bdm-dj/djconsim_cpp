#pragma once

#include <al.h>
#include <alc.h>

#include <cmath>
#include <iostream>
#include <vector>

#define _USE_MATH_DEFINES

namespace Audio
{

class SoundObject
{
protected:
    ALuint buffer;
    ALuint source;
    int sampling_rate;

public:
    SoundObject(
        int sampling_rate,
        const std::vector<unsigned short>& wav_data)
        : sampling_rate(sampling_rate)
    {
        alGenBuffers(1, &buffer);
        alGenSources(1, &source);

        //バッファに音源データを入れる
        alBufferData(buffer, AL_FORMAT_MONO16, wav_data.data(), sampling_rate, sampling_rate);
    }

    SoundObject(
        int sampling_rate,
        const unsigned short* wav_data)
        : sampling_rate(sampling_rate)
    {
        alGenBuffers(1, &buffer);
        alGenSources(1, &source);

        //バッファに音源データを入れる
        alBufferData(buffer, AL_FORMAT_MONO16, wav_data, sampling_rate, sampling_rate);
    }

    SoundObject(int sampling_rate)
        : sampling_rate(sampling_rate)
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

    void setWave(const std::vector<unsigned short>& wav_data)
    {
        //alDeleteBuffers(1, &buffer);
        //alDeleteSources(1, &source);
        alGenBuffers(1, &buffer);
        alGenSources(1, &source);

        std::cout << wav_data.size() << std::endl;
        alBufferData(buffer, AL_FORMAT_MONO16, wav_data.data(), sampling_rate, sampling_rate);
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

    virtual void changePitch(float ratio)
    {
        alSourcef(source, AL_PITCH, ratio);
    }
};


}  // namespace Audio
