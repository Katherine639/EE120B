#include <avr/io.h>
#include "io.c"
#include <avr/interrupt.h>


volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;

unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks
void TimerOn()
{
	// AVR timer/counter controller register TCCR1
	// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TC	NT1 register will count at 125,000 ticks/s
	TCCR1B =0x0B;
	// AVR output compare register OCR1A.
	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1	ms has passed. Thus, we compare to 125.
	OCR1A=125;
	// AVR timer interrupt mask register
	// bit1: OCIE1A 	--	enables compare match interrupt
	TIMSK1 	=0x02;	//Initialize avr counter
	TCNT1=0;
	// TimerISR will be called every _avr_timer_cntcurr	milliseconds
	_avr_timer_cntcurr	=_avr_timer_M;
	//Enable global interrupts	:	0x80: 1000000
	SREG=0x80;
}

void TimerOff()
{
	// bit3bit1bit0=000: timer off
	TCCR1B 	=	0x00;
}
void TimerISR()
{
	TimerFlag=1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1
	//	(every 1 ms per TimerOn settings)
	// Count down to 0 rather than up to TOP	(	res	ults in a more	efficient comparison)
	_avr_timer_cntcurr--;
	if(_avr_timer_cntcurr == 0)
	{
		// Call the ISR that the user uses
		TimerISR();
		_avr_timer_cntcurr 	= _avr_timer_M;
	}
}

void TimerSet(unsigned long M)
{
	_avr_timer_M =	M;
	_avr_timer_cntcurr  = _avr_timer_M;
}

enum IC_states {IC_init, IC_wait, IC_Add_one, IC_Minus_one, IC_reset,IC_wait_fall} IC_state;
unsigned char B;
unsigned char I;
unsigned char D;
void Icrement_tick()
{
	I = (~PINA) & 0x01;
	D = (~PINA) & 0x02;
	switch(IC_state) //transitions
	{
		case IC_init:
		{
			IC_state = IC_wait;
			break;
		}
		
		case IC_wait_fall:
		{
			if(I && D)
			{
				IC_state = IC_reset;
			}
			else
			{
				IC_state = IC_wait;
			}
			
			break;
		}
		
		case IC_wait:
		{
			if(I && D)
			{
				IC_state = IC_reset;
			}
			else if (!I && D && (B > 0))
			{
				IC_state = IC_Minus_one;
				
			}
			else if (I && !D && (B < 9))
			{
				IC_state = IC_Add_one;
				
			}
			else
			{
				IC_state = IC_wait;
			}
			break;
		}
		
		case IC_Add_one:
		{
			if(I && D)
			{
				IC_state = IC_reset;
			}
			else
			{
				IC_state = IC_wait_fall;
			}
			break;
		}
		
		case IC_Minus_one:
		{
			if(I && D)
			{
				IC_state = IC_reset;
			}
			else
			{
				IC_state = IC_wait_fall;
			}
			break;
		}
		
		case IC_reset:
		{
			IC_state = IC_wait;
			break;
		}
		default:
		{
			IC_state = IC_init;
			break;
		}
	}
	switch(IC_state) //state actions
	{
		case IC_init:
		{
			B = 0;
			
			LCD_Cursor(1);
			//LCD_ClearScreen();
			//LCD_WriteData( B + '0' );
			//PORTC = 0x00;
			break;
		}
		
		/*case IC_wait_fall:
		{
			
			break;
		}*/
		
		
		case IC_wait:
		{
			//PORTC = B & 0x0F;
			//LCD_Cursor(1);
			//LCD_WriteData(B + '0');
			break;
		}
		
		case IC_Add_one:
		{
			
			
			B = B + 1;
			LCD_Cursor(1);
			//LCD_ClearScreen();
			LCD_WriteData(B + '0');
			//PORTC = (PORTC + 1) ;
			IC_state = IC_wait_fall;
			break;
		}
		
		case IC_Minus_one:
		{
			
			
			B = B - 1;
			LCD_Cursor(1);
			//LCD_ClearScreen();
			LCD_WriteData( B + '0' );
			//PORTC = (PORTC - 1) ;
			IC_state = IC_wait_fall;
			break;
		}
		
		case IC_reset:
		{
			
			B = 0;
			LCD_Cursor(1);
			//LCD_ClearScreen();
			LCD_WriteData( B + '0' );
			//PORTC = 0x00;
			break;
			
		}
		default:
		{
			break;
		}
	}
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	B = 0;
	IC_state = IC_init;
	LCD_init();
	
	TimerSet(1000);
	TimerOn();
	
	
	LCD_ClearScreen();
	LCD_Cursor(1);
	LCD_WriteData( B + '0' );
	//LCD_DisplayString(1, "Hello World");
	while(1)
	{
			
			
		Icrement_tick();
		while (!TimerFlag);
		TimerFlag = 0;
		//continue;
	}
}	
