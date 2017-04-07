/*
 * adc.h
 *
 *  Created on: 07-04-2017
 *      Author: Jeff
 */

#ifndef ADC_H_
#define ADC_H_

#include "main.h"

#define AIN1 0x01 // PA1
#define AIN2 0x00 // PA0

void adc_init();
uint8_t adc_read_single(uint8_t mux);
uint8_t adc_read_10(uint8_t mux);
uint8_t adc_read_avg(uint8_t mux, uint8_t amount);
uint8_t adc_read_cont(uint8_t mux);

#endif /* ADC_H_ */
