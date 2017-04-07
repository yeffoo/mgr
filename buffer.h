/*
 * buffer.h
 *
 *  Created on: 22 maj 2016
 *      Author: Jeff
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "main.h"

// Buffer for UART0

#define BUFFER1_SIZE	64

void put_in_buffer1( uint8_t data );
uint8_t available_buffer1( void );
uint8_t get_from_buffer1( void );

// Buffer for UART1

#define BUFFER2_SIZE	64

void put_in_buffer2( uint8_t data );
uint8_t available_buffer2( void );
uint8_t get_from_buffer2( void );

#endif /* BUFFER_H_ */
