//
// Created by kris on 11.09.20.
//
#include <wiringPiI2C.h>
#include "ADS1115.h"

using namespace ci;
using namespace ci::app;

void ADS1115::setup()
{


    m_i2cAddress = ADS1015_ADDRESS;
    m_conversionDelay = ADS1115_CONVERSIONDELAY;
    m_bitShift = 0;
    m_gain = GAIN_EIGHT; /* +/- 6.144V range (limited to VDD +0.3V max!) */
    fd = wiringPiI2CSetup(m_i2cAddress);
}

void ADS1115::update()
{
    int a = readADC_SingleEnded(0);
    int b = readADC_SingleEnded(1);
    int c = readADC_SingleEnded(2);
    int d = readADC_SingleEnded(3);
    console() << a << " " << b << " " << c << " " << d << std::endl;
}

int ADS1115::readADC_SingleEnded(uint8_t channel)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(m_conversionDelay));
    uint16_t config =
            ADS1015_REG_CONFIG_CQUE_NONE |    // Disable the comparator (default val)
            ADS1015_REG_CONFIG_CLAT_NONLAT |  // Non-latching (default val)
            ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
            ADS1015_REG_CONFIG_CMODE_TRAD |   // Traditional comparator (default val)
            ADS1015_REG_CONFIG_DR_1600SPS |   // 1600 samples per second (default)
            ADS1015_REG_CONFIG_MODE_SINGLE;   // Single-shot mode (default)

    // Set PGA/voltage range
    config |= m_gain;

    // Set single-ended input channel
    switch (channel)
    {
        case (0):
            config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
            break;
        case (1):
            config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
            break;
        case (2):
            config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
            break;
        case (3):
            config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
            break;
    }

    // Set 'start single-conversion' bit
    config |= ADS1015_REG_CONFIG_OS_SINGLE;

    // Write config register to the ADC
    writeRegister(fd, ADS1015_REG_POINTER_CONFIG, config);

    // Wait for the conversion to complete
    // delay(m_conversionDelay);
    std::this_thread::sleep_for(std::chrono::milliseconds(m_conversionDelay));
    // Read the conversion results
    // Shift 12-bit results right 4 bits for the ADS1015
    return readRegister(fd, ADS1015_REG_POINTER_CONVERT);


}

void ADS1115::writeRegister(uint8_t i2cFd, uint8_t reg, uint16_t value)
{
    wiringPiI2CWriteReg16(i2cFd, reg, (value >> 8) | (value & 0xFF));
}

uint16_t ADS1115::readRegister(uint8_t i2cFd, uint8_t reg)
{
    wiringPiI2CWrite(i2cFd, ADS1015_REG_POINTER_CONVERT);
    uint16_t reading = wiringPiI2CReadReg16(i2cFd, reg);
    reading = (reading >> 8) | (reading << 8); // yes, wiringPi did not assemble the bytes as we want
    return reading;
}