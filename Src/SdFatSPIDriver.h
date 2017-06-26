#ifndef SDFATSPIDRIVER_H
#define SDFATSPIDRIVER_H

#include "SpiDriver/SdSpiBaseDriver.h"
#include <Arduino_FreeRTOS.h>
#include <stm32f1xx_hal_spi.h>

// This is custom implementation of SPI Driver class. SdFat library is
// using this class to access SD card over SPI
//
// Main intention of this implementation is to drive data transfer
// over DMA and synchronize with FreeRTOS capabilities.

class SdFatSPIDriver : public SdSpiBaseDriver
{
	// SPI module
	SPI_HandleTypeDef spiHandle;

	// GPS thread handle
	TaskHandle_t xSDThread = NULL;

public:
	SdFatSPIDriver();

	virtual void activate();
	virtual void begin(uint8_t chipSelectPin);
	virtual void deactivate();
	virtual uint8_t receive();
	virtual uint8_t receive(uint8_t* buf, size_t n);
	virtual void send(uint8_t data);
	virtual void send(const uint8_t* buf, size_t n);
	virtual void select();
	virtual void setSpiSettings(SPISettings spiSettings);
	virtual void unselect();
};


#endif //SDFATSPIDRIVER_H
