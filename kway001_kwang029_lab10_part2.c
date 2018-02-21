
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

enum States {a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,aa,bb,cc,dd,ee,ff,gg,hh,ii,jj,kk,ll,mm,nn,oo,pp,qq,rr,ss,tt,uu,vv,ww,xx,yy,zz, aaa, bbb} state;

void TimerSet(unsigned long M)
{
	_avr_timer_M =	M;
	_avr_timer_cntcurr  = _avr_timer_M;
}

unsigned char I;
unsigned long count;
void Tick()
{
	//I = (~PINB) & 0x01;
	
	switch(state){//CS120B is Legend... wait for it DARY
		case a:
			LCD_DisplayString(1,"CS120B is Legend");
			while(count < 500000){count++;}count = 0;
			state = b;
		case b:
			LCD_DisplayString(1,"S120B is Legend.");
			while(count < 500000){count++;}count = 0;
			state = c;
		case c:
			LCD_DisplayString(1,"120B is Legend..");
			while(count < 500000){count++;}count = 0;
			state = d;
		case d:
			LCD_DisplayString(1,"20B is Legend...");
			while(count < 500000){count++;}count = 0;
			state = e;
		case e:
			LCD_DisplayString(1,"0B is Legend...w");
			while(count < 500000){count++;}count = 0;
			state = f;
		case f:
			LCD_DisplayString(1,"B is Legend...wa");
			while(count < 500000){count++;}count = 0;
			state = g;
		case g:
			LCD_DisplayString(1," is Legend...wai");
			while(count < 500000){count++;}count = 0;
			state = h;
		case h:
			LCD_DisplayString(1,"is Legend...wait");
			while(count < 500000){count++;}count = 0;
			state = i;
		case i:
			LCD_DisplayString(1,"s Legend...wait ");
			while(count < 500000){count++;}count = 0;
			state = j;
		case j:
			LCD_DisplayString(1," Legend...wait f");
			while(count < 500000){count++;}count = 0;
			state = k;
		case k:
			LCD_DisplayString(1,"Legend...wait fo");
			while(count < 500000){count++;}count = 0;
			state = l;
		case l:
			LCD_DisplayString(1,"egend...wait for");
			while(count < 500000){count++;}count = 0;
			state = m;
		case m:
			LCD_DisplayString(1,"gend...wait for ");
			while(count < 500000){count++;}count = 0;
			state = n;
		case n:
			LCD_DisplayString(1,"end...wait for i");
			while(count < 500000){count++;}count = 0;
			state = o;
		case o:
			LCD_DisplayString(1,"nd...wait for it");
			while(count < 500000){count++;}count = 0;
			state = p;
		case p:
			LCD_DisplayString(1,"d...wait for it ");
			while(count < 500000){count++;}count = 0;
			state = q;
		case q:
			LCD_DisplayString(1,"...wait for it D");
			while(count < 500000){count++;}count = 0;
			state = r;
		case r:
			LCD_DisplayString(1,"..wait for it DA");
			while(count < 500000){count++;}count = 0;
			state = s;
		case s:
			LCD_DisplayString(1,".wait for it DAR");
			while(count < 500000){count++;}count = 0;
			state = t;
		case t:
			LCD_DisplayString(1,"wait for it DARY");
			while(count < 500000){count++;}count = 0;
			state = u;
		case u:
			LCD_DisplayString(1,"ait for it DARY!");
			while(count < 500000){count++;}count = 0;
			state = v;
		case v:
			LCD_DisplayString(1,"it for it DARY! ");
			while(count < 500000){count++;}count = 0;
			state = w;
		case w:
			LCD_DisplayString(1,"t for it DARY!  ");
			while(count < 500000){count++;}count = 0;
			state = x;
		case x:
			LCD_DisplayString(1," for it DARY!   ");
			while(count < 500000){count++;}count = 0;
			state = y;
		case y:
			LCD_DisplayString(1,"for it DARY!    ");
			while(count < 500000){count++;}count = 0;
			state = z;
		case z:
			LCD_DisplayString(1,"or it DARY!     ");
			while(count < 500000){count++;}count = 0;
			state = aa;
		case aa:
			LCD_DisplayString(1,"r it DARY!      ");
			while(count < 500000){count++;}count = 0;
			state = bb;
		case bb:
			LCD_DisplayString(1," it DARY!       ");
			while(count < 500000){count++;}count = 0;
			state = cc;
		case cc:
			LCD_DisplayString(1,"it DARY!        ");
			while(count < 500000){count++;}count = 0;
			state = dd;
		case dd:
			LCD_DisplayString(1,"t DARY!         ");
			while(count < 500000){count++;}count = 0;
			state = ee;
		case ee:
			LCD_DisplayString(1," DARY!          ");
			while(count < 500000){count++;}count = 0;
			state = ff;
		case ff:
			LCD_DisplayString(1,"DARY!           ");
			while(count < 500000){count++;}count = 0;
			state = gg;
		case gg:
			LCD_DisplayString(1,"ARY!            ");
			while(count < 500000){count++;}count = 0;
			state = hh;
		case hh:
			LCD_DisplayString(1,"RY!             ");
			while(count < 500000){count++;}count = 0;
			state = ii;
		case ii:
			LCD_DisplayString(1,"Y!              ");
			while(count < 500000){count++;}count = 0;
			state = jj;
		case jj:
			LCD_DisplayString(1,"!               ");
			while(count < 500000){count++;}count = 0;
			state = kk;
		case zz:
			LCD_DisplayString(1,"                ");
			while(count < 500000){count++;}count = 0;
			state = aaa;
		case aaa:
			LCD_DisplayString(1,"                ");
			while(count < 500000){count++;}count = 0;
			state = bbb;
		case bbb:
			LCD_DisplayString(1,"                ");
			while(count < 500000){count++;}count = 0;
			state = kk;
		case kk:
			LCD_DisplayString(1,"               C");
			while(count < 500000){count++;}count = 0;
			state = ll;
		case ll:
			LCD_DisplayString(1,"              CS");
			while(count < 500000){count++;}count = 0;
			state = mm;
		case mm:
			LCD_DisplayString(1,"             CS1");
			while(count < 500000){count++;}count = 0;
			state = nn;
		case nn:
			LCD_DisplayString(1,"            CS12");
			while(count < 500000){count++;}count = 0;
			state = oo;
		case oo:
			LCD_DisplayString(1,"           CS120");
			while(count < 500000){count++;}count = 0;
			state = pp;
		case pp:
			LCD_DisplayString(1,"          CS120B");
			while(count < 500000){count++;}count = 0;
			state = qq;
		case qq:
			LCD_DisplayString(1,"         CS120B ");
			while(count < 500000){count++;}count = 0;
			state = rr;
		case rr:
			LCD_DisplayString(1,"        CS120B i");
			while(count < 500000){count++;}count = 0;
			state = ss;
		case ss:
			LCD_DisplayString(1,"       CS120B is");
			while(count < 500000){count++;}count = 0;
			state = tt;
			case tt:
			LCD_DisplayString(1,"      CS120B is ");
			while(count < 500000){count++;}count = 0;
			state = uu;
		case uu:
			LCD_DisplayString(1,"     CS120B is L");
			while(count < 500000){count++;}count = 0;
			state = vv;
		case vv:
			LCD_DisplayString(1,"    CS120B is Le");
			while(count < 500000){count++;}count = 0;
			state = ww;
		case ww:
			LCD_DisplayString(1,"   CS120B is Leg");
			while(count < 500000){count++;}count = 0;
			state = xx;
		case xx:
			LCD_DisplayString(1,"  CS120B is Lege");
			while(count < 500000){count++;}count = 0;
			state = yy;
		case yy:
			LCD_DisplayString(1," CS120B is Legen");
			while(count < 500000){count++;}count = 0;
			state = a;
		
	}
	
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0x00; PORTB = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	LCD_init();
	
	TimerSet(1);
	TimerOn();
	
	count = 0;
	
	LCD_ClearScreen();
	//LCD_Cursor(1);
	LCD_DisplayString(1,"A");
	//LCD_DisplayString(1, "Hello World");
	while(1)
	{
			
			
			//LCD_DisplayString(1, "Hello World");
		Tick();
		//LCD_Cursor(1);
		//LCD_WriteData( 1 + '0');
		while (!TimerFlag);
		TimerFlag = 0;
		//continue;
	}
}	
