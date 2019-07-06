#pragma once

#include <al.h>
#include <alc.h>

#include "sound_object.hpp"

#include <array>
#include <cmath>

#define SAMPLINGRATE 44100
#define _USE_MATH_DEFINES

namespace Audio
{

class SinWave : public SoundObject<SAMPLINGRATE>
{
public:
    SinWave(int freq)
        : SoundObject(
              [freq]() {
                  std::array<unsigned short, SAMPLINGRATE> wav_data;
                  for (int i = 0; i < SAMPLINGRATE; i++) {
                      wav_data[i] = 32767 * sin(2 * M_PI * i * freq / SAMPLINGRATE);
                  }
                  return wav_data;
              }())
    {
    }

    ~SinWave() = default;
};


}  // namespace Audio
