
#include <avr/io.h>


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF; // Configure PORTA as input, initialize to 1s
	DDRB = 0xFF; PORTB = 0x00; // Configure PORTB as outputs, initialize to 0s
	unsigned char led = 0x00;
	
	unsigned char button1 = 0x00;
	unsigned char button2 = 0x00;
	unsigned char button3 = 0x00;
	unsigned char button4 = 0x00;
	unsigned int sum = 0;
	while(1)
	{
		// if PA0 is 1, set PB1PB0=01, else =10
		// 1) Read inputs
		button1 = ~PINA & 0x01; // button is connected to A0
		button2 = ~PINA & 0x02;
		button3 = ~PINA & 0x04;
		button4 = ~PINA & 0x08;
		sum = button1 + button2 + button3 + button4;
		// 2) Perform Computation
		if (sum <= 2 && sum > 0) { // True if button is pressed
			led = 0x60; // Sets B to bbbbbb01
			// (clear rightmost 2 bits, then set to 01)
		}
		else if( sum <= 4 && sum > 0){
			led = 0x70;
		}
		else if( sum <= 6 && sum > 0){
			led =  0x38;
		}
		else if( sum <= 9 && sum > 0){
			led =  0x3C;
		}
		else if( sum <= 12 && sum > 0){
			led = 0x3E;
		}
		else if( sum <= 15 && sum > 0){
			led = 0x3F;
			while(PINA != 0);
		}
		else {
			//led = (led & 0xFC) | 0x00; // Sets B to bbbbbb10
			// (clear rightmost 2 bits, then set to 10)
		}
		// 3) Write output
		PORTB = led;
		
	}
}


