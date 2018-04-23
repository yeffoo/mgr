/*
 * uart.c
 *
 *  Created on: 17 maj 2016
 *      Author: Jeff
 */

#include "uart.h"

/*
FTDI
 */
void uart0_conf(unsigned int baud) {
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
	UCSR0B |= (1 << RXCIE0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8 bit data

	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L = (unsigned char)baud;

	//OSCCAL = 145; // Kalibracja
}

void uart0_send( uint8_t data ) {
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

uint8_t uart0_receive( void ) {
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}

void uart0_puts(char *data) {
//	register char c;
//	while ((c = *data++))
//		uart0_send(c);
	while ( *data )
		uart0_send(*data++);
}

/*
ESP8266
 */
void uart1_conf(unsigned int baud) {
	UCSR1B |= (1 << TXEN1) | (1 << RXEN1);
	UCSR1B |= (1 << RXCIE1);
	UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10); // 8 bit data

	UBRR1H = (unsigned char)(baud>>8);
	UBRR1L = (unsigned char)baud;

	//OSCCAL = 145; // Kalibracja
}

void uart1_send( uint8_t data ) {
	while ( !( UCSR1A & (1<<UDRE1)) );
	UDR1 = data;
}

uint8_t uart1_receive( void ) {
	while ( !(UCSR1A & (1<<RXC1)) );
	return UDR1;
}

void uart1_puts(char *data) {
	while (*data)
		uart1_send(*data++);
}
