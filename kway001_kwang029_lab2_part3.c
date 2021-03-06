#include <avr/io.h>

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char fuelLevel = 0x00;
	unsigned char seatBelt = 0x00;
	unsigned char driver = 0x00;
	unsigned char ignition = 0x00;
	unsigned char sensor = 0x00;
    while(1)
    {
		fuelLevel = PINA;
		seatBelt = PINA & 0x40;
		driver = PINA & 0x20;
		ignition = PINA & 0x10;
		
		if((fuelLevel & 0x01) == 0x01)
		{
			sensor = 0x60;
		}
		if((fuelLevel & 0x02) == 0x02)
		{
			sensor = 0x60;
		}	
		if((fuelLevel & 0x03) == 0x03)
		{
			sensor = 0x70;
		}	
		if((fuelLevel & 0x04) == 0x04)
		{
			sensor = 0x70;
		}	
		if((fuelLevel & 0x05) == 0x05)
		{
			sensor = 0x38;
		}	
		if((fuelLevel & 0x06) == 0x06)
		{
			sensor = 0x38;
		}	
		if((fuelLevel & 0x07) == 0x07)
		{
			sensor = 0x3C;
		}	
		if((fuelLevel & 0x08) == 0x08)
		{
			sensor = 0x3C;
		}
		if((fuelLevel & 0x09) == 0x09)
		{
			sensor = 0x3C;
		}	
		if((fuelLevel & 0x0A) == 0x0A)
		{
			sensor = 0x3E;
		}	
		if((fuelLevel & 0x0B) == 0x0B)
		{
			sensor = 0x3E;
		}	
		if((fuelLevel & 0x0C) == 0x0C)
		{
			sensor = 0x3E;
		}	
		if((fuelLevel & 0x0D) == 0x0D)
		{
			sensor = 0x3F;
		}	
		if((fuelLevel & 0x0E) == 0x0E)
		{
			sensor = 0x3F;
		}	
		if((fuelLevel & 0x0F) == 0x0F)
		{
			sensor = 0x3F;
		}
		
		if(ignition == 0x10)
		{
			if(driver == 0x20)
			{
				if(seatBelt == 0x40)
				{
					PORTC = sensor;
				}
				else
				{
					PORTC = (sensor | 0xA0);
				}
			}
		}
		else
		{
			PORTC = sensor;
		}													 			
    }
}
