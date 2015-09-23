/*
 * main.c
 *
 *  Created on: Sep 13, 2015
 *       Autor: Bartosz WoŸniak
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <avr/interrupt.h>

//---------******************************-----------
//makrodefinicje portów
#define OUT1_PIN (1<<PD3)
#define OUT2_PIN (1<<PD4)
#define OUT3_PIN (1<<PD5)

#define OUT1_ON PORTD |= OUT1_PIN
#define OUT2_ON PORTD |= OUT2_PIN
#define OUT3_ON PORTD |= OUT3_PIN

#define OUT1_OFF PORTD &=~ OUT1_PIN
#define OUT2_OFF PORTD &=~ OUT2_PIN
#define OUT3_OFF PORTD &=~ OUT3_PIN

#define OUT1_TOG PORTD ^= OUT1_PIN
#define OUT2_TOG PORTD ^= OUT2_PIN
#define OUT3_TOG PORTD ^= OUT3_PIN

#define KEY_PLUS (1<<PD2)
#define KEY_SET (1<<PD1)
#define KEY_MINUS (1<<PD0)
//---------************KONIEC MAKR******************-----------


//---------******************************-----------
//STA£E ZNAKOWE DLA WYŒWIETLACZA 7 SEG
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

// TABLICA ZIAREN DLA FUNKCJI SRAND:
const uint8_t ziarno[] PROGMEM = {
		135, 184, 111, 211, 130, 91,  132, 159, 48,  79,  89,  190, 55,  212, 77,  9,
		117, 198, 29,   75, 125, 72,  155, 216, 54,  88,  61,  148, 199, 197, 152, 207,
		146, 195, 28,   11, 246, 241, 255, 103, 31,  179, 156, 101, 78,  116, 43,  133,
		204, 105, 25,   46, 102, 94 , 228, 165, 34 , 50,  100, 63 , 62 , 90 , 151, 182,
		82 , 219 ,153,   7 ,30,  147, 112, 56,  40 , 158, 244, 213, 83 , 74 , 123, 124,
		181 ,187 ,58 , 230, 126, 8 ,  10,  201, 99 , 33 , 237, 186, 222, 252, 98 , 47 ,
		173, 171, 157,  42 ,139, 229, 183, 129, 154, 76 , 188, 114, 81,  149, 37,  248,
		86,  233, 208, 226, 59,  169, 4 ,  45,  106, 172, 200, 145, 138, 73,  110, 24,
		189, 164, 142, 122, 223, 68,  35,  84,  49,  127, 95,  44,  60,  238, 93,  254,
		240, 192, 2 ,   71 ,243, 27,  17,  225, 70,  235, 185, 85 , 69 , 80 , 14 , 150,
		209, 119, 250 ,217, 203, 131, 128, 210, 65,  221, 92,  215, 144, 5 ,  234, 36,
		163, 191, 87,  168, 175, 18,  15,  134, 251, 202, 0 ,  176, 214, 194, 170, 38

};
//-----------------------*********** KONIEC STA£YCH*********-----------------

//-----------------------*********** zmienne globalne*********-----------------
uint8_t flag=0;
//-----------------------*********** deklaracje funkcji*********-------------

uint8_t key_down ( uint8_t key);
void serwis (void);
void regulacja(uint8_t var_tim);

//---------------------------------------------------------------------------
uint8_t i = 0;
//***************************************************************************
// ----------*********** MAIN *************----------------------------------
//***************************************************************************
int main (void){

	DDRB = 0xff; // wyjscia wyswietlacza
	PORTB = 0xff; //zgaszam wysw.
	DDRD |= (1<<PD3)|(1<<PD4)|(1<<PD5); //3 wyjscia mocy

	DDRD &=~ ((1<<PD0)|(1<<PD1)|(1<<PD2)); //klawisze
	PORTD |= (1<<PD0)|(1<<PD1)|(1<<PD2); //podci¹gam wejscia przycikow

	if ( key_down ( KEY_SET)) serwis();

	TCCR0B |= (1<<CS02) | (1<<CS00); // prescale 1024
	TIMSK |= (1<<TOIE0); //zezwolenie na przerwanie od przepe³nienia
	TCNT0 = 157 ; // wychodzi nam przerwanie co
	sei(); //globalny uk³ad przerwañ

	uint8_t licz = 0;



	while (1){
		if ( flag ){
			++licz;
			flag =0;
		}

		if (licz == 10) PORTB=rand();
	};
}

//***************************************************************************
// ----------**********KONIEC MAIN************-------------------------------
//***************************************************************************

uint8_t key_down ( uint8_t key){

	if (!(PIND & key)){
		_delay_ms(30);
		if (!(PIND & key)){ // tu wiadomo ze juz wcisnieto
			while( !(PIND & key)){} //czekaj a¿ puszczê
			_delay_ms(30);
			return 1;
		}
	}
	return 0;
}


void serwis (void){
//wchodzimy w tryb serwisowy
//	tutaj zapisujemy dane do eepromu
	uint8_t n = 0;
	uint8_t t_kropki = eeprom_read_byte(0x01);
	uint8_t t_kreski = eeprom_read_byte(0x02);
	uint8_t t_pauzy  = eeprom_read_byte(0x03);
	PORTB=0x00;

	for ( uint8_t i = 3 ; !i ; --i){
		PORTB = ~PORTB;
		_delay_ms(300);
	}
//tu pole do popisu :
	// mo¿na przerobiæ kod na tablice i wykorzystaæ n do indeksowania,
	// argumentem funkcji by³oby tab[n] !
	while ( n<3 ){
		if ( key_down ( KEY_SET)) ++n;

		if (n == 0)regulacja(t_kropki);
			//ustaw pauzê // regulacja od 0.1 do 0.5

		if (n == 1)regulacja(t_kreski);
			//ustaw kropkê  // regulacja od 0.1 do 0.5

		if (n == 2)regulacja(t_pauzy);
			//ustaw kreskê // regulacja od 0.3 do 1.5
	}

	//wpisz z powrotem dane do eepromu
	eeprom_write_byte(0x01,t_kropki);
	eeprom_write_byte(0x02,t_kreski);
	eeprom_write_byte(0x03,t_pauzy);
}

void regulacja(uint8_t var_tim){
	if(key_down(KEY_PLUS)) {
		++var_tim;
		if (var_tim == 16) var_tim = 15;
	}

	if(key_down(KEY_MINUS)){
		--var_tim;
		if (var_tim == 2) var_tim = 3;
	}

	PORTB = pgm_read_byte(&znak[var_tim]);
}


ISR(TIMER0_OVF_vect){
TCNT0 = 157;
		flag = 1;
}
