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
//      https://w.atwiki.jp/opengl/pages/174.html
//      https://www.youfit.co.jp/archives/1418
class WaveFile
{

private:
    // meta data in wave files
    unsigned short channel_quantity;
    unsigned short block_size;
    unsigned short bit_per_sample;
    unsigned int bps;
    unsigned int sampling_rate;

    std::ifstream fp;
    uint32_t wav_data_size;
    std::ifstream::pos_type wav_data_head;
    std::size_t loaded_size;


    struct ChunkOfFmt {
        unsigned format : 16;
        unsigned channel_quantity : 16;
        unsigned sampling_freq : 32;
        unsigned bps : 32;
        unsigned block_size : 16;
        unsigned bit_per_sample : 16;
    } chunk_fmt;


public:
    void open(std::string path);

    template <int size>
    std::array<unsigned short, size> read()
    {
        std::cout << "read() size: " << size << std::endl;
        std::array<unsigned short, size> out;

        fp.read(reinterpret_cast<char*>(out.data()), size * sizeof(unsigned short) / sizeof(char));
        loaded_size += size;
        if (loaded_size == wav_data_size) {
            loaded_size = 0;
            fp.seekg(wav_data_head);
        }
        return out;
    }

    bool is_end() const
    {
        return (0 == wav_data_size) || (wav_data_size == loaded_size);
    }

    WaveFile() = default;

    WaveFile(const std::string& path)
    {
        open(path);
    }

    ~WaveFile()
    {
        fp.close();
    }
};

}  // namespace Audio
