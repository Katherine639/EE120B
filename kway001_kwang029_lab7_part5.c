#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
void TimerOn()
{
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff()
{
	TCCR1B = 0x00;
}
void TimerISR()
{
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0)
	{
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}



enum States {Start, INIT, MATH, WAIT, PAUSE, RESET}state;
void Tick();	
unsigned char i = 0x00;
unsigned char cnt = 0x00;
unsigned char time = 0x00;

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	
	TimerSet(25);
	TimerOn();
	state = Start;
    while(1)
    {
		Tick();
        while (!TimerFlag);
        TimerFlag = 0;
    }
}

void Tick()
{
	switch(state) //Transistions
	{
		case Start:
		{
			PORTB = 0x00;
			state = INIT;
			break;
		}
		
		case INIT:
		{
			if((~PINA & 0x03) == 0x03)
			{
				state = RESET; break;
			}
			else if(((~PINA & 0x03) == 0x01) || ((~PINA & 0x03) == 0x02))
			{
				state = MATH; break;
			}
			else
			{
				state = WAIT; break;
			}
		}
		
		case MATH:
		{
			if(time >= 3)
			{
				cnt = 8;
			}
			state = WAIT;
			break;
		}
		
		case WAIT:
		{
			if((~PINA & 0x03) == 0x03)
			{
				state = RESET; break;
			}
			else if(((~PINA & 0x03) == 0x01) || ((~PINA & 0x03) == 0x02))
			{
				state = PAUSE; break;
			}
			else
			{
				state = INIT; break;
			}
		}
		
		case PAUSE:
		{
			if(i <= cnt)
			{
				state = PAUSE; break;
			}
			else
			{
				i = 0; 
				++time;
				state = MATH;
				break;
			}
		}
		
		case RESET:
		{
			if((~PINA & 0x03) == 0x00)
			{
				state = INIT; break;
			}
			else
			{
				state = RESET; break;
			}
		}
		
		default:
			break;
	}
	switch(state) //state actions
	{
		case Start:
			break;
			
		case INIT:
		{
			cnt = 32;
			time = 0;
			i = 0;
			break;
		}
		
		case MATH:
		{
			if((~PINA & 0x03) == 0x01)
			{
				if(PORTB >= 9)
				{
					PORTB = 0x09;
				}
				else
				{
					++PORTB;
				}
				break;
			}
			else if((~PINA & 0x03) == 0x02)
			{
				if(PORTB <= 0)
				{
					PORTB = 0x00;
				}
				else
				{
					--PORTB;
				}
				break;
			}
			else
			{
				break;
			}
		}
		
		case WAIT:
			break;
			
		case PAUSE:
			++i;
			break;
			
		case RESET:
			PORTB = 0x00;
			break;
			
			default:
				break;
	}
}
