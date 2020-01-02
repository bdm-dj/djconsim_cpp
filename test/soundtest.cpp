#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "audio.hpp"
#include "online_wave.hpp"
#include "wav.hpp"

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>


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
            for (int t = 0; t < 1000; t += 10) {
                hoge.play();
            }
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


#if 0
    {
        Audio::OnlineWavePlayer<44100> player;
        std::array<unsigned short, 44100> wav_data;

        for (int n = 0; n < 1000;) {
            for (int i = 0; i < 44100; i++, n++) {
                wav_data[i] = 20000 * sin(2 * M_PI * 440 * n / 44100.0);
            }
            player.playWave(wav_data);
        }
    }
#endif


#if 1
    {
        Audio::OnlineWavePlayer<44100 * 2> player;
        //std::array<unsigned short, 441> wav_data;
        Audio::WaveFile file("hpanda.wav");

        auto pulse_cut = [](double x) { return x > 0.95 ? 1.0 : 0.0; };

        for (int n = 0; n < 30; n++) {
            /*for (int i = 0; i < 441; i++) {
                wav_data[i] = 32767 * pulse_cut(sin(2 * M_PI * i * (440 + 30 * (n + i / 44100.0)) / 44100.0));
            }*/
            auto hoge = file.read<44100 * 2>();

            player.playWave(hoge);
        }
    }
#endif

    return 0;
}

#pragma GCC diagnostic pop
