/*
 * GccApplication4.c
 *
 * Created: 5/23/2024 10:56:46 PM
 * Author : Administrator
 */ 
// #include <pthread.h>

#include <avr/io.h>
#include "keypad.h"
#include "lcd.h"
#include "adc.h"
#include <stdio.h>

#define RESET_BUTTON '*'
// #include 

/*
 * adc.c
 *
 * Created: 5/24/2024 12:55:50 AM
 *  Author: Administrator
 */ 

#define SENSOR_READ_PERIOD_MS 500
volatile char curr_char_input = '\0'; 

// pthread_mutex_t CHAR_LOCK; 
// pthread_mutex_t LCD_WRITE_LOCK; 

// void keyboard_thread(){
// 	while (1) {
// 		set_curr_char(get_char_wait()); 
// 	}
// }



int reading_prev_prev = 0; 
int reading_prev = 0; 
int reading_curr = 0; 

unsigned int total_combined = 0; 
unsigned char num_readings = 0; 
#define NUM_TOP_BITS 5
#define NUM_TOTAL_BITS 8
#define NUM_COMBINATIONS 8 //3 ^ 2


int get_sample(){
	
		// configure the ADC
		ADMUX = 0b01000000;
		ADCSRA = 0b11000000;
		while (ADCSRA & 1 << 5);
	    
		
		return ADCL+ (ADCH << 8);

}

void read_and_update_samples() {

		reading_prev_prev = reading_prev;
		reading_prev = reading_curr; 
		reading_curr = get_sample(); 

	
		total_combined += reading_curr; 

		num_readings += 1; 

}

// uint_t curr_time = 0; 
// uint_t 



int get_top(int sample_obtained, char num_total_bits, char num_top_bits) {
	return sample_obtained >> (num_total_bits - num_top_bits); 
}

char get_bottom_bit_mask(char bottom_bits) {
	char bottom_mask = 0 ; 
	for(int i = 0; i < bottom_bits; i++) {
		bottom_mask *= 2; 
		bottom_mask += 1; 
	}

	return bottom_mask; 
}
int get_bottom(int full_num, char num_bottom_bits) {
	int bottom_mask = get_bottom_bit_mask(num_bottom_bits); 
	return full_num & bottom_mask; 

}




float get_bottom_float(int full_num, int num_combinations, int num_bottom_bits) {
	
	return (float)((float) get_bottom(full_num, num_bottom_bits) / (float) num_combinations); 
}










char time_passed_equal_to_period() {
	return 1; 
}


float convert_int_to_float(int int_to_convert, char total_bits, char top_bits) {
	char bottom_bits = total_bits - top_bits; 

	float bottom_float = get_bottom_float(int_to_convert, NUM_COMBINATIONS, bottom_bits);

	int top = get_top(int_to_convert, total_bits, top_bits);

	return bottom_float + top; 
	 
}


void print_sample_clear(int sample_to_print, int r, int c){
	
	char buf[10]; 


	sprintf(buf, "%.3f", convert_int_to_float(sample_to_print, NUM_TOTAL_BITS, NUM_TOP_BITS)); 
	lcd_clr(); 

	lcd_pos(r, c); 
	lcd_puts2(buf);
}

void print_sample_no_clear(int sample_to_print, int r, int c){
	char buf[10]; 

	sprintf(buf, "%.3f", convert_int_to_float(sample_to_print, NUM_TOTAL_BITS, NUM_TOP_BITS)); 

	lcd_pos(r, c); 
	lcd_puts2(buf);
}

void reset_samples() {
	reading_prev_prev = 0 ;
	reading_prev = 0; 
	total_combined = reading_curr; 
	num_readings = 1; 

}


int get_avg() {
	return total_combined / num_readings; 
}

void set_curr_char(char c) {
	curr_char_input = c; 
}

void reset_curr_char() {
	set_curr_char('\0');
}


void sample_sm() {
	while (1){

		

		curr_char_input = get_char1(); 

		if (RESET_BUTTON == curr_char_input) {
			reset_samples(); 
			reset_curr_char(); 
		} 


		if (/*num ms passed = 500*/ time_passed_equal_to_period()) {

			read_and_update_samples(); 
			print_sample_clear(reading_curr, 0, 0);
		

			if (reading_prev) {
				print_sample_no_clear(reading_curr, 0, 5);
			} else {
				lcd_pos(0, 5);
				lcd_puts2("--");
			}

			if (reading_prev_prev) {
				print_sample_no_clear(reading_curr, 1, 0);

			}
			else {
				lcd_pos(1,0);
				lcd_puts2("--");
			}

			if (reading_prev_prev && reading_prev) {
				print_sample_no_clear(get_avg(), 1, 5);
			} else {
				lcd_pos(1, 5);
				lcd_puts2("--");
			}
			/*num ms passed = 0 / reset*/
		}





	}
}








// void setup_mutex_locks() {
// 	pthread_mutex_init(&CHAR_LOCK);
// 	pthread_mutex_init(&LCD_WRITE_LOCK);
// }

char safe_read_user_input(){
	// pthread_mutex_lock(&CHAR_LOCK);
	char c = curr_char_input ;
	// pthread_mutex_unlock(&CHAR_LOCK);
	return c;

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
    // test1();


	// char c = get_char1(); 


	// lcd_init(); 
	// lcd_clr(); 
	// lcd_pos(0, 0); 
	// lcd_put(c);


	sample_sm(); 
}

