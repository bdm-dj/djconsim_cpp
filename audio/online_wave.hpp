#pragma once

#include "sound_object.hpp"

#include <al.h>
#include <alc.h>

#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

#define SAMPLINGRATE 44100
#define _USE_MATH_DEFINES

namespace Audio
{

template <unsigned int sampling_rate>
class OnlineWavePlayer
{
private:
    Audio::SoundObject<sampling_rate> sound_object;
    volatile bool sound_ready;

public:
    OnlineWavePlayer() : sound_ready(false)
    {
        std::thread play_thread{[this]() {
            volatile bool infinite_loop = true;
            while (infinite_loop) {
                while (!sound_ready) {
                }
                sound_object.play();
                auto start = std::chrono::system_clock::now();  // 計測開始時間
                while (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start).count() < 100000) {
                }
                sound_ready = false;
            }
        }};
        play_thread.detach();
    }

    ~OnlineWavePlayer()
    {
        while (sound_ready) {
        }
    }

    void playWave(const std::array<unsigned short, sampling_rate / 100> wav_data)
    {
        while (sound_ready) {
        }
        sound_object.setWave(wav_data);
        sound_ready = true;
    }
};


}  // namespace Audio
