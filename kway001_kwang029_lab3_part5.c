#include <avr/io.h>
enum States {Start, INIT, POUND, CHECK, WAIT, UNLOCK, LOCK, PAUSE} state;
void Tick();
unsigned char array[3] = {0x01, 0x02, 0x01};
unsigned char i = 0;

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x02;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	state = Start;
	
	while(1)
	{
		Tick();
	}
}


void Tick()
{
	switch(state) //Transitions
	{
		case Start:
		{
			state = INIT; break;
		}
		
		case INIT:
		{
			if((~PINA & 0x87) == 0x04)
			{
				state = POUND; break;
			}
			else if((~PINA & 0x87) == 0x80)
			{
				state = LOCK; break;
			}
			else
			{
				state = INIT; break;
			}
		}
		
		case POUND:
		{
			if((~PINA & 0x87) == 0x00)
			{
				state = CHECK; break;
			}
			else
			{
				state = POUND; break;
			}
		}
		
		case CHECK:
		{
			if((~PINA & 0x87) == array[i])
			{
				state = WAIT; break;
			}
			else if(i == 0x04)
			{
				state = UNLOCK; break;
			}
			else if((~PINA & 0x87) == 0x80)
			{
				state = LOCK; break;
			}
			else if((~PINA & 0x87) == 0x00)
			{
				state = CHECK; break;
			}
			else if((~PINA & 0x87) != array[i])
			{
				state = PAUSE; break;
			}
			break;
		}
		
		case PAUSE:
		{
			if((~PINA & 0x87) == 0x00)
			{
				state = CHECK; break;
			}
			else
			{
				state = INIT; break;
			}
		}
		
		case WAIT:
		{
			if((~PINA & 0x87) == 0x00)
			{
				++i;
				state = CHECK; break;
			}
			else
			{
				state = WAIT; break;
			}
		}
		case UNLOCK:
		{
			state = INIT; break;
		}
		case LOCK:
		{
			if((~PINA & 0x87) == 0x00)
			{
				state = INIT; break;
			}
			else
			{
				state = LOCK; break;
			}
		}
		
		default:
		break;
	}
	switch(state) // state actions
	{
		
		case Start:
		{
			PORTB = 0x02;
			break;
		}
		
		case INIT:
		{
			i = 0x00;
			PORTC = 0x01;
			break;
		}
		case POUND:
		{
			PORTC = 0x02;
			PORTD = i;
			break;
		}
		case CHECK:
		{
			PORTC = 0x03;
			PORTD = i;
			break;
		}
		case WAIT:
		{
			PORTC = 0x04;
			PORTD = i;
			break;
		}
		case UNLOCK:
		{
			PORTC = 0x05;
			if(PORTB == 0x01)
			{
				PORTB = 0x02; break;
			}
			else
			{
				PORTB = 0x01; break;
			}
		}
		case LOCK:
		{
			PORTC = 0x06;
			PORTB = 0x02;
			break;
		}
		
		default:
		break;
	}
}
