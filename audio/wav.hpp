#pragma once

#include <al.h>
#include <alc.h>

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>

namespace Audio
{


// Reference:
//  https://w.atwiki.jp/opengl/pages/174.html
//  https://www.youfit.co.jp/archives/1418
class WaveFile
{
public:
    void open(std::string path);

    template <int size>
    std::array<unsigned short, size> read()
    {
        /*
        if (loaded_size + size > data_size) {
            size = data_size - loaded_size;
        }
        */
        std::cout << "read() size: " << size << std::endl;
        std::array<unsigned short, size> out;

        fp.read(reinterpret_cast<char*>(out.data()), size * sizeof(unsigned short) / sizeof(char));
        loaded_size += size;
        if (loaded_size == data_size) {
            loaded_size = 0;
            fp.seekg(data_head);
        }
        return out;
    }

    bool is_end() const
    {
        return (0 == data_size) || (data_size == loaded_size);
    }

    WaveFile() = default;

    WaveFile(const std::string& path)
    {
        open(path);
        std::cout << "loaded_size: " << loaded_size << std::endl;
        std::cout << "data_size: " << data_size << std::endl;
        std::cout << "sampling_rate: " << sampling_rate << std::endl;
    }

    ~WaveFile()
    {
        fp.close();
    }

private:
    // meta data in wave files
    unsigned short channel_quantity;
    unsigned short block_size;
    unsigned short bit_per_sample;
    unsigned int bps;
    unsigned int sampling_rate;

    std::ifstream fp;
    std::ifstream::pos_type data_head;
    std::size_t data_size;
    std::size_t loaded_size;
};

}  // namespace Audio
