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

class ReductionSinWave : public SoundObject<SAMPLINGRATE>
{
public:
    ReductionSinWave(int freq, double tau)
        : SoundObject(
              [freq, tau]() {
                  std::array<unsigned short, SAMPLINGRATE> wav_data;
                  for (int i = 0; i < SAMPLINGRATE; i++) {
                      wav_data[i] = 32767 * std::exp(-(double)i / SAMPLINGRATE / tau)
                                    * (1.0 - std::exp(-(double)i / SAMPLINGRATE / 0.04))
                                    * (0.1 * std::sin(2 * M_PI * 3 * freq * i / SAMPLINGRATE)
                                          + std::sin(2 * M_PI * freq * i / SAMPLINGRATE));
                  }

                  std::array<unsigned short, SAMPLINGRATE> filtered_wav_data;
                  constexpr int filter_reach = 3;
                  for (int i = 0; i < filter_reach; i++) {
                      filtered_wav_data[i] = filtered_wav_data[SAMPLINGRATE - i - 1] = wav_data[i];
                  }
                  for (int i = filter_reach; i < SAMPLINGRATE - filter_reach; i++) {
                      filtered_wav_data[i] = (0.2 - std::exp(-(double)i / SAMPLINGRATE / tau)) * 0.5 * (wav_data[i + filter_reach] - wav_data[i - filter_reach]) + (0.8 + std::exp(-(double)i / SAMPLINGRATE / tau)) * wav_data[i];
                  }

                  return filtered_wav_data;
              }())
    {
    }

    ~ReductionSinWave() = default;
};


}  // namespace Audio
