#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <thread>

auto main() -> int
{
    boost::asio::io_service io;

    // ポートは /dev/ttyACM0
    boost::asio::serial_port serial(io, "/dev/cu.usbmodem14101");
    // 速度は 9600bps
    serial.set_option(boost::asio::serial_port_base::baud_rate(9600));

    // テキトウに5秒待つ
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // "ping" を送信
    std::cout << "on send..." << std::endl;
    boost::asio::write(serial, boost::asio::buffer("ping\n"));

    // serial から response_buf に '\n' まで読み込む
    std::cout << "on read..." << std::endl;
    boost::asio::streambuf response_buf;
    boost::asio::read_until(serial, response_buf, '\n');

    // 表示して終わり
    std::cout << boost::asio::buffer_cast<const char*>(response_buf.data());
}
