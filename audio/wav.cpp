#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "wav.hpp"
#include "audio.hpp"

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

namespace Audio
{


void WaveFile::open(std::string path)
{
    fp.open(path.c_str(), std::ios::binary);

    auto getChunkSize = [this](const std::string true_id) -> uint32_t {
        std::string id(4, '\0');
        fp.read(id.data(), 4);
        std::cout << "compare(" << id << ", " << true_id << ")" << std::endl;
        if (true_id != id) {
            throw AudioException("Invalid Riff Identifier");
        }

        uint32_t size;
        fp.read((char*)&size, 4);
        return size;
    };

    try {

        {  // Chunk ID: RIFF
            getChunkSize("RIFF");

            std::string format(4, '\0');
            fp.read(format.data(), 4);
            if (format != "WAVE") {
                throw AudioException("Error: Not a WAV file");
            }
        }

        {  // Subchunk ID: fmt
            uint32_t fmt_chunk_size = getChunkSize("fmt ");
            fp.read((char*)&chunk_fmt, sizeof(chunk_fmt));
            std::cout << "format: " << chunk_fmt.format << std::endl;
            std::cout << "channel_quantity: " << chunk_fmt.channel_quantity << std::endl;
            std::cout << "sampling_rate: " << chunk_fmt.sampling_rate << std::endl;
            std::cout << "byte_rate: " << chunk_fmt.byte_rate << std::endl;
            std::cout << "block_size: " << chunk_fmt.block_size << std::endl;
            std::cout << "bit_per_sample: " << chunk_fmt.bit_per_sample << std::endl;


            if (auto size_diff = fmt_chunk_size - sizeof(chunk_fmt); size_diff > 0) {
                // skip extension params
                fp.seekg(size_diff, std::ios::cur);
            }
        }

        {  // Subchunk ID: data
            wav_data_size = getChunkSize("data");
            wav_data_head = fp.tellg();
        }

    } catch (const AudioException& e) {
        std::cout << e.what() << std::endl;
        return;
    }

    // jump to wav_file_head
    fp.seekg(wav_data_head);
    loaded_size = 0;
}

std::vector<unsigned short> WaveFile::read(int size)
{
    std::cout << "read() size: " << size << std::endl;
    std::vector<unsigned short> out(size);

    fp.read(reinterpret_cast<char*>(out.data()), size * sizeof(unsigned short) / sizeof(char));
    loaded_size += size;
    if (loaded_size == wav_data_size) {
        loaded_size = 0;
        fp.seekg(wav_data_head);
    }
    return out;
}

std::vector<unsigned short> WaveFile::read_all()
{
    std::cout << "read_all()" << std::endl;
    std::vector<unsigned short> out(wav_data_size);

    fp.seekg(wav_data_head);
    fp.read(reinterpret_cast<char*>(out.data()), wav_data_size * sizeof(unsigned short) / sizeof(char));

    return out;
}

}  // namespace Audio

#pragma GCC diagnostic pop
