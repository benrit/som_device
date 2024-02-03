/*
 * uart.h
 *
 *  Created on: Feb 3, 2024
 *      Author: benrit
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "cmsis_os.h"


extern UART_HandleTypeDef huart1;
extern osThreadId read_uart_id;

void MX_USART1_UART_Init(void);

void read_uart(void const * arg);

#endif /* INC_UART_H_ */
