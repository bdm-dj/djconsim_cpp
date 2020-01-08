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

class OnlineWavePlayer
{
private:
    int sampling_rate;
    Audio::SoundObject sound_object;
    //std::mutex mtx;
    //std::condition_variable cond;
    volatile bool sound_updated;
    volatile bool end;
    std::thread play_thread;

public:
    OnlineWavePlayer(int sampling_rate)
        : sampling_rate(sampling_rate),
          sound_object(sampling_rate),
          sound_updated(false), end(false),
          play_thread{
              [this]() {
                  while (!end) {
                      std::cout << "play_thread is waiting to play" << std::endl;
                      while (!sound_updated) {
                      }
                      //std::unique_lock<std::mutex> lock(mtx);
                      //cond.wait(lock, [this]() { return sound_updated; });
                      std::cout << "play_thread" << std::endl;
                      sound_object.play();
                      sound_updated = false;
                      //cond.notify_one();

                      std::cout << "play_thread sleep" << std::endl;
                      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                      std::cout << "play_thread woke up" << std::endl;
                  }
                  std::cout << "play_thread ended" << std::endl;
              }}
    {
    }

    ~OnlineWavePlayer()
    {
        end = true;
        play_thread.join();
    }

    void playWave(const std::vector<unsigned short>& wav_data)
    {
        std::thread set_thread{
            [this, &wav_data]() {
                //std::unique_lock<std::mutex> lock(mtx);
                //cond.wait(lock, [this]() { return !sound_updated; });
                std::cout << "audio_thread is waiting to set" << std::endl;
                while (sound_updated) {
                }
                std::cout << "audio_thread" << std::endl;
                sound_object.setWave(wav_data);
                std::cout << "set done" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                sound_updated = true;
                //cond.notify_one();
            }};

        if (set_thread.joinable()) {
            set_thread.join();
        }
        std::cout << "playWave done" << std::endl;
    }
};


}  // namespace Audio
