

#include <avr/io.h>
#include "bit.h"
#include "io.c"
#include <avr/interrupt.h>

// Returns '\0' if no key pressed, else returns char '1', '2', ... '9', 'A', ...
// If multiple keys pressed, returns leftmost-topmost one
// Keypad must be connected to port C
/* Keypad arrangement
        PC4 PC5 PC6 PC7
   col  1   2   3   4
row
PC0 1   1 | 2 | 3 | A
PC1 2   4 | 5 | 6 | B
PC2 3   7 | 8 | 9 | C
PC3 4   * | 0 | # | D
*/
unsigned char GetKeypadKey() {

	PORTC = 0xEF; // Enable col 4 with 0, disable others with 1s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	//if (GetBit(PINC,1) == 0 && GetBit(PINC,4) == 0) { return('');}
	if (GetBit(PINC,0)==0) { return('1'); }
	if (GetBit(PINC,1)==0) { return('4'); }
	if (GetBit(PINC,2)==0) { return('7'); }
	if (GetBit(PINC,3)==0) { return('*'); }
	//if (GetBit(PINC,0)==0 && GetBit(PINC,4) == 0) { return('2'); }

	// Check keys in col 2
	PORTC = 0xDF; // Enable col 5 with 0, disable others with 1s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	if (GetBit(PINC,0)==0) { return('2'); }
	if (GetBit(PINC,1)==0) { return('5'); }
	if (GetBit(PINC,2)==0) { return('8'); }
	if (GetBit(PINC,3)==0) { return('0'); }
	// ... *****FINISH*****

	// Check keys in col 3
	PORTC = 0xBF; // Enable col 6 with 0, disable others with 1s
	asm("nop"); // add a delay to allow PORTC to stabilize before checking
	// ... *****FINISH*****
	if (GetBit(PINC,0)==0) { return('3'); }
	if (GetBit(PINC,1)==0) { return('6'); }
	if (GetBit(PINC,2)==0) { return('9'); }
	if (GetBit(PINC,3)==0) { return('#'); }

	// Check keys in col 4	
	// ... *****FINISH*****
	PORTC = 0x0F;
	asm("nop");
	
	if (GetBit(PINC,0)==0) { return('A'); }
	if (GetBit(PINC,1)==0) { return('B'); }
	if (GetBit(PINC,2)==0) { return('C'); }
	if (GetBit(PINC,3)==0) { return('D'); }
		

	return('\0'); // default value

}

int main(void)
{
	unsigned char x;
	DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
	
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	
	LCD_init();
	LCD_ClearScreen();
	
	while(1) {
		x = GetKeypadKey();
		switch (x) {
			case '\0': ; break; // All 5 LEDs on
			case '1': LCD_DisplayString(1,"1"); break; // hex equivalent
			case '2': LCD_DisplayString(1,"2"); break;
			case '3': LCD_DisplayString(1,"3"); break;
			case '4': LCD_DisplayString(1,"4"); break;
			case '5': LCD_DisplayString(1,"5"); break;
			case '6': LCD_DisplayString(1,"6"); break;
			case '7': LCD_DisplayString(1,"7"); break;
			case '8': LCD_DisplayString(1,"8"); break;

			// . . . ***** FINISH *****
			case '9': LCD_DisplayString(1,"9"); break;
			case 'A': LCD_DisplayString(1,"A"); break;
			case 'B': LCD_DisplayString(1,"B"); break;
			case 'C': LCD_DisplayString(1,"C"); break;
			case 'D': LCD_DisplayString(1,"D"); break;
			case '*': LCD_DisplayString(1,"*"); break;
			case '0': LCD_DisplayString(1,"0"); break;
			case '#': LCD_DisplayString(1,"#"); break;
			default: PORTB = 0x1B; break; // Should never occur. Middle LED off.
		}
	}
}
