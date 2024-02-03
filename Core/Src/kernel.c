/*
 * kernel.c
 *
 *  Created on: Nov 16, 2023
 *      Author: benrit
 */


#include "kernel.h"
#include "main.h"

device uart_d;


int __io_putchar(int ch)
{
    HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return (status == HAL_OK ? ch : 0);
}




void kernel_init(void){

	uart_d = (device) {
		.init = MX_USART1_UART_Init
	};


    osThreadDef(read_uart, read_uart, osPriorityHigh, 0, 4096);
    read_uart_id = osThreadCreate(osThread(read_uart), NULL);



}

