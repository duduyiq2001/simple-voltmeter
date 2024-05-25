/*
 * GccApplication4.c
 *
 * Created: 5/23/2024 10:56:46 PM
 * Author : Administrator
 */ 

#include <avr/io.h>

/*
 * adc.c
 *
 * Created: 5/24/2024 12:55:50 AM
 *  Author: Administrator
 */ 
int get_sample(){
	
		// configure the ADC
		ADMUX = 0b01000000;
		ADCSRA = 0b11000000;
		while (ADCSRA & 1 << 5);
	    
		
		return ADCL+ (ADCH << 8);

}

void test1(){
	char buf[20];
	avr_init();
	lcd_init();
	while (1) {
		sprintf(buf, "%d", get_sample());
		lcd_clr();
		lcd_pos(0, 0);
		lcd_puts2(buf);
		avr_wait(500);
	}
}

int main(void)
{
    /* Replace with your application code */
    test1();
}

