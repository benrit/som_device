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


#define CMD_COUNT 10
#define CMD_LEN 8
#define PARAM_LEN 24


typedef struct _console_cmd{
	char cmd[CMD_LEN];
	void (*exec)(char *);

}console_cmd_t;


extern device spi1_d;

#define PROCESS_CMD 0x01

void kernel_init(void);



#endif /* INC_KERNEL_H_ */
