/*
 * main.c
 *
 *  Created on: 07-04-2017
 *      Author: Jeff
 */

#include "main.h"

#include "uart.h"
#include "adc.h"
//#include "buffer.h"

#define BUFFER1_SIZE	128
uint8_t buffer1[BUFFER1_SIZE];
uint8_t	buffer1_head = 0, buffer1_tail = 0;

void put_in_buffer1( uint8_t data ) {
	buffer1[buffer1_head] = data;
	if( ++buffer1_head >= BUFFER1_SIZE )
		buffer1_head = 0;
}

uint8_t available_buffer1( void ) {
	return( (buffer1_head - buffer1_tail ) % BUFFER1_SIZE );
}

uint8_t get_from_buffer1( void ) {
	uint8_t data;
	data = buffer1[buffer1_tail];
	if( ++buffer1_tail >= BUFFER1_SIZE )
		buffer1_tail = 0;

	return data;
}

#define BUFFER2_SIZE	256
uint8_t buffer2[BUFFER2_SIZE];
uint8_t	buffer2_head = 0, buffer2_tail = 0;

void put_in_buffer2( uint8_t data ) {
	buffer2[buffer2_head] = data;
	if( ++buffer2_head >= BUFFER2_SIZE )
		buffer2_head = 0;
}

uint8_t available_buffer2( void ) {
	return( (buffer2_head - buffer2_tail ) % BUFFER2_SIZE );
}

uint8_t get_from_buffer2( void ) {
	uint8_t data;
	data = buffer2[buffer2_tail];
	if( ++buffer2_tail >= BUFFER2_SIZE )
		buffer2_tail = 0;

	return data;
}

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

char tablica[40] = "AT+CWSAP=przekazniki,password,1,2";

int main() {
	DDRC |= (1 << REL4) | (1 << REL3) | (1 << REL2) | (1 << REL1);

	uart0_conf(MYUBRR0);
	uart1_conf(MYUBRR1);
	//adc_init();

	sei();

	while(1) {
		//adc_start_single(AIN2);
		if(rel1_flag) {
			rel1_flag = 0;
			//uart1_puts("AT+CWSAP="+0x22+"przekazniki"+0x22+","+0x22+"password"+0x22+",1,2");
/*			uart1_puts("AT+CWSAP=");
			uart1_send(0x22);//przekazniki,password,1,2")
			uart1_puts("bufet");
			uart1_send(0x22);
			uart1_send(0x2C);
			uart1_send(0x22);
			uart1_puts("password");
			uart1_send(0x22);
			uart1_puts(",1,2<CR><LF>");*/
			//_delay_ms(5000);
		}

		if( available_buffer1() )
			uart0_send( get_from_buffer1() );
		if( available_buffer2() )
			uart1_send( get_from_buffer2() );
		zmien_stan_przekaznikow();

/*		uart0_puts("AT");
		_delay_ms(100);*/

	}
}
ISR(USART1_RX_vect) {
	put_in_buffer1(UDR1);
}

ISR(USART0_RX_vect) {
	if( UDR0 == 0x01 ) {
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
	}
	put_in_buffer2(UDR0);
}



