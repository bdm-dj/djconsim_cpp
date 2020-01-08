#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "audio.hpp"
#include "wav.hpp"

#include <al.h>
#include <alc.h>

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#define _USE_MATH_DEFINES


namespace Audio
{

class Manager
{
    ALCdevice* device;
    ALCcontext* context;

    std::vector<ALuint> buffers;

public:
    Manager()
    {
        // Open OpenAL Device (NULL to get default)
        device = alcOpenDevice(NULL);
        if (device) {
            context = alcCreateContext(device, NULL);
            alcMakeContextCurrent(context);
        } else {
            throw std::runtime_error{"OpenAL Device cannot be opened."};
        }
    }

    ~Manager()
    {
        alDeleteBuffers(buffers.size(), buffers.data());

        context = alcGetCurrentContext();
        device = alcGetContextsDevice(context);
        alcMakeContextCurrent(NULL);
        alcDestroyContext(context);
        alcCloseDevice(device);
    }

    ALuint loadWAV(std::string path)
    {
        WaveFile file{path};
        std::vector<ALushort> wav_data = file.read_all();
        ALuint id;
        alGenBuffers(1, &id);
        alBufferData(id, file.getWaveFormat(),
            wav_data.data(), wav_data.size(), 44100);
        buffers.push_back(id);

        return id;
    }
};

// use pointer to control when it's initialized
std::unique_ptr<Manager> manager_ptr;

void init()
{
    manager_ptr = std::make_unique<Manager>();
}

ALuint loadWAV(std::string path)
{
    return manager_ptr->loadWAV(path);
}


}  // namespace Audio


#pragma GCC diagnostic pop
