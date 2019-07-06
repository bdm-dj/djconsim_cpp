#include "audio.hpp"
#include "reduction.hpp"
#include "sinwave.hpp"
#include "white_noise.hpp"

#include <chrono>
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

#if 1
    {
        for (int i = 440; i < 1000; i += 30) {
            std::cout << i << std::endl;
            Audio::ReductionSinWave hoge(i, 0.08);
            hoge.play();
            wait(3.0);
        }
    }
#endif

    return 0;
}
