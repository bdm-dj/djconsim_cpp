#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "audio.hpp"
#include "online_wave.hpp"
#include "reduction.hpp"
#include "sinwave.hpp"
#include "wav.hpp"
#include "white_noise.hpp"

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>

void wait(double time_sec)
{
    auto start = std::chrono::system_clock::now();  // 計測開始時間

    while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() / 1000.0 < time_sec) {
    }
}

int main()
{
    Audio::init();

    //Audio::SoundObject fuga(700);
    //fuga.play();

#if 0
    {
        for (int i = 440; i < 1000; i += 30) {
            std::cout << i << std::endl;
            Audio::SinWave hoge(i);
            hoge.play();
            system("sleep 2");
        }
    }
#endif

#if 0
    {
        Audio::WhiteNoise hoge;

        hoge.play();
        system("sleep 2");
    }
#endif

#if 0
    {
        for (int i = 440; i < 1000; i += 30) {
            std::cout << i << std::endl;
            Audio::ReductionSinWave hoge(i, 0.08);
            hoge.play();
            wait(3.0);
        }
    }
#endif

#if 1
    {
        Audio::OnlineWavePlayer<44100> player;
        //std::array<unsigned short, 441> wav_data;
        Audio::WaveFile file("loop.wav");


        auto pulse_cut = [](double x) { return x > 0.95 ? 1.0 : 0.0; };

        for (int n = 0; n < 1000; n++) {
            /*for (int i = 0; i < 441; i++) {
                wav_data[i] = 32767 * pulse_cut(sin(2 * M_PI * i * (440 + 30 * (n + i / 44100.0)) / 44100.0));
            }*/
            auto hoge = file.read<441>();

            for (auto&& v : hoge) {
                std::cout << v << '|';
            }
            std::cout << std::endl;

            player.playWave(hoge);
        }
    }
#endif

    return 0;
}

#pragma GCC diagnostic pop
