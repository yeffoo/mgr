/*
 * main.c
 *
 *  Created on: 07-04-2017
 *      Author: Jeff
 */

#include "main.h"

#include "uart.h"
#include "buffer.h"
#include "adc.h"

uint8_t rel1_flag, rel2_flag, rel3_flag, rel4_flag;

void zmien_stan_przekaznikow() {
	if( rel1_flag ) {
		PORTC ^= (1 << REL1);
		rel1_flag = 0;
	}
		else if( rel2_flag ) {
			PORTC ^= (1 << REL2);
			rel2_flag = 0;
	}
		else if( rel3_flag ) {
			PORTC ^= (1 << REL3);
			rel3_flag = 0;
	}
		else if( rel4_flag ) {
			PORTC ^= (1 << REL4);
			rel4_flag = 0;
	}
	//_delay_ms(20);
}

volatile uint16_t flag_1ms, flag_1s;
void timer0_init() {
	TCCR0A |= (1 << COM0A1); // Clear OC0A on Compare Match
	TCCR0A |= (1 << WGM01); // CTC
	TCCR0B |= (1 << CS01) | (1 << CS00); // Prescaler 64, f=125 kHz
	TIMSK0 |= (1 << OCIE0A); // Compare interrupt
	OCR0A = 125;
}

int main() {
	DDRC |= (1 << REL4) | (1 << REL3) | (1 << REL2) | (1 << REL1);

	uart0_conf(MYUBRR0);
	uart1_conf(MYUBRR1);
	adc_init();
	timer0_init();

	sei();

	uint8_t pomiar;

	while(1) {

		if(flag_1ms) {
			flag_1ms = 0;
			flag_1s++;
			while(available_buffer2()) {
				switch(get_from_buffer2()) {
					case 0x01:
						PORTC ^= (1 << REL1);
					break;
					case 0x02:
						PORTC ^= (1 << REL2);
					break;
					case 0x03:
						PORTC ^= (1 << REL3);
					break;
					case 0x04:
						PORTC ^= (1 << REL4);
					break;
				}
			}
		}

		if( flag_1s >=1000 ) {
			flag_1s = 0;
			pomiar = adc_read_single(AIN1);
			put_in_buffer1(pomiar);
			pomiar = adc_read_single(AIN2);
			put_in_buffer1(pomiar);
			while(available_buffer1()) {
				uart0_send(get_from_buffer1());
			}
		}
	}
}
ISR(USART1_RX_vect) {
	//put_in_buffer1(UDR1);
}

ISR(USART0_RX_vect) {
	put_in_buffer2(UDR0);
}

ISR(TIMER0_COMPA_vect) {
	flag_1ms = 1;
}

