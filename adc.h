/*
 * adc.h
 *
 *  Created on: 07-04-2017
 *      Author: Jeff
 */

#ifndef ADC_H_
#define ADC_H_

#include "main.h"

#define AIN1 PA1
#define AIN2 PA0

void adc_init();
uint8_t adc_read_single();
uint8_t adc_read_avg(uint8_t amount);
uint8_t adc_read_cont();

#endif /* ADC_H_ */
