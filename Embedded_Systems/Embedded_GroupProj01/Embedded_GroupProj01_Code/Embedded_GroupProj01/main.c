/*
 * Embedded_GroupProj01.c
 *
 * Created: 10/21/2023 2:19:07 PM
 * Author : Abdelrahman shrief - Ali Osama - Sondos Reda - Khloud Elhwary 
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/delay.h>


int main (void)
{
	DDRB	= 0xFF;
	PORTB	= 0x00;
	
	while(1){
		PORTB &=~(1<<PINB1);
		PORTB |=(1<<PINB0);
		_delay_ms(500);
		PORTB &=~(1<<PINB0);
		PORTB |=(1<<PINB1);
		_delay_ms(500);


	}
}


