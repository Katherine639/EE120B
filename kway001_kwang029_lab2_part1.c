#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char numPortA = 0x00;
	unsigned char numPortB = 0x00;
	unsigned char totalA = 0x00;
	unsigned char totalB = 0x00;
	unsigned char loop = 0x00;
	unsigned char temp = 0x00;
	
    while(1)
    {
		numPortA = PINA;
		numPortB = PINB;
		totalA = 0x00;
		totalB = 0x00;
		for(loop; loop < 0x08; loop = loop + 0x01)
		{
			temp = (numPortA >> loop) & 0x01;
			if(temp == 0x01)
			{
				totalA = totalA + 0x01;
			}
		}
		loop = 0x00;
		for(loop; loop < 0x08; loop = loop + 0x01)
		{
			temp = (numPortB >> loop) & 0x01;
			if(temp == 0x01)
			{
				totalB = totalB + 0x01;
			}
		}
		PORTC = totalB + totalA;		
		loop = 0x00;		
    }
}
