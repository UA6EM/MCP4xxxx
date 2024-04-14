/*
 * MCP4xxxx Library for Arduino
 * v0.1
 * MIT License
 * (c) 2024 UA6EM
 */

#include <Arduino.h>
#include <MCP4xxxx.h>
#include <SPI.h>

#define MAX_SPEED_WRITE  250000

 MCP4xxxx::MCP4xxxx(const int& CS, const int& MOSI, const int& SCK, 
                const uint32_t& maxSpeedWrite, const uint8_t& SPIMode) {
    CSpin = CS;
    MOSIpin = MOSI;
    SCKpin = SCK;
    speedW = maxSpeedWrite;
    spimode = SPIMode;
	pinMode(CSpin, OUTPUT);
	digitalWrite(CSpin, HIGH);
}

 MCP4xxxx::MCP4xxxx(const int& CS, const int& MOSI, const int& SCK) {
    CSpin = CS;
    MOSIpin = MOSI;
    SCKpin = SCK;
    speedW = MAX_SPEED_WRITE; // 250 kHz
    spimode = SPI_MODE0;
    pinMode(CSpin, OUTPUT);
	digitalWrite(CSpin, HIGH);
}

 MCP4xxxx::MCP4xxxx(const int& CS) {
    CSpin = CS;
    MOSIpin = MOSI;
    SCKpin = SCK;
    speedW = MAX_SPEED_WRITE; // 250 kHz
    spimode = SPI_MODE0;
    pinMode(CSpin, OUTPUT);
	digitalWrite(CSpin, HIGH);
}

void MCP4xxxx::begin(void){
	SPI.begin();
}

void MCP4xxxx::writeValue(const int& value) {
    SPI.beginTransaction(SPISettings(speedW, MSBFIRST, spimode));
    digitalWrite(CSpin, LOW);
    MSb = 0x11;         // 0b00010001 ; where x = 0, command bits for write
    LSb = value & 0xFF; // No value greater than 255 ; send 0x0 otherwise
    uint16_t transmission = MSb << 8 | LSb;
    SPI.transfer16(transmission);
    digitalWrite(CSpin, HIGH); // Disable chip select
    SPI.endTransaction();
}

void MCP4xxxx::setOff() {
    SPI.beginTransaction(SPISettings(speedW, MSBFIRST, spimode));
    digitalWrite(CSpin, LOW);
    
    MSb = 0x31;  // 0b00110001 ; the first 4 bits are the address, the next 
                 // 2 bits are the command (11, read), and the last 2 are insignificant
    LSb = 0xFF;  // send all ones for the second half so MCP4xxx doesn't get confused.
    uint16_t transmission = MSb << 8 | LSb;
    SPI.transfer16(transmission); // MCP4xxxx will send value back after                              
    digitalWrite(CSpin, HIGH);
    SPI.endTransaction();
  }
