/*
 * main.c
 *
 *  Created on: Sep 13, 2015
 *       Autor: Bartosz Wo�niak
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <avr/interrupt.h>

const uint8_t znak[] PROGMEM  =
{
		0b11000000, //0
		0b11111001, //1
		0b10100100, //2
		0b10110000, //3
		0b10011001, //4
		0b10010010, //5
		0b10000010, //6
		0b11111000, //7
		0b10000000, //8
		0b10010000, //9
		0b10001000, //A
		0b10000011, //b
		0b11000110, //C
		0b10100001, //d
		0b10000110, //E
		0b10001110, //F
		0b01111111 //.
};

const uint8_t ziarno[] PROGMEM = {
		135, 184, 111, 211, 130, 91, 132, 159, 48, 79, 89, 190, 55, 212, 77, 9,
		117, 198, 29, 75, 125, 72, 155, 216, 54, 88, 61, 148, 199, 197, 152, 207,
		146, 195, 28, 11, 246, 241, 255, 103, 31, 179, 156, 101, 78, 116, 43, 133,
		204, 105, 25, 46, 102, 94 ,228, 165, 34 ,50, 100, 63 ,62 ,90 ,151, 182, 118,
		82 ,219 ,153, 7 ,30, 147, 112, 56, 40 ,158, 244, 213, 83 ,74 ,123, 124, 224,
		181 ,187 ,58 ,230, 126, 8 ,10, 201, 99 ,33 ,237, 186, 222, 252, 98 ,47 ,39,
		173, 171, 157, 42 ,139, 229, 183, 129, 154, 76 ,188, 114, 81, 149, 37, 248,
		86, 233, 208, 226, 59, 169, 4 ,45, 106, 172, 200, 145, 138, 73, 110, 24, 64,
		189, 164, 142, 122, 223, 68, 35, 84, 49, 127, 95, 44, 60, 238, 93, 254, 218,
		240, 192, 2 ,71 ,243, 27, 17, 225, 70, 235, 185, 85 ,69 ,80 ,14 ,150, 245,
		209, 119, 250 ,217, 203, 131, 128, 210, 65, 221, 92, 215, 144, 5 ,234, 36,
		163, 191, 87, 168, 175, 18, 15, 134, 251, 202, 0 ,176, 214, 194, 170, 38

};

uint8_t i = 0;
int main (void){
DDRB = 0xff; // wyjscia wyswietlacza
DDRD |= (1<<PD3)|(1<<PD4)|(1<<PD5); //3 wyjscia mocy

DDRD &=~ ((1<<PD0)|(1<<PD1)|(1<<PD2)); //klawisze
PORTD |= (1<<PD0)|(1<<PD1)|(1<<PD2); //podci�gam wejscia przycikow



	while (1){
		_delay_ms(1000);
		PORTB = pgm_read_byte(&znak[i] ) ;
		++i;
if ( i== 17) i= 0;
	}
}

//ISR(TIMER0_COMP_vect)
//ISR(TIMER0_OVF_vect)
//{

//}

