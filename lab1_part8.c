#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char partB = 0x00;
	unsigned char partC = 0x00;
	while(1)
	{
		partB = (PINA & 0xF0) >> 4;
		partC = (PINA & 0x0F) << 4;
		
		PORTB = partB;
		PORTC = partC;
	}
}
