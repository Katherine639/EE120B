#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	// in Free Running Mode, a new conversion will trigger
	// whenever the previous conversion completes.
}

unsigned short MAX = 0x0C7;
unsigned short ADC_copy = 0x00;
unsigned short tmp = 0x00;
	
int main(void)
{	
	tmp = (MAX / 8);
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	ADC_init();
	
    while(1)
    {
		ADC_copy = ADC;
		if(ADC_copy <= tmp)
		{
			PORTB = 0x01;
		}
		else if(ADC_copy <= (2*tmp))
		{
			PORTB = 0x03;
		}
		else if(ADC_copy <= (3*tmp))
		{
			PORTB = 0x07;
		}
		else if(ADC_copy <= (4*tmp))
		{
			PORTB = 0x0F;
		}
		else if(ADC_copy <= (5*tmp))
		{
			PORTB = 0x1F;
		}
		else if(ADC_copy <= (6*tmp))
		{
			PORTB = 0x3F;
		}
		else if(ADC_copy <= (7*tmp))
		{
			PORTB = 0x7F;
		}
		else
		{
			PORTB = 0xFF; 
		}
    }
}
