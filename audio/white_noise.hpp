#pragma once

#include <al.h>
#include <alc.h>

#include "sound_object.hpp"

#include <array>
#include <cmath>
#include <random>

#define SAMPLINGRATE 44100
#define _USE_MATH_DEFINES

namespace Audio
{

class WhiteNoise : public SoundObject<SAMPLINGRATE>
{
public:
    WhiteNoise()
        : SoundObject(
              []() {
                  std::random_device seed_gen;
                  std::default_random_engine engine(seed_gen());
                  std::normal_distribution<> dist(0.0, 1.0);

                  std::array<unsigned short, SAMPLINGRATE / 100> wav_data;
                  for (int i = 0; i < SAMPLINGRATE / 100; i++) {
                      wav_data[i] = 32767 * dist(engine);
                  }
                  return wav_data;
              }())
    {
    }

    ~WhiteNoise() = default;
};


}  // namespace Audio
