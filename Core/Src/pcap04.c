/*
 * pcap04.c
 *
 *  Created on: Feb 3, 2024
 *      Author: benrit
 */

#include "pcap04.h"

SPI_HandleTypeDef hspi;


uint8_t spi_read(uint8_t *cmd, size_t size);


void pcap04_init(void){

	hspi.Instance = SPI5;
	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.Direction = SPI_DIRECTION_2LINES;
	hspi.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi.Init.NSS = SPI_NSS_SOFT;
	hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi.Init.CRCPolynomial = 10;


	if(HAL_SPI_Init(&hspi)==HAL_OK){
		Error_Handler();
	}

	// send test cmd 0xfe expected result is 0x11
	uint8_t test_cmd = 0x7e;

	if(spi_read(&test_cmd, 2) != 0x11){
		Error_Handler();
	}


}

uint8_t spi_read(uint8_t *cmd, size_t size){
	uint8_t dataRx;

	HAL_SPI_TransmitReceive(&hspi, cmd, &dataRx, size, HAL_MAX_DELAY);

	return dataRx;
}


void spi_write(uint8_t *data, uint32_t size){

	HAL_SPI_Transmit(&hspi, data, size, HAL_MAX_DELAY);

}
