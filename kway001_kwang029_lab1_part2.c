#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char cntavail = 0x00;
	unsigned char firstPark = 0x00;
	unsigned char secondPark = 0x00;
	unsigned char thirdPark = 0x00;
	unsigned char fourthPark = 0x00;
	
    while(1)
    {
		firstPark = PINA & 0x01;
		secondPark = PINA & 0x02;
		thirdPark = PINA & 0x04;
		fourthPark = PINA & 0x08;
		
		secondPark = secondPark >> 1;
		thirdPark = thirdPark >> 2;
		fourthPark = fourthPark >> 3;
		
		cntavail = firstPark + secondPark + thirdPark + fourthPark;	
		cntavail = 0x04 - cntavail;	
		PORTC = cntavail;
    }
}
