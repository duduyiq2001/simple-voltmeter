/*
 * utility.h
 *
 * Created: 5/24/2024 12:22:51 AM
 *  Author: Administrator
 */ 
/*
 * utility.h
 *
 * Created: 5/13/2024 7:11:03 AM
 *  Author: Administrator
 */ 

#ifndef UTILITY
#define UTILITY

// frequency of the current ck
#define XTAL_FRQ 8000000lu
#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))

/************************************************************************/
/* set a pin portnum to 1 on PortA                                                                     */
/************************************************************************/
void set_port(char* portname, char portnum);


/************************************************************************/
/* clear a pin portnum to 1 on PortA                                                                     */
/************************************************************************/
void clear_port(char* portname, char portnum);


/************************************************************************/
/* get the value of a pin portnum to 1 on PortA                                                                     */
/************************************************************************/
char get_pin(char* portname, char portnum);


void wait_avr(unsigned short msec);
void wait_micro(unsigned short microsec);
#endif


