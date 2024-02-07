/*
 * pcap04.c
 *
 *  Created on: Feb 3, 2024
 *      Author: benrit
 */

#include "pcap04.h"

SPI_HandleTypeDef hspi;

void spi_write(uint8_t *data, uint32_t size);

#define PCAP04_INITIALIZE 0x8A


void pcap04_init(void){

	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	 __HAL_RCC_GPIOB_CLK_ENABLE();
	 __HAL_RCC_SPI1_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	hspi.Instance = SPI1;
	hspi.Init.Mode = SPI_MODE_MASTER;
	hspi.Init.Direction = SPI_DIRECTION_2LINES;
	hspi.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi.Init.NSS = SPI_NSS_SOFT;
	hspi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi.Init.CRCPolynomial = 10;


	if(HAL_SPI_Init(&hspi)==HAL_OK){
		Error_Handler();
	}


	uint8_t cmd = PCAP04_INITIALIZE;
	HAL_SPI_Transmit(&hspi, &cmd, 1, HAL_MAX_DELAY);


	// send test cmd 0xfe expected result is 0x11
	uint8_t test_cmd = 0x7e;
	uint8_t data_rx[5] = {0};

	HAL_SPI_TransmitReceive(&hspi, &test_cmd, data_rx, 2, HAL_MAX_DELAY);
	if(data_rx[0] != 0x11){
		Error_Handler();
	}

}


void spi_write(uint8_t *data, uint32_t size){

	HAL_SPI_Transmit(&hspi, data, size, HAL_MAX_DELAY);

}
