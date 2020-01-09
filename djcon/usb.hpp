#pragma once

#include <boost/asio.hpp>

#include <array>
#include <chrono>
#include <cstddef>
#include <deque>
#include <iostream>
#include <thread>

namespace DJCon
{

// Reference: http://tips.hecomi.com/entry/20120728/1343504831
class USBSerial
{
    boost::asio::io_service io;
    boost::asio::serial_port port;

    std::deque<uint8_t> received_data;

public:
    USBSerial(const std::string device_path)
        : io{}, port{io, device_path.c_str()},
          received_data{}
    {
        using namespace boost ::asio;

        port.set_option(serial_port_base::baud_rate(9600));
        port.set_option(serial_port_base::character_size(8));
        port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
        port.set_option(serial_port_base::parity(serial_port_base::parity::none));
        port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));

        std::cout << "sleeping for connection" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "woke up" << std::endl;
    }

    ~USBSerial()
    {
        if (port.is_open()) {
            port.close();
        }
    }

    void poll()
    {
        using namespace boost::asio;

        try {

            std::array<uint8_t, 32> buf;
            std::cout << "wait reading" << std::endl;
            std::size_t length = port.read_some(buffer(buf));
            std::cout << "Packet Read. Length: " << length << std::endl;
            for (std::size_t i = 0; i < length; ++i) {
                received_data.push_back(buf[i]);
            }

        } catch (const std::exception& e) {

            std::cerr << e.what() << std::endl;
            exit(EXIT_FAILURE);

        } catch (...) {

            std::cerr << "Unknown Exception" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    template <class T>
    std::optional<T> read()
    {
        if (received_data.size() < sizeof(T)) {
            return std::nullopt;
        }

        union {
            T data;
            uint8_t bytes[sizeof(T)];
        } serialized_data;

        std::cout << "received_data.size() = " << received_data.size() << std::endl;
        for (uint8_t& byte : serialized_data.bytes) {
            byte = received_data.front();
            received_data.pop_front();
        }
        std::cout << "received_data.size() = " << received_data.size() << std::endl;

        return std::make_optional<T>(serialized_data.data);
    };

    template <class T>
    void send(const T& data)
    {
        try {
            boost::system::error_code ret;
            std::cout << "start writing: " << data << std::endl;
            port.write_some(boost::asio::buffer(reinterpret_cast<const uint8_t*>(&data), sizeof(T)), ret);
            std::cout << "end writing" << std::endl;

            if (ret) {
                std::cerr << "serial_port::write_some() return = " << ret << std::endl;
                return;
            }

        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void discard(int byte_size)
    {
        received_data.erase(received_data.begin(), received_data.begin() + byte_size);
    }
};

/*
void hoge()
{

    // 受信データ
    std::vector<unsigned char> receive_api_frame(1024);

    // API フレーム送りまーす
    try {
        io_service io;
        serial_port port(io, USB_SERIAL_PORT);
        port.set_option(serial_port_base::baud_rate(9600));
        port.set_option(serial_port_base::character_size(8));
        port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
        port.set_option(serial_port_base::parity(serial_port_base::parity::none));
        port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));

        port.write_some(buffer(send_api_frame));

        // 全データ受信するまでグルグル
        size_t total_length = 0;
        std::array<unsigned char, 32> buf;
        while (true) {
            size_t length = port.read_some(buffer(buf));
            for (size_t i = 0; i < length; ++i) {
                receive_api_frame.push_back(buf[i]);
                std::cout << buf[i];
            }
            total_length += length;
            //std::cout << length << " " << total_length << std::endl;

            // 受信データ長チェック
            const int NOT_COUNTED_FRAME_LENGTH = 4;
            int received_length = static_cast<size_t>(receive_api_frame.at(2)) + NOT_COUNTED_FRAME_LENGTH;
            if (receive_api_frame.at(2) != 0xff && total_length == received_length) {
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // 受信結果書き出し
    for (size_t i = 0; i < receive_api_frame.size() - 1; ++i) {
        std::cout << std::hex << static_cast<unsigned int>(receive_api_frame.at(i)) << " ";
    }
    std::cout << std::endl;

    return 0;
}
*/

}  // namespace DJCon
