#include <avr/io.h>
enum States {Start, INIT, LIGHT, WAIT}state;
void Tick();

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	state = Start;
	while(1)
	{
		Tick();
	}
}

void Tick(){
	switch(state){//Transitions
		case Start:
		PORTC = 0x00;
		state = INIT;
		break;
		
		case INIT:
		if((~PINA & 0x01) == 0x01)
		{
			state = LIGHT; break;
		}
		else
		{
			state = INIT; break;
		}
		
		case LIGHT:
		state = WAIT;
		break;
		
		case WAIT:
		if((~PINA & 0x01) == 0x01)
		{
			state = WAIT; break;
		}
		else if((~PINA & 0x01) == 0x00)
		{
			state = INIT; break;
		}
		
		default:
		break;
	}
	switch(state){ //State actions
		case Start:
		break;
		
		case INIT:
		break;
		
		case LIGHT:
		if(PORTC == 0x00)
		{
			PORTC = 0x01; break;
		}
		else if(PORTC == 0x2A)
		{
			PORTC = 0x00; break;
		}
		else
		{
			PORTC = (PORTC << 1);
			if((PORTC & 0x04) == 0x04)
			{
				PORTC = PORTC | 0x01; break;
			}
			break;
		}
		
		case WAIT:
		break;
		
		default:
		break;
	}
	
}
