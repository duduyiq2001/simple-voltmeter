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
#include "stdio.h"
#include <math.h>
#include <time.h>
#include <avr/wdt.h>
/*
 * adc.c
 *
 * Created: 5/24/2024 12:55:50 AM
 *  Author: Administrator
 */
// volatile unsigned char TimerFlag = 0; // ISR raises, main() lowers
// void TimerISR()
// {
// 	TimerFlag = 1;
// }
void float_to_string(char *buffer, float value, int places)
{
	int d1 = (int)value;				  // Get the integer part
	float f2 = value - (float)d1;		  // Get fractional part
	int d2 = trunc(f2 * pow(10, places)); // Turn into integer
	sprintf(buffer, "%d.%d", d1, d2);	  // Format as a string
}
int get_sample()
{

	// configure the ADC
	ADMUX = 0b01000000;
	ADCSRA = 0b11000000;
	while (ADCSRA & 1 << 5)
		;

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

void print_none()
{
	lcd_clr();
	/**
	 * inputting instant
	 */

	lcd_pos(0, 0);
	lcd_puts2("ins:");
	lcd_puts2("--");
	/**
	 * inputting min
	 */
	lcd_pos(1, 0);
	lcd_puts2("min:");
	lcd_puts2("--");
	/**
	 * inputting max
	 */
	lcd_pos(0, 9);
	lcd_puts2("max:");
	lcd_puts2("--");
	/**
	 * inputting avg
	 */
	lcd_pos(1, 9);
	lcd_puts2("avg:");
	lcd_puts2("--");
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
	wdt_disable();	
	get_sample();
	// TimerSet(500);
	while (1)
	{
        avr_wait(495);
		if (get_char1() == '1')
		{
			total = 0;
			count = 0;
			min = 1023;
			max = 0;
			print_none();
			avr_wait(200);
			while (get_char() != '2'){
				print_none();
			}
			
		}
		int instant = get_sample();
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
		print_stats(instant, min, max, total, count);
	}
}
