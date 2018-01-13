#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned char weightA = 0x00;
	unsigned char weightB = 0x00;
	unsigned char weightC = 0x00;
	unsigned short totalWeight = 0x0000;
	unsigned char differenceWeight = 0x00;
	unsigned char tempWeight = 0x00;
	
    while(1)
    {
        weightA = PINA;
		weightB = PINB;
		weightC = PINC;
		
		totalWeight = weightA + weightB + weightC;
		
		if(abs((weightA - weightC)) >= 0x50)
		{
			differenceWeight = 0x02;
		}
		if(totalWeight >= 0x008C)
		{
			tempWeight = 0x01;
		}		
		PORTD = tempWeight | differenceWeight;
		tempWeight = 0x00;
		differenceWeight = 0x00;
		totalWeight = 0x0000;
    }
}
