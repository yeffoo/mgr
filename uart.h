/*
 * uart.h
 *
 *  Created on: 17 maj 2016
 *      Author: Jeff
 */

#ifndef UART_H_
#define UART_H_

#include "main.h"

#define FOSC 8000000// Clock Speed
#define BAUD0 9600
#define MYUBRR0 FOSC/16/BAUD0-1
#define BAUD1 9600
#define MYUBRR1 FOSC/16/BAUD1-1

void uart0_conf(unsigned int baud);
void uart0_send( uint8_t data );
uint8_t uart0_receive( void );
void uart0_puts(char *data);

void uart1_conf(unsigned int baud);
void uart1_send( uint8_t data );
uint8_t uart1_receive( void );
void uart1_puts(char *data);

#endif /* UART_H_ */
