#include "audio.hpp"

#include <al.h>
#include <alc.h>

#include <cmath>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

#define SAMPLINGRATE 44100
//ここでπを宣言
#define _USE_MATH_DEFINES


namespace Audio
{

class Manager
{
    ALCdevice* device;
    ALCcontext* context;

public:
    Manager()
    {
        //OpenALの下準備　おまじない的な
        device = alcOpenDevice(NULL);
        context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(context);
    }

    ~Manager()
    {
        //OpenALの後始末
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context);
        alcCloseDevice(device);
    }
};

std::shared_ptr<Manager> manager_ptr;

void init()
{
    manager_ptr = std::make_shared<Manager>();
}


}  // namespace Audio
