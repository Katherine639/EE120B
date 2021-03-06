
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)


	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum States {one, twothree, twoone, three} state;
unsigned char PauseFlag = 0;


void oci(){
	switch(state){
		case one:
			PORTB = 0x01;
			state = twothree;
			break;
		case twothree:
			PORTB = 0x02;
			state = three;
			break;
		case twoone:
			PORTB = 0x02;
			state = one;
			break;
		case three:
			PORTB = 0x04;
			state = twoone;
			break;
	}
}

int main()
{
	DDRB = 0xFF; // Set port B to output
	PORTB = 0x00; // Init port B to 0s
	DDRA = 0x00;
	PORTA = 0xFF;
	TimerSet(100);
	TimerOn();
	unsigned char buttonI;
	
	while(1) {
		buttonI = (~PINA & 0x01);
		
		if(buttonI == 0 && PauseFlag == 0){
			oci();
		}
		else if(PauseFlag == 1 && buttonI == 1){
			state = one;
			PauseFlag = 0;
		}
		else{
			PauseFlag = 1;
		}
		
		
		// User code (i.e. synchSM calls)
		// Toggle PORTB; Temporary, bad programming style
		while (!TimerFlag);	// Wait 1 sec
		TimerFlag = 0;
		// Note: For the above a better style would use a synchSM with TickSM()
		// This example just illustrates the use of the ISR and flag
	}
}
