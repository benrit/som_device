/*
 * uart.c
 *
 *  Created on: Feb 3, 2024
 *      Author: benrit
 */

#include "uart.h"


UART_HandleTypeDef huart1;
osThreadId read_uart_id;



void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */
 __NVIC_EnableIRQ(USART1_IRQn);
 __NVIC_SetPriority(USART1_IRQn, 10);
  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 1000000;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;



  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN USART1_Init 2 */
  huart1.Instance->CR1 |= USART_CR1_RXNEIE;

  /* USER CODE END USART1_Init 2 */

}


void read_uart(void const * arg){

	while(1){
		if(osSignalWait(0x0001, osWaitForever).status == osEventSignal){}
        HAL_GPIO_TogglePin(GPIOG, LD3_Pin);
		osDelay(1000);
	}
}



void USART1_IRQHandler(void){
	HAL_UART_IRQHandler(&huart1);

	if((huart1.Instance->SR & USART_SR_RXNE) == USART_SR_RXNE ){
		if(huart1.Instance->DR == '\r'){
			HAL_GPIO_TogglePin(GPIOG, LD4_Pin);
			osSignalSet(read_uart_id, 0x0001);
			uint8_t temp[] = {'\r', '\n'};

			HAL_UART_Transmit_IT(&huart1, temp, 2);

		}else{
			HAL_UART_Transmit_IT(&huart1, (uint8_t*)&huart1.Instance->DR, 1);
		}

	}

}



