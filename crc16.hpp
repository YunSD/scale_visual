#pragma once

unsigned short CRC16_CALCULATE(unsigned char* buffer, unsigned short len);

unsigned short CRC16_CALCULATE(std::vector<unsigned char>& frame);

