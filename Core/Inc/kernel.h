/*
 * kernel.h
 *
 *  Created on: Nov 16, 2023
 *      Author: benrit
 */

#ifndef INC_KERNEL_H_
#define INC_KERNEL_H_

#include <stdint.h>
#include "device_def.h"
#include "uart.h"

void kernel_init(void);


extern device spi1_d;

#endif /* INC_KERNEL_H_ */
