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

int main() {
	DDRC |= (1 << REL4) | (1 << REL3) | (1 << REL2) | (1 << REL1);

	uart0_conf(MYUBRR0);
	uart1_conf(MYUBRR1);
	adc_init();

	sei();

	uint8_t pomiar;

	while(1) {
		if(rel1_flag) {
			rel1_flag = 0;
		}

		pomiar = adc_read_single(AIN1);
		put_in_buffer1(pomiar);
		pomiar = adc_read_single(AIN2);
		put_in_buffer1(pomiar);
		while(available_buffer1()) {
			uart0_send(get_from_buffer1());
		}
		zmien_stan_przekaznikow();
		_delay_ms(1000);
		while(available_buffer2()) {
			if(get_from_buffer2() == 0x01)
				PORTC ^= (1 << REL1);
		}
	}
}
ISR(USART1_RX_vect) {
	//put_in_buffer1(UDR1);
}

ISR(USART0_RX_vect) {
/*	if( UDR0 == 0x01 ) {
		rel1_flag = 1;
	}
	else if( UDR0 == 0x02 ) {
		rel2_flag = 1;
	}
	else if( UDR0 == 0x03 ) {
		rel3_flag = 1;
	}
	else if( UDR0 == 0x04 ) {
		rel4_flag = 1;
	}*/
	put_in_buffer2(UDR0);
}



