#pragma once

#include <al.h>
#include <alc.h>

#include <string>

namespace Audio
{

class AudioException
{
private:
    const char* msg;  // 例外を説明するメッセージ
public:
    AudioException(const char* msg) : msg(msg) {}  // コンストラクタ
    const char* what() const { return msg; }       // メッセージを返す
};

void init();
ALuint loadWAV(std::string path);

}  // namespace Audio
