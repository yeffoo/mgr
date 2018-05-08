/*
 * main.c
 *
 *  Created on: 07-04-2017
 *      Author: Jeff
 */

#include "main.h"
#include <stdlib.h>
#include "string.h"

#include "uart.h"
#include "buffer.h"
#include "adc.h"


volatile uint8_t flag_1ms, flag_1s, flag_10s;
volatile uint16_t tick;

void timer0_init() {
	TCCR0A |= (1 << COM0A1); // Clear OC0A on Compare Match
	TCCR0A |= (1 << WGM01); // CTC
	TCCR0B |= (1 << CS01) | (1 << CS00); // Prescaler 64, f=125 kHz
	TIMSK0 |= (1 << OCIE0A); // Compare interrupt
	OCR0A = 125;
}

char relcmp[16];

char rel1on[] = "REL1_ON\r\n";
char rel1off[] = "REL1_OFF\r\n";
char rel2on[] = "REL2_ON\r\n";
char rel2off[] = "REL2_OFF\r\n";
char rel3on[] = "REL3_ON\r\n";
char rel3off[] = "REL3_OFF\r\n";
char rel4on[] = "REL4_ON\r\n";
char rel4off[] = "REL4_OFF\r\n";
char relon[] = "REL_ON\r\n";
char reloff[] = "REL_OFF\r\n";
uint8_t  cnt;

void relays_state(char *comp, uint8_t size) {
	if( strcmp(comp, rel1on) == 0) {
		PORTC |= (1 << REL1);
	}
	else if( strcmp(comp, rel1off) == 0 ) {
		PORTC &= ~(1 << REL1);
	}
	else if( strcmp(comp, rel2on) == 0 ) {
		PORTC |= (1 << REL2);
	}
	else if( strcmp(comp, rel2off) == 0 ) {
		PORTC &= ~(1 << REL2);
	}
	else if( strcmp(comp, rel3on) == 0 ) {
		PORTC |= (1 << REL3);
	}
	else if( strcmp(comp, rel3off) == 0 ) {
		PORTC &= ~(1 << REL3);
	}
	else if( strcmp(comp, rel4on) == 0 ) {
		PORTC |= (1 << REL4);
	}
	else if( strcmp(comp, rel4off) == 0 ) {
		PORTC &= ~(1 << REL4);
	}
	else if( strcmp(comp, relon) == 0 ) {
		PORTC |= (1 << REL4) | (1 << REL3) | (1 << REL2) | (1 << REL1);
	}
	else if( strcmp(comp, reloff) == 0 ) {
		PORTC &= ~( (1 << REL4) | (1 << REL3) | (1 << REL2) | (1 << REL1) );
	}
	memset(comp, 0, size);
}

volatile uint16_t pomiar = 128;
char data_adc_tmp[4];
char data_adc[16];// = "512b256\r\n";

int main() {
	DDRC |= (1 << REL4) | (1 << REL3) | (1 << REL2) | (1 << REL1);
	PORTC &= ~( (1 << REL4) | (1 << REL3) | (1 << REL2) | (1 << REL1) );

	uart0_conf(MYUBRR0);
	uart1_conf(MYUBRR1);
	adc_init();
	timer0_init();

	sei();

//	uint8_t temp;
//	uint8_t oscyl = OSCCAL;
	OSCCAL -= 10; // tutaj byl blad

	uint8_t tmp1;

	while(1) {

		if( flag_1ms >= 10 ) {
			flag_1ms = 0;
			while ( available_bufferRX1() ) {
				tmp1 = get_from_bufferRX1();
				relcmp[cnt++] = tmp1;

				if(tmp1 == '\n') {
					cnt = 0;
					relays_state(relcmp, sizeof(relcmp));
				}
			}
		}

		if(flag_10s) {
			flag_10s = 0;
			pomiar = adc_read_10(AIN1);
			itoa(pomiar, data_adc, 10);
			strcat(data_adc, "b");
			pomiar = adc_read_10(AIN2);
			itoa(pomiar, data_adc_tmp, 10);
			strcat(data_adc, data_adc_tmp);
//			uart0_puts(data_adc);
			uart1_puts(data_adc);
		}

	}
}

//ftdi
//ISR(USART0_RX_vect) {
//	uint8_t tmp_data;
///*	while(UDR0 != '\n') {
//		put_in_bufferTX1(UDR0);
//	}*/
//	tmp_data = UDR0;
////	put_in_bufferRX0(tmp_data);
//	uart1_send(tmp_data);
//}

//esp
ISR(USART1_RX_vect) {
//	uint8_t tmp_data;
//	tmp_data = UDR1;
//	while(UDR1 != '\r') {
//		put_in_bufferRX1(UDR1);
//	}
	put_in_bufferRX1(UDR1);
//	uart0_send(UDR1);
}

ISR(TIMER0_COMPA_vect) {
	flag_1ms++;
	if(tick++ >= 10000) {
		tick = 0;
		flag_10s = 1;
	}
//	pomiar = adc_read_10(AIN1);
}

