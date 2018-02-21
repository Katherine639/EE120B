#include <avr/io.h>

void set_PWM(double frequency);
void PWM_off();
void PWM_on();

void Tick();
enum States{Start, INC, DEC, INIT, WAIT, Toggle} state;
double array[9] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25, 0};
double temp =  0;
unsigned char bottom = 0x00;
unsigned char top = 0x07;
unsigned char position = 0x00;
unsigned char clicker = 0x00;
unsigned char tmp = 0x00;

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = Start;
	PWM_on();
	clicker = 1;
	
	while(1)
	{
		Tick();
	}
}

void Tick()
{
	switch(state) // transitions
	{
		case Start:
		{
			state = INIT;
			break;
		}
		case INIT:
		{
			if((~PINA & 0x07) == 0x01)
			{
				state = INC;
				break;
			}
			else if((~PINA & 0x07) == 0x02)
			{
				state = DEC;
				break;
			}
			else if((~PINA & 0x07) == 0x04)
			{
				state = Toggle;
				break;
			}
			else
			{
				state = INIT;
				break;
			}
		}
		case INC:
		{
			temp = array[position];
			state = WAIT;
			break;
		}
		case DEC:
		{
			temp = array[position];
			state = WAIT;
			break;
		}
		case WAIT:
		{
			if((~PINA & 0x07) == 0x00)
			{
				state = INIT;
				break;
			}
			else
			{
				state = WAIT;
				break;
			}
		}
		case Toggle: 
		{
			state = WAIT;
			break;
		}
		default:
			break;
	}
	switch(state) // state actions
	{
		case Start:
			break;
		case INIT:
		{
			break;
		}
		case INC:
		{
			if((position + 1) > top)
			{
				position = top;
				break;
			}
			else
			{
				++position;
				break;
			}
		}
		case DEC:
		{
			if((position - 1) < bottom)
			{
				position = bottom;
				break;
			}
			else
			{
				--position;
				break;
			}
		}
		case WAIT:
		{
			temp = array[position];
			set_PWM(temp);
			break;
		}
		case Toggle:
		{		
			if(clicker)
			{
				PWM_off();
				tmp = position;
				position = 8;
				clicker = 0;
				break;
			}	
			else
			{
				PWM_on();
				position = tmp;
				clicker = 1;
				break;
			}
		}
		default:
		break;
		
	}
}
void set_PWM(double frequency) {
	
	
	// Keeps track of the currently set frequency
	// Will only update the registers when the frequency
	// changes, plays music uninterrupted.
	static double current_frequency;
	if (frequency != current_frequency) {

		if (!frequency) TCCR3B &= 0x08; //stops timer/counter
		else TCCR3B |= 0x03; // resumes/continues timer/counter
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) OCR3A = 0xFFFF;
		
		// prevents OCR3A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) OCR3A = 0x0000;
		
		// set OCR3A based on desired frequency
		else OCR3A = (short)(8000000 / (128 * frequency)) - 1;

		TCNT3 = 0; // resets counter
		current_frequency = frequency;
	}
}
void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB6 on compare match between counter and OCR3A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM32: When counter (TCNT3) matches OCR3A, reset counter
	// CS31 & CS30: Set a prescaler of 64
	set_PWM(0);
}
void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}
