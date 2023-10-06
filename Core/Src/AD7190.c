/*
 * AD7190.c
 *
 *  Created on: Sep 30, 2023
 *      Author: benrit
 */
#include <stdio.h>
#include "AD7190.h"

static SPI_HandleTypeDef spi1;
static GPIO_InitTypeDef NSS_Pin;


void AD7190_Error_Handler(void) {
    printf("Error initializing SPI1\n");

    while(1);
}




void ad7190_init(void){

	printf("Initializing AD7190\r\n");
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_SPI1_CLK_ENABLE();
	__NVIC_EnableIRQ(SPI1_IRQn);
	__NVIC_SetPriority(SPI1_IRQn, 9);

	GPIO_InitTypeDef gpioa;

	gpioa.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	gpioa.Mode = GPIO_MODE_AF_PP;
	gpioa.Pull = GPIO_NOPULL;
	gpioa.Speed = GPIO_SPEED_LOW;
	gpioa.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &gpioa);

	NSS_Pin.Pin = GPIO_PIN_4;
	NSS_Pin.Mode = GPIO_MODE_OUTPUT_PP;
	NSS_Pin.Pull = GPIO_NOPULL;
	NSS_Pin.Speed = GPIO_SPEED_LOW;
//	gpioa.Alternate = GPIO_AF5_SPI1;
	HAL_GPIO_Init(GPIOA, &NSS_Pin);


    spi1.Instance = SPI1;
    spi1.Init.Mode = SPI_MODE_MASTER;
    spi1.Init.Direction = SPI_DIRECTION_2LINES;
    spi1.Init.DataSize = SPI_DATASIZE_8BIT;
    spi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
    spi1.Init.CLKPhase = SPI_PHASE_2EDGE;
    spi1.Init.NSS = SPI_NSS_SOFT;
    spi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
    spi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    spi1.Init.TIMode = SPI_TIMODE_DISABLE;
    spi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    spi1.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&spi1) != HAL_OK)
    {
        AD7190_Error_Handler();
    }


}


void ad7190_reset(void){
	uint8_t registerWord[7];

	registerWord[0] = 0x01;
	registerWord[1] = 0xFF;
	registerWord[2] = 0xFF;
	registerWord[3] = 0xFF;
	registerWord[4] = 0xFF;
	registerWord[5] = 0xFF;
	registerWord[6] = 0xFF;

	HAL_SPI_Transmit(&spi1, registerWord, 7, 0xffff);
}

uint32_t ad7190_read_adc_value(uint8_t ch){



}


uint8_t ad7190_read_8bit(uint8_t cmd){
    uint8_t receive = 0;

    cmd |= AD7190_CR_WR;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
    HAL_SPI_Transmit(&spi1, &cmd, 1, 1000);
//    for(int i=0; i<200; i++) {
//    	asm("nop");
//    };
    HAL_SPI_Receive(&spi1, &receive, 1, 1000);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

    return receive;
}

uint32_t ad7190_read_24bit(uint8_t cmd){
    uint32_t receive = 0;
    uint8_t temp = 0;

    cmd |= AD7190_CR_WR;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
    HAL_SPI_Transmit(&spi1, &cmd, 1, 1000);
//    for(int i=0; i<200; i++) {
//    	asm("nop");
//    };
    HAL_SPI_Receive(&spi1, &temp, 1, 1000);
    receive = (temp<<16);

    HAL_SPI_Receive(&spi1, &temp, 1, 1000);
    receive |= (temp<<8);

    HAL_SPI_Receive(&spi1, &temp, 1, 1000);
    receive |= temp;


    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);

    return receive;
}



void ad7190_write_24bit(uint8_t cmd, uint32_t data){
    uint8_t temp = 0;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	HAL_SPI_Transmit(&spi1, &cmd, 1, 1000);
	temp = (uint8_t)(data);
	HAL_SPI_Transmit(&spi1, &temp, 1, 1000);
	temp = (uint8_t)(data >> 8);
	HAL_SPI_Transmit(&spi1, &temp, 1, 1000);
	temp = (uint8_t)(data >> 16);
	HAL_SPI_Transmit(&spi1, &temp, 1, 1000);

}



void SPI1_IRQHandler(void){
	HAL_SPI_IRQHandler(&spi1);

}

