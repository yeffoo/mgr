/*
 * adc.c
 *
 *  Created on: 07-04-2017
 *      Author: Jeff
 */

#include "adc.h"

// Conversion time: 13-260 us
// Sampling frequency: 50-200 kHz
void adc_init() {
	ADMUX |= (1 << REFS0); // Vref = AVCC
	ADCSRA |= (1 << ADIE); // Interrupt
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler: 128, sampling frequency: 62,5 kHz
	ADCSRA |= (1 << ADEN); // Turn on ADC
}

uint8_t adc_read_single() {
	uint8_t ret;

	ADCSRA |= (1 << ADSC); // Start conversion

	return ret;
}

uint8_t adc_read_10() {
	uint8_t ret;
	uint16_t avg = 0;

	uint8_t i;
	for(i=0; i<10; i++) {
		avg += adc_read_single();
	}

	ret = avg / 10;

	return ret;
}

uint8_t adc_read_avg(uint8_t amount) {
	uint8_t ret;
	uint16_t avg = 0;

	uint8_t i;
	for(i=0; i<amount; i++) {
		avg += adc_read_single();
	}

	ret = avg / amount;

	return ret;
}

uint8_t adc_read_cont() {
	uint8_t ret;

	ADCSRA |= (1 << ADSC); // Start conversion

	return ret;
}
