// scale_visual.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "modbus.hpp"



int main()
{
    //spdlog::init_thread_pool(10000, 1);
    //auto file_logger = spdlog::rotating_logger_mt<spdlog::async_factory>("main_logger", "logs/mylogs.log", 1024 * 1024 * 5, 100);
    //spdlog::set_default_logger(file_logger);
    //int i = 0;
    //file_logger->set_level(spdlog::level::debug);
    //while (i < 1000000)
    //{
    //    file_logger->debug("Async message #{}", i);
    //    i++;
    //}
    modbus_t* mb;
    int ret;
    //创建一个modbus-rtu对象，指定串口号，波特率，校验位，数据位，停止位
    //成功返回指针，否则返回NULL, 会调用malloc申请内存
    mb = modbus_new_rtu("COM1", 115200, 'N', 8, 1);		//windows
    
    ret = modbus_set_debug(mb, true);

    //设置从机地址，成功返回0, 否则返回-1
    ret = modbus_set_slave(mb, 0);

    //连接Modbus主机，成功返回0, 否则返回-1
    ret = modbus_connect(mb);

    //设置响应超时时间1s,200ms
    ret = modbus_set_response_timeout(mb, 10, 200000);

    //读取寄存器数据,起始地址2, 数量5, 保存到table数组中
    //成功返回5, 否则返回-1
    uint16_t* table = {0};
    ret = modbus_read_registers(mb, 2, 5, table);
    
    //创建一个modbus-rtu对象，指定串口号，波特率，校验位，数据位，停止位
    //成功返回指针，否则返回NULL, 会调用malloc申请内存
    //spdlog::drop_all();
    return 0;
}

