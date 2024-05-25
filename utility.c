/*
 * utility_c.c
 *
 * Created: 5/23/2024 11:07:47 PM
 *  Author: Administrator
 */ 

#include "utility.h"
#include <avr/io.h>

void wait_avr(unsigned short msec){
	TCCR0 = 3;
	while(msec --){
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ/64)*0.001);
		SET_BIT(TIFR, TOV0);
		while(!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}


// tcnto = 256 - 8000000*0.001
//	in terms of 10 micro sc
void wait_micro(unsigned short microsec){
	TCCR0 = 2;
	while(microsec --){
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ/8)*0.00001);
		SET_BIT(TIFR, TOV0);
		while(!GET_BIT(TIFR, TOV0));
	}
	TCCR0 = 0;
}



void set_port(char* portname, char portnum){
	*portname = *portname | 0x01 << portnum;
	
}

void clear_port(char* portname, char portnum){
	*portname = *portname & (~(0x01 << portnum));
	
}

char get_pin(char* portname, char portnum){
	
	return *portname & 0x01 << portnum;
}

