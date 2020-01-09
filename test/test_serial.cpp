#include "usb.hpp"

#include <iostream>


#pragma pack(push, 1)

struct DataSet {
    bool flag1 : 1;
    bool flag2 : 1;
    bool flag3 : 1;
    bool flag4 : 1;
    bool flag5 : 1;
    signed : 3;
    signed num1 : 16;
    unsigned num2 : 16;
};

#pragma pack(pop)


int main(int argc, char* argv[])
{
    DJCon::USBSerial usb{"/dev/cu.usbmodem14101"};


    bool initial_frame_started = false;
    bool initial_frame_done = false;
    int initial_frame_count = 0;

    std::cout << "loop start" << std::endl;
    usb.send('i');

    while (true) {
    outer_begin:
        usb.poll();

        if (!initial_frame_done) {
            auto buf = usb.read<uint8_t>();
            std::cout << buf.value() << std::endl;
            if (buf) {
                switch (buf.value()) {
                case 't':
                    ++initial_frame_count;
                    std::cout << "initial_frame_count = " << initial_frame_count << std::endl;
                    break;
                case 'f':
                    ++initial_frame_count;
                    std::cout << "initial_frame_count = " << initial_frame_count << std::endl;
                    if (initial_frame_count == 36) {
                        initial_frame_done = true;
                    }
                    break;
                default:
                    initial_frame_count = 0;
                }
            }
            usb.send('i');
            continue;
        }

        std::cout << "fuga" << std::endl;

        auto buf = usb.read<DataSet>();
        if (buf) {
            char* data = reinterpret_cast<char*>(&buf.value());
            std::cout << data[0] << ','
                      << data[1] << ','
                      << data[2] << ','
                      << data[3] << ','
                      << data[4] << std::endl;
            /*
            DataSet& data = buf.value();
            std::cout << std::dec
                      << data.flag1 << ' ' << data.flag2 << ' ' << data.flag3 << ' ' << data.flag4 << ' ' << data.flag5 << ' '
                      << data.num1 << ' ' << data.num2
                      << std::endl;
                      */
        }
    }

    return 0;
}
