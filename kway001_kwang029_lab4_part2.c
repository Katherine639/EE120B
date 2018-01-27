#include <avr/io.h>
#include "io.c"
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1=0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum States {wait, buttonInc, buttonDec, reset} state;
unsigned char counter = 1;
unsigned char value = 7;


void Tick() {
	unsigned char buttonI = (~PINA & 0x01);
	unsigned char buttonD = (~PINA & 0x02);
	
	
	switch(state) {
		case wait:
		if (buttonD)
		{
			if (value > 0)
			value--;
			PORTB = value;
			state = buttonDec;
		}
		else if (buttonI)
		{
			if (value < 9)
			value++;
			PORTB = value;
			state = buttonInc;
		}
		break;
		case buttonDec:
		if (!buttonD)
		{

			state = wait;
		}
		else if (buttonI)
		{
			state = reset;
		}
		else
		{
			//counter++;
			//counter%=50;
			//if (counter == 0 && value > 0)
			//{
			//value--;
			//state =
			//}
		}
		//PORTB = value;
		break;
		case buttonInc:
		if (!buttonI)
		{
			state = wait;
		}
		else if (buttonD)
		{
			state = reset;
		}
		else
		{
			//counter++;
			//counter%=50;
			//if (counter == 0 && value < 9)
			//{
			//value++;
			//}
		}
		//PORTB = value;
		break;
		case reset:
		value = 0;
		if (!buttonD && !buttonI)
		state = wait;
		PORTB = 0;
		break;
		default:
		break;
	}

}

int main()
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	PORTB = 7;
	while(1){
		Tick();
	}
}
