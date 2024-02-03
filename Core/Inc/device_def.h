/*
 * device_def.h
 *
 *  Created on: Feb 2, 2024
 *      Author: benrit
 */

#ifndef INC_DEVICE_DEF_H_
#define INC_DEVICE_DEF_H_

typedef struct __device{
	void (*write)(uint8_t *data, uint32_t size);
	uint8_t (*read)(void);
	void (*init)(void);
	void (*deinit)(void);
} device ;



#endif /* INC_DEVICE_DEF_H_ */
