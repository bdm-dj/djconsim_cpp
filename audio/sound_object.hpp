#pragma once

#include <al.h>
#include <alc.h>

#include <array>
#include <cmath>

#define SAMPLINGRATE 44100
#define _USE_MATH_DEFINES

namespace Audio
{

void init();

template <unsigned int sampling_rate>
class SoundObject
{
protected:
    ALuint buffer;
    ALuint source;

public:
    SoundObject(std::array<unsigned short, sampling_rate> wav_data)
    {
        alGenBuffers(1, &buffer);
        alGenSources(1, &source);

        //バッファに音源データを入れる
        alBufferData(buffer, AL_FORMAT_MONO16, wav_data.data(), sampling_rate * sizeof(signed short), sampling_rate);
    }

    ~SoundObject()
    {
        // バッファの破棄
        alDeleteBuffers(1, &buffer);
        // ソースの破棄
        alDeleteSources(1, &source);
    }

    virtual void play()
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
