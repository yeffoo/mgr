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


volatile uint16_t flag_1ms, flag_1s;

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
long i = 0, cnt;

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
	memset(comp, 0, size);
}

volatile uint8_t pomiar = 128;
char data_adc_tmp[4];
char data_adc[] = "512b256";

int main() {
	DDRC |= (1 << REL4) | (1 << REL3) | (1 << REL2) | (1 << REL1);

	uart0_conf(MYUBRR0);
	uart1_conf(MYUBRR1);
	adc_init();
	timer0_init();

	sei();


	uint8_t temp;
//	uint8_t oscyl = OSCCAL;
	OSCCAL -= 10; // tutaj byl blad

	uint8_t tmp1;


//	uart1_puts(data_adc);

	while(1) {

		if( flag_1ms >= 10 ) {
			flag_1ms = 0;
			while ( available_bufferRX1() ) {
				tmp1 = get_from_bufferRX1();
				relcmp[cnt++] = tmp1;
//				uart0_send(tmp1);

				if(tmp1 == '\n') {
					cnt = 0;
					relays_state(relcmp, sizeof(relcmp));
//					pomiar = adc_read_10(AIN1);
//					itoa(pomiar, data_adc, 10);
//					strcat(data_adc, "b");
//					pomiar = adc_read_10(AIN2);
//					sprintf(data_adc_tmp, "%d", pomiar);
//					strcat(data_adc, data_adc_tmp);
					uart1_puts(data_adc);
//					uart1_send('\n');
				}
			}
		}

//		if( flag_1s >=1000 ) {
//			flag_1s = 0;
//			pomiar = adc_read_single(AIN1);
//			uart0_send(pomiar);
//			uart1_send(pomiar);
////			put_in_bufferTX0(pomiar);
//			pomiar = adc_read_single(AIN2);
//			uart0_send(pomiar);
//			uart1_send(pomiar);
////			put_in_bufferTX0(pomiar);
////			while(available_bufferTX0()) {
////				temp = get_from_bufferTX0();
//////				uart0_send(get_from_bufferTX0());
////				uart0_send(temp);
////				uart1_send(temp); // Wysyla do modulu ESP8266
////			}
//			cnt = 0;
//		}
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
//	pomiar = adc_read_10(AIN1);
}

