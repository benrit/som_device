/*
 * kernel.c
 *
 *  Created on: Nov 16, 2023
 *      Author: benrit
 */


#include "kernel.h"
#include "main.h"

device spi1_d;
device uart_d;

SPI_HandleTypeDef hspi;

int __io_putchar(int ch)
{
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return (status == HAL_OK ? ch : 0);
}




static void spi_init(void){

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
}

uint8_t spi_read(void){
	uint8_t dataRx;
	HAL_SPI_TransmitReceive(&hspi, 0, &dataRx, sizeof(uint8_t), HAL_MAX_DELAY);

	return dataRx;
}


void spi_write(uint8_t *data, uint32_t size){

	HAL_SPI_Transmit(&hspi, data, size, HAL_MAX_DELAY);

}

void kernel_init(void){
	spi1_d = (device){
		.init = spi_init,
		.read = spi_read,
		.write = spi_write
	};

	uart_d = (device) {
		.init = MX_USART1_UART_Init
	};


    osThreadDef(read_uart, read_uart, osPriorityHigh, 0, 4096);
    read_uart_id = osThreadCreate(osThread(read_uart), NULL);



}

