#pragma once

#include "audio.hpp"

namespace Audio
{

class Source
{
    ALuint id;

public:
    Source()
    {
        alGenSources(1, &id);
        alSourcef(id, AL_GAIN, 1.0f);
        alSourcef(id, AL_PITCH, 1.0f);
    }

    Source(const ALuint buffer)
    {
        alGenSources(1, &id);
        alSourcef(id, AL_GAIN, 1.0f);
        alSourcef(id, AL_PITCH, 1.0f);
        alSourcei(id, AL_BUFFER, buffer);
        alSourcei(id, AL_LOOPING, AL_TRUE);
    }
    ~Source()
    {
        alDeleteSources(1, &id);
    }

    void play(ALuint buffer)
    {
        alSourcei(id, AL_BUFFER, buffer);
        alSourcePlay(id);
    }
    void play()
    {
        alSourcePlay(id);
    }

    void setGain(ALfloat gain)
    {
        alSourcef(id, AL_GAIN, gain);
    }

    void setPitch(ALfloat pitch)
    {
        alSourcef(id, AL_PITCH, pitch);
    }
};


}  // namespace Audio
