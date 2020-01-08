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
    std::ifstream fp;
    uint32_t wav_data_size;
    std::ifstream::pos_type wav_data_head;
    std::size_t loaded_size;

    struct ChunkOfFmt {
        unsigned format : 16;
        unsigned channel_quantity : 16;
        unsigned sampling_rate : 32;
        unsigned byte_rate : 32;
        unsigned block_size : 16;
        unsigned bit_per_sample : 16;
    } chunk_fmt;


public:
    void open(std::string path);

    std::vector<unsigned short> read(int size);
    std::vector<unsigned short> read_all();

    bool is_end() const
    {
        return (0 == wav_data_size) || (wav_data_size == loaded_size);
    }

    int getSampleRate() { return chunk_fmt.sampling_rate; }
    int getChannelQuantity() { return chunk_fmt.sampling_rate; }
    int getWaveFormat()
    {
        if (chunk_fmt.bit_per_sample == 8) {
            if (chunk_fmt.channel_quantity == 1) {
                return AL_FORMAT_MONO8;
            } else {
                return AL_FORMAT_STEREO8;
            }
        } else if (chunk_fmt.bit_per_sample == 16) {
            if (chunk_fmt.channel_quantity == 1) {
                return AL_FORMAT_MONO16;
            } else {
                return AL_FORMAT_STEREO16;
            }
        }
        return 0x0000;
    }


    WaveFile() = default;
    WaveFile(const std::string& path) { open(path); }
    ~WaveFile() { fp.close(); }
};

}  // namespace Audio
