#include <avr/io.h>

int main(void)
{
	DDRD = 0x00; PORTD = 0xFF;
	DDRB = 0xFE; PORTB = 0x01;
	
	unsigned short sensor = 0x0000;
	unsigned char temp = 0x00;
	unsigned char output = 0x01;
    while(1)
    {
        sensor = (PIND << 1);
		temp = PINB & 0x01;
		
		sensor = sensor | temp;
		
		if(sensor >= 0x0046)
		{
			output = 0x02;
		}			 
		else if((sensor < 0x0046) && (sensor > 0x0005))
		{
			output = 0x04;
		}
		PORTB = output;
		output = 0x01;
		sensor = 0x0000;
    }
}
