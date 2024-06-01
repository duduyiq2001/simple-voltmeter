/*
 * GccApplication4.c
 *
 * Created: 5/23/2024 10:56:46 PM
 * Author : Administrator
 */

#include <avr/io.h>
#include "avr.h"
#include "keypad.h"
#include "lcd.h"
#include <stdio.h>
#include <math.h>

/*
 * adc.c
 *
 * Created: 5/24/2024 12:55:50 AM
 *  Author: Administrator
 */

int get_sample_pa1(){
	
    // configure the ADC
    ADMUX = 0b01010000;  
    ADCSRA = 0b11000000;
    while (ADCSRA & (1 << 5));
    
    return ADCL + (ADCH << 8);

}
void float_to_string(char *buffer, float value, int places)
{
	int d1 = (int)value;				  // Get the integer part
	float f2 = value - (float)d1;		  // Get fractional part
	int d2 = trunc(f2 * pow(10, places)); // Turn into integer
	sprintf(buffer, "%d.%d", d1, d2);	  // Format as a string
}


enum mode {
	DIFFERENTIAL, NORMAL
};


enum mode CURR_MODE = NORMAL; 

#define MODE_CHANGE_BUTTON '#'
int get_sample()
{

	// configure the ADC
	ADMUX = 0b01000000;
	ADCSRA = 0b11000000;
	while (ADCSRA & 1 << 5);

	return ADCL + (ADCH << 8);
}

void test1()
{
	char buf[50];
	avr_init();
	lcd_init();
	while (1)
	{
		float_to_string(buf, ((get_sample() * 1.0) / 1023.0) * 5.0, 2);
		lcd_clr();
		lcd_pos(0, 0);
		lcd_puts2(buf);
		avr_wait(500);
	}
}

void print_stats(int instant, int min, int max, unsigned long long total, unsigned long long count)
{
	char buf[50];
	lcd_clr();
	/**
	 * inputting instant
	 */
	float_to_string(buf, (instant * 1.0) / 1023.0 * 5.0, 2);
	lcd_pos(0, 0);
	lcd_puts2("ins:");
	lcd_puts2(buf);
	/**
	 * inputting min
	 */
	float_to_string(buf, (min * 1.0) / 1023.0 * 5.0, 2);
	lcd_pos(1, 0);
	lcd_puts2("min:");
	lcd_puts2(buf);
	/**
	 * inputting max
	 */
	float_to_string(buf, (max * 1.0) / 1023.0 * 5.0, 2);
	lcd_pos(0, 9);
	lcd_puts2("max:");
	lcd_puts2(buf);
	/**
	 * inputting avg
	 */
	float_to_string(buf, (((total * 1.0) / (count * 1.0)) / 1023.0) * 5.0, 2);
	lcd_pos(1, 9);
	lcd_puts2("avg:");
	lcd_puts2(buf);
}


int main(void)
{
	/* Replace with your application code */
	// test1();
	unsigned long long total = 0;
	unsigned long long count = 0;
	int min = 1023;
	int max = 0;
	avr_init();
	lcd_init();
	get_sample();
	while (1)
	{
		
		int instant; 
		if ( CURR_MODE == NORMAL)	{
			avr_wait(500);
			
			instant = get_sample();
			total += instant;
			count += 1;
			if (instant < min)
			{
				min = instant;
			}
			if (instant > max)
			{
				max = instant;
			}
		} else if (CURR_MODE == DIFFERENTIAL) {
			avr_wait(500);
			
		
			instant = get_sample_pa1(); 
			 

			instant *= 2;


			total += instant;
			count += 1;
			if (instant < min)
			{
				min = instant;
			}
			if (instant > max)
			{
				max = instant;
			}	
		}
		print_stats(instant, min, max, total, count);

		char user_in = get_char1(); 
		if ('\0' == user_in){
			continue; 
		} else if ('1' == user_in ) {
			total = 0;
			count = 0;
			min = 1023;
			max = 0;
			print_stats(0, min, max, total, count);
			avr_wait(1000);
		} else if (MODE_CHANGE_BUTTON == user_in) {
			if(CURR_MODE == NORMAL){
			CURR_MODE = DIFFERENTIAL;
			}
			else{
				CURR_MODE = NORMAL;
			} 

			total = 0;
			count = 0;
			min = 1023;
			max = 0;
			print_stats(0, min, max, total, count);
			avr_wait(1000);
		}
	}
}
