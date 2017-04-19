/*
 * buffer.c
 *
 *  Created on: 22 maj 2016
 *      Author: Jeff
 */

#include "buffer.h"

// Buffers for UART0

// TX buffer

uint8_t bufferTX0[BUFFER0_SIZE];
uint8_t	bufferTX0_head = 0, bufferTX0_tail = 0;

void put_in_bufferTX0( uint8_t data ) {
	bufferTX0[bufferTX0_head] = data;
	if( ++bufferTX0_head >= BUFFER0_SIZE )
		bufferTX0_head = 0;
}

uint8_t available_bufferTX0( void ) {
	return( (bufferTX0_head - bufferTX0_tail ) % BUFFER0_SIZE );
}

uint8_t get_from_bufferTX0( void ) {
	uint8_t data;
	data = bufferTX0[bufferTX0_tail];
	if( ++bufferTX0_tail >= BUFFER0_SIZE )
		bufferTX0_tail = 0;

	return data;
}

// RX buffer

uint8_t bufferRX0[BUFFER0_SIZE];
uint8_t	bufferRX0_head = 0, bufferRX0_tail = 0;

void put_in_bufferRX0( uint8_t data ) {
	bufferRX0[bufferRX0_head] = data;
	if( ++bufferRX0_head >= BUFFER0_SIZE )
		bufferRX0_head = 0;
}

uint8_t available_bufferRX0( void ) {
	return( (bufferRX0_head - bufferRX0_tail ) % BUFFER0_SIZE );
}

uint8_t get_from_bufferRX0( void ) {
	uint8_t data;
	data = bufferRX0[bufferRX0_tail];
	if( ++bufferRX0_tail >= BUFFER0_SIZE )
		bufferRX0_tail = 0;

	return data;
}

// Buffers for UART1

// TX buffer

uint8_t bufferTX1[BUFFER1_SIZE];
uint8_t	bufferTX1_head = 0, bufferTX1_tail = 0;

void put_in_bufferTX1( uint8_t data ) {
	bufferTX1[bufferTX1_head] = data;
	if( ++bufferTX1_head >= BUFFER1_SIZE )
		bufferTX1_head = 0;
}

uint8_t available_bufferTX1( void ) {
	return( (bufferTX1_head - bufferTX1_tail ) % BUFFER1_SIZE );
}

uint8_t get_from_bufferTX1( void ) {
	uint8_t data;
	data = bufferTX1[bufferTX1_tail];
	if( ++bufferTX1_tail >= BUFFER1_SIZE )
		bufferTX1_tail = 0;

	return data;
}

// RX buffer

uint8_t bufferRX1[BUFFER1_SIZE];
uint8_t	bufferRX1_head = 0, bufferRX1_tail = 0;

void put_in_bufferRX1( uint8_t data ) {
	bufferRX1[bufferRX1_head] = data;
	if( ++bufferRX1_head >= BUFFER1_SIZE )
		bufferRX1_head = 0;
}

uint8_t available_bufferRX1( void ) {
	return( (bufferRX1_head - bufferRX1_tail ) % BUFFER1_SIZE );
}

uint8_t get_from_bufferRX1( void ) {
	uint8_t data;
	data = bufferRX1[bufferRX1_tail];
	if( ++bufferRX1_tail >= BUFFER1_SIZE )
		bufferRX1_tail = 0;

	return data;
}
