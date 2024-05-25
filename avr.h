/*
 * avr.h
 *
 * Created: 5/24/2024 12:23:51 AM
 *  Author: Administrator
 */ 
/*
 * avr.h
 *
 * Created: 5/17/2024 10:58:15 PM
 *  Author: Administrator
 */ 
#ifndef _AVR_H
#define _AVR_H

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#define XTAL_FRQ 8000000lu

#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))

#define WDR() asm volatile("wdr"::)
#define NOP() asm volatile("nop"::)
#define RST() for(;;);

void avr_init(void);

void avr_wait(unsigned short msec);

#endif /* _AVR_H */