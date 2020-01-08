#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "audio.hpp"
#include "source.hpp"
#include "wav.hpp"

#include <chrono>
#include <cmath>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <thread>

void sigsegv_handler(int sig)
{
    std::cout << "SIGSEGV! lol" << std::endl;
}

int main()
{

#if 1
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
#endif

    Audio::init();


#if 1
    {
        /*
        std::thread bgm_thread{[]() {
            auto buffer = Audio::loadWAV("loop.wav");
            Audio::Source source{buffer};
            source.setGain(100.0f);
            source.play();
        }};
        */

        std::thread test_thread{[]() {
            auto buffer1 = Audio::loadWAV("loop.wav");
            Audio::Source source1{buffer1};
            source1.setGain(100.0f);
            source1.play();

            auto buffer = Audio::loadWAV("coin.wav");
            Audio::Source source{buffer};
            source.setGain(100.0f);
            source.play();
            float pitch = 1.0f;
            while (true) {
                char c = getch();
                switch (c) {
                case ' ':
                    source.play();
                    break;
                case 'u':
                    pitch += 0.1f;
                    source.setPitch(pitch);
                    break;
                case 't':
                    pitch -= 0.1f;
                    source.setPitch(pitch);
                    break;
                }
            }
        }};

        //bgm_thread.join();
        test_thread.join();
    }
#endif

#if 0

    {
        std::thread audio_thread{
            [&]() {
                std::vector<unsigned short> wav_data(44100);
                for (int i = 0; i < 44100; i++) {
                    wav_data.at(i) = 39726 * std::sin(2 * M_PI * 440 * i / 44100.0);
                }
                Audio::SoundObject sin_object{44100, wav_data};
                float pitch = 1.0;


                for (int n = 0; n < 100; n++) {
                    sin_object.changePitch(pitch);
                    sin_object.play();
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    pitch *= 1.1;
                }
            }};
        audio_thread.join();
    }
#endif


#if 0
    {
        Audio::OnlineWavePlayer player(44100);
        std::vector<unsigned short> wav_data(44100);
        for (int i = 0; i < 44100; i++) {
            wav_data.at(i) = 39726 * std::sin(2 * M_PI * 440 * i / 44100.0);
        }

        for (int n = 0; n < 100; n++) {
            std::cout << n << std::endl;
            player.playWave(wav_data);
        }
    }
#endif


#if 0
    {
        Audio::OnlineWavePlayer player(44100 * 2);
        //std::array<unsigned short, 441> wav_data;
        Audio::WaveFile file("hpanda.wav");

        auto pulse_cut = [](double x) { return x > 0.95 ? 1.0 : 0.0; };

        for (int n = 0; n < 30; n++) {
            /*for (int i = 0; i < 441; i++) {
                wav_data[i] = 32767 * pulse_cut(sin(2 * M_PI * i * (440 + 30 * (n + i / 44100.0)) / 44100.0));
            }*/
            std::vector<unsigned short> hoge = file.read(44100 * 2);
            player.playWave(hoge);
        }
    }
#endif


#if 0
    {
        Audio::WaveFile file("loop.wav");
        auto wav_data = file.read_all();
        volatile bool to_set = true;
        std::unique_ptr<Audio::SoundObject> wav_sound_ptr;

        std::thread audio_thread{
            [&]() {
                for (int n = 0; n < 100; n++) {
                    std::cout << "audio_thread: waiting" << std::endl;
                    while (to_set) {
                    }
                    wav_sound_ptr->play();
                    std::cout << "audio_thread: to be continued" << std::endl;
                    to_set = true;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }};

        std::thread set_thread{
            [&]() {
                long int cursor = 0;
                for (int n = 0; n < 100; n++) {
                    std::cout << "set_thread: waiting" << std::endl;
                    while (!to_set) {
                    }
                    wav_sound_ptr = std::make_unique<Audio::SoundObject>(44100, wav_data.data() + cursor);
                    cursor += 44100;
                    std::cout << "set_thread: to be continued" << std::endl;
                    to_set = false;
                }
            }};

        set_thread.join();
        audio_thread.join();
    }
#endif

    return 0;
}

#pragma GCC diagnostic pop
