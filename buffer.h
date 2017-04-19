/*
 * buffer.h
 *
 *  Created on: 22 maj 2016
 *      Author: Jeff
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "main.h"

// BufferS for UART0

#define BUFFER0_SIZE	64

void put_in_bufferTX0( uint8_t data );
uint8_t available_bufferTX0( void );
uint8_t get_from_bufferTX0( void );

void put_in_bufferRX0( uint8_t data );
uint8_t available_bufferRX0( void );
uint8_t get_from_bufferRX0( void );

// Buffer for UART1

#define BUFFER1_SIZE	64

void put_in_bufferTX1( uint8_t data );
uint8_t available_bufferTX1( void );
uint8_t get_from_bufferTX1( void );

void put_in_bufferRX1( uint8_t data );
uint8_t available_bufferRX1( void );
uint8_t get_from_bufferRX1( void );

#endif /* BUFFER_H_ */
