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

    // "RIFF" の読み込み
    unsigned int riff;
    fp.read((char*)&riff, 4);

    // データサイズを取得
    // データサイズ = ファイルサイズ - 8 byte
    fp.read((char*)&data_size, 4);
    // WAVEの読み込み
    unsigned int wave;
    fp.read((char*)&wave, 4);

    try {
        // PCM 情報とデータの先頭の取得
        for (int i = 0; i < 2; ++i) {
            unsigned int res, size;
            fp.read((char*)&res, 4);
            fp.read((char*)&size, 4);
            if (0x20746d66u == res) {  //fmt
                // PCM 情報の取得
                unsigned short res16;
                fp.read((char*)&res16, 2);
                if (1 != res16) {  // 非対応フォーマット
                    throw AudioException("Invalid Wav Format");
                }
                // モノラル(1), ステレオ(2)
                fp.read((char*)&channel_quantity, 2);
                if (2 < channel_quantity) {
                    throw AudioException("Invalid Channel Quantity");
                }
                // サンプリングレート
                fp.read((char*)&sampling_rate, 4);
                // 1秒あたりのバイト数(byte/sec)
                fp.read((char*)&bps, 4);
                // ブロックサイズ(byte/sample)
                fp.read((char*)&block_size, 2);
                // サンプルあたりのビット数(bit/sample)
                fp.read((char*)&bit_per_sample, 2);
            } else if (0x61746164u == res) {  //data
                // データの開始位置を保存
                data_head = fp.tellg();
                data_size = size;
                // データを読み飛ばす
                fp.seekg(size, std::ios::cur);
            }
        }
        // データの開始位置までシーク
        fp.seekg(data_head);
        loaded_size = 0;
    } catch (const AudioException& e) {
        std::cout << e.what() << std::endl;
        return;
    }
}


}  // namespace Audio

#pragma GCC diagnostic pop
