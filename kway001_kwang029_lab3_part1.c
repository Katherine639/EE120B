#include <avr/io.h>
enum States {Start, INIT, TURN_OFF, WAIT1, TURN_ON, WAIT2}state;
void Tick();

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x01;
	state = Start;
	while(1)
	{
		Tick();
	}
}

void Tick(){
	switch(state){ //Transitions
		case Start:
		PORTB = 0x01;
		state = INIT;
		break;
		
		case INIT:
		if((~PINA & 0x01) == 0x01)
		{
			state = TURN_OFF; break;
		}
		else
		{
			state = INIT; break;
		}
		
		case TURN_OFF:
		if((~PINA & 0x01) == 0x00)
		{
			state = WAIT1; break;
		}
		else
		{
			state = TURN_OFF; break;
		}
		
		case WAIT1:
		if((~PINA & 0x01) == 0x01)
		{
			state = TURN_ON; break;
		}
		else
		{
			state = WAIT1; break;
		}
		
		case TURN_ON:
		if((~PINA & 0x01) == 0x00)
		{
			state = WAIT2; break;
		}
		else
		{
			state = TURN_ON; break;
		}
		
		case WAIT2:
		if((~PINA & 0x01) == 0x01)
		{
			state = TURN_OFF; break;
		}
		else
		{
			state = WAIT2; break;
		}
		
		default:
		break;
	}
	switch(state){ //State actions
		case Start:
		break;
		
		case INIT:
		PORTB = 0x01;
		break;
		
		case TURN_OFF:
		PORTB = 0x02;
		break;
		
		case WAIT1:
		break;
		
		case TURN_ON:
		PORTB = 0x01;
		break;
		
		case WAIT2:
		break;
		
		default:
		break;
	}
}
