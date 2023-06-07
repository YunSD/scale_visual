// scale_visual.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "asio.hpp"
#include "crc16.hpp"
#include "modbus_rtu_frame.cpp"



int main()
{
    std::cout << "Hello World!\n";
    spdlog::init_thread_pool(10000, 1);
    auto file_logger = spdlog::rotating_logger_mt<spdlog::async_factory>("main_logger", "logs/mylogs.log", 1024 * 1024 * 5, 100);
    spdlog::set_default_logger(file_logger);
    //int i = 0;
    //file_logger->set_level(spdlog::level::debug);
    //while (i < 1000000)
    //{
    //    file_logger->debug("Async message #{}", i);
    //    i++;
    //}
    
    
    //asio::io_service io;
    //asio::serial_port port(io, "COM2");
    //port.set_option(asio::serial_port_base::baud_rate(9600));
    //port.set_option(asio::serial_port_base::character_size(8));
    //port.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
    //port.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
    //uint8_t a[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x0a };
    //uint16_t crc = CRC16_CALCULATE(a, sizeof(a));
    //std::cout << std::hex << crc;

    //std::vector<unsigned char> bytes;
    //bytes.push_back(0x01);
    //bytes.push_back(0x03);
    //bytes.push_back((0x0000 >> 8) & 0xFF);
    //bytes.push_back(0x0000 & 0xFF);
    //bytes.push_back((0x000a >> 8) & 0xFF);
    //bytes.push_back(0x000a & 0xFF);
    //uint16_t crc1 = CRC16_CALCULATE(bytes);
    //std::cout << std::hex << crc1;
    ModbusRTUFrame frame(0x01, 0x03, 0x0000, 0x000a);
    std::vector<unsigned char> bytes = frame.toBytes();
    for (int i = 0; i < bytes.size(); i++) {
        std::cout << std::hex << (int)bytes[i];
    }

    //std::cout << std::hex << frame.toBytes();
    ////int bytes[10];
    ////bytes[1] = 12;
    ////asio::write(port, asio::buffer(bytes));
    //unsigned char buf[100];
    //asio::read(port, asio::buffer(buf));
    //std::cout << buf;
    spdlog::drop_all();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
