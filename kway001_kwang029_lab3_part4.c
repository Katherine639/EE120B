#include <avr/io.h>
enum States {Start, INIT, POUND, WAIT, Y, LOCK, PAUSE}state;
void Tick();

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x02;
	DDRC = 0xFF; PORTC = 0x00;
	state = Start;
	while(1)
	{
		Tick();
	}
}

//Tick function written by Kent
//Fransisco helped with some of the transitions logic
void Tick(){
	switch(state){ //Transitions
		case Start:
		{
			state = INIT;
			break;
		}
		
		case INIT:
		if((~PINA & 0x04) == 0x04)
		{
			state = POUND; break;
		}
		else if ((~PINA & 0x80) == 0x80)
		{
			state = LOCK; break;
		}
		else
		{
			state = INIT; break;
		}
		
		case POUND:
		{
			state = WAIT; break;
		}
		
		case WAIT:
		{
			if(((~PINA & 0x02) == 0x02) && ((PORTB & 0x01) == 0x01))
			{
				state = LOCK; break;
			}
			else if((~PINA & 0x02) == 0x02)
			{
				state = Y; break;
			}
			else if((~PINA & 0x80) == 0x80)
			{
				state = LOCK; break;
			}
			else if((~PINA & 0x01) == 0x01)
			{
				state = INIT; break;
			}
			else
			{
				state = WAIT; break;
			}
		}
		
		
		case Y:
		{
			state = PAUSE; break;
		}
		
		case PAUSE:
		if((~PINA & 0x87) == 0x00)
		{
			state = INIT; break;
		}
		else
		{
			state = PAUSE; break;
		}
		
		case LOCK:
		if((~PINA & 0x00) == 0x00)
		{
			state = INIT; break;
		}
		else
		{
			state = LOCK; break;
		}
		
		default:
		break;
	}
	switch(state){ //State actions
		case Start:
		PORTB = 0x02;
		PORTC = 0x00;
		break;
		
		case INIT:
		PORTC = 0x01;
		break;
		
		case POUND:
		PORTC = 0x02;
		break;
		
		case WAIT:
		PORTC = 0x03;
		break;
		
		case Y:
		PORTC = 0x04;
		PORTB = 0x01;
		break;
		
		case PAUSE:
		PORTC = 0x05;
		break;
		
		case LOCK:
		PORTC = 0x06;
		PORTB = 0x02;
		break;
	}
	
}
