/*
 * AD7190.h
 *
 *  Created on: Sep 30, 2023
 *      Author: benrit
 */

#ifndef INC_AD7190_H_
#define INC_AD7190_H_

#include "stm32f4xx_hal.h"


#define AD7190_CR_WEN     (0<<7)
#define AD7190_CR_WR      (1<<6)
#define AD7190_CR_RS2     (1<<5)
#define AD7190_CR_RS1     (1<<4)
#define AD7190_CR_RS0     (1<<3)
#define AD7190_CR_CREAD   (1<<2)
#define AD7190_CR_CR1     (0<<1)
#define AD7190_CR_CR0     (0<<0)

#define AD7190_SR_RDY     (1<<7)
#define AD7190_SR_ERR     (1<<6)
#define AD7190_SR_NOREF   (1<<5)
#define AD7190_SR_PARITY  (1<<4)
#define AD7190_SR_SR3     (0<<3)
#define AD7190_SR_CHD2    (1<<2)
#define AD7190_SR_CHD1    (1<<1)
#define AD7190_SR_CHD0    (1<<0)

#define AD7190_MR_MD2     (1<<23)
#define AD7190_MR_MD1     (1<<22)
#define AD7190_MR_MD0     (1<<21)
#define AD7190_MR_DAT_STA (1<<20)
#define AD7190_MR_CLK1    (1<<19)
#define AD7190_MR_CLK0    (1<<18)
#define AD7190_MR_MR17    (0<<17)
#define AD7190_MR_MR16    (0<<16)
#define AD7190_MR_SINC    (1<<15)
#define AD7190_MR_MR14    (0<<14)
#define AD7190_MR_ENPAR   (1<<13)
#define AD7190_MR_MR12    (0<<12)
#define AD7190_MR_Single  (1<<11)
#define AD7190_MR_REJ60   (1<<10)
#define AD7190_MR_FS9     (1<<9)
#define AD7190_MR_FS8     (1<<8)
#define AD7190_MR_FS7     (1<<7)
#define AD7190_MR_FS6     (1<<6)
#define AD7190_MR_FS5     (1<<5)
#define AD7190_MR_FS4     (1<<4)
#define AD7190_MR_FS3     (1<<3)
#define AD7190_MR_FS2     (1<<2)
#define AD7190_MR_FS1     (1<<1)
#define AD7190_MR_FS0     (1<<0)

#define AD7190_CON_CHOP   (1<<23)
#define AD7190_CON_CON22  (0<<22)
#define AD7190_CON_CON21  (0<<21)
#define AD7190_CON_REFSEL (1<<20)
#define AD7190_CON_CON19  (1<<19)
#define AD7190_CON_CON18  (1<<18)
#define AD7190_CON_CON17  (1<<17)
#define AD7190_CON_CON16  (1<<16)
#define AD7190_CON_CH7    (1<<15)
#define AD7190_CON_CH6    (1<<14)
#define AD7190_CON_CH5    (1<<13)
#define AD7190_CON_CH4    (1<<12)
#define AD7190_CON_CH3    (1<<11)
#define AD7190_CON_CH2    (1<<10)
#define AD7190_CON_CH1    (1<<9)
#define AD7190_CON_CH0    (1<<8)
#define AD7190_CON_BURN   (1<<7)
#define AD7190_CON_REFDET (1<<6)
#define AD7190_CON_CON5   (1<<5)
#define AD7190_CON_BUF    (1<<4)
#define AD7190_CON_UB     (1<<3)
#define AD7190_CON_G2     (1<<2)
#define AD7190_CON_G1     (1<<1)
#define AD7190_CON_G0     (1<<0)

#define AD7190_STATUS_REGISTER 0x00
#define AD7190_CONFIGURATION_REGISTER 0x10
#define AD7190_ID_REGISTER 0x20


typedef enum {
	Status_Ok = 0x00,
	Status_Err = 0x01
}Status_TypeDef;


Status_TypeDef ad7190_init(void);
void ad7190_reset(void);
uint32_t ad7190_read_adc_value(uint8_t);

uint8_t ad7190_read_8bit(uint8_t cmd);
uint32_t ad7190_read_24bit(uint8_t cmd);


#endif /* INC_AD7190_H_ */
