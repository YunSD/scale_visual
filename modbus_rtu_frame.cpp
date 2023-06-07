#include <iostream>
#include <vector>
#include <asio.hpp>
#include "crc16.hpp"
#include "spdlog/spdlog.h"

/* Max between RTU and TCP max adu length (so TCP) */
#define MAX_MESSAGE_LENGTH 260;

class ModbusRTURespondFrame {
public:
    ModbusRTURespondFrame() {};

    void init(unsigned char* buf) {
        int len = 1 + 1 + 1 + buf[3] + 1 + 1;

        int index = 0;
        addr = buf[index++];
        funcCode = buf[index++];
        len = buf[index++];

        std::vector<unsigned char> data;
        for (int i = 0; i < len; i++) {
            data.push_back(buf[i + index]);
        };
        data = data; index += len;

        crc = ((buf[index++] << 8) & 0xFFFF) | ((buf[index]) & 0x00FF);
    }

    bool check_crc() {
        unsigned int len = 1 + 1 + 1 + data.size();
        unsigned char* frame = new unsigned char[len];

        int index;

        frame[index++] = addr;
        frame[index++] = funcCode;
        frame[index++] = len;

        for (unsigned char i : data) {
            frame[index++] = i;
        }

        unsigned short crc_t = CRC16_CALCULATE(frame, len);

        delete[] frame;

        return crc == crc_t;
    };


    unsigned char addr;
    unsigned char funcCode;
    unsigned char len;
    std::vector<unsigned char> data;
    unsigned short crc;
};



class ModbusRTUFrame
{
public:
    ModbusRTUFrame(unsigned char slaveAddr, unsigned char funcCode, unsigned short addr, unsigned short data)
        : m_slaveAddr(slaveAddr), m_funcCode(funcCode), m_addr(addr), m_data(data){
    }

    std::vector<unsigned char> toBytes(){
        std::vector<unsigned char> bytes;
        bytes.push_back(m_slaveAddr);
        bytes.push_back(m_funcCode);
        bytes.push_back((m_addr >> 8) & 0xFF);
        bytes.push_back(m_addr & 0xFF);
        bytes.push_back((m_data >> 8) & 0xFF);
        bytes.push_back(m_data & 0xFF);
        unsigned short crc = CRC16_CALCULATE(bytes);
        bytes.push_back((crc >> 8) & 0xFF);
        bytes.push_back(crc & 0xFF);
        return bytes;
    }


    bool send(asio::serial_port& port){
        std::vector<unsigned char> bytes = toBytes();
        asio::write(port, asio::buffer(bytes));
        return true;
    }


    bool receive(asio::serial_port& port, ModbusRTURespondFrame &response){
        const int max_response_length = MAX_MESSAGE_LENGTH;
        unsigned char buf[max_response_length];
        // read all
        asio::read(port, asio::buffer(buf),asio::transfer_all()); 

        //spdlog::info("Async message #{}", buf);
        response.init(buf);
        return response.check_crc();
    }


private:
    unsigned char m_slaveAddr;
    unsigned char m_funcCode;
    unsigned short m_addr;
    unsigned short m_data;
};


