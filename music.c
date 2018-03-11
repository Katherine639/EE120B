double TWINKLE[] = {NOTE_A4, NOTE_A4, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_FS5, NOTE_E5, 0, NOTE_D5, NOTE_D5, NOTE_CS5, NOTE_CS5, NOTE_B4, NOTE_B4, NOTE_A4};
double MARYLAMB[] = {NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, 0, NOTE_G4, NOTE_G4, NOTE_G4, 0, NOTE_A4, NOTE_C5, NOTE_C5, 0, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4};
double MCYD[] = {NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, 0, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_G4, 0, 0, NOTE_D4 /*?*/, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_E4,NOTE_D4, 0, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_G4};
double ODE[] = {NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, 0, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4};
unsigned char song_start = 0;



enum songPlay {initSong, play, check, play1, play2, play3, play4, off} stateSong;
unsigned int i;
void MUSIC_TICK(){
	switch(stateSong){
		case initSong:
			PWM_on();
			if(choice == 1) {
				song_start = 1;
				stateSong = play1;
				/*USART_Flush();
				if (USART_IsSendReady())
				{
					USART_Send(song_start);
				}*/
			}
			if(choice == 2) {
				song_start = 2;
				stateSong = play2;
				/*USART_Flush();
				if (USART_IsSendReady())
				{
					USART_Send(song_start);
				}*/
			}
			if(choice == 3) {
				song_start = 3; 
				stateSong = play3;
				/*USART_Flush();
				if (USART_IsSendReady())
				{
					USART_Send(song_start);
				}*/
			}
			if(choice == 4) {
				song_start = 4; 
				stateSong = play4;
				/*USART_Flush();
				if (USART_IsSendReady())
				{
					USART_Send(song_start);
				}*/
			}
			else stateSong = initSong;
		case play1:
			stateSong = check;
			break;
		case play2:
			stateSong = check;
			break;
		case play3:
			stateSong = check;
			break;
		case play4:
			stateSong = check;
			break;
		case check:
			if (i == (int)( sizeof(TWINKLE) / sizeof(TWINKLE[0])) || i == (int)( sizeof(TWINKLE) / sizeof(TWINKLE[0])) || i == (int)( sizeof(TWINKLE) / sizeof(TWINKLE[0])) ||i == (int)( sizeof(TWINKLE) / sizeof(TWINKLE[0])) )
			{
				i = 0;
				stateSong = off;
			}
			else
			{
				if(choice == 1) stateSong = play1;
				if(choice == 2) stateSong = play2;
				if(choice == 3) stateSong = play3;
				if(choice == 4) stateSong = play4;
			}
			break;
			case off:
				song_start = 0;
				choice = 0;
				PWM_off();
				USART_Flush();
				if (USART_IsSendReady())
				{
					USART_Send(song_start);
				}
				stateSong = initSong;
				break;
		default:
			stateSong = initSong;
			break;
	}
	switch(stateSong){
		case initSong:
			i = 0;
			break;
		case play1:
			set_PWM(TWINKLE[i]);
			if(i == (int)( sizeof(TWINKLE) / sizeof(TWINKLE[0])) ){
				//PWM_off();
				//stateSong = off;
			} else i++;
			break;
		case play2:
			set_PWM(MARYLAMB[i]);
			if(i == (int)( sizeof(MARYLAMB) / sizeof(MARYLAMB[0])) ){
				//PWM_off();
				//stateSong = off;
			} else i++;
			break;
		case play3:
			set_PWM(MCYD[i]);
			if(i == (int)( sizeof(MCYD) / sizeof(MCYD[0])) ){
				//PWM_off();
				//stateSong = off;
			} else i++;
			break;
		case play4:
			set_PWM(ODE[i]);
			if(i == (int)( sizeof(ODE) / sizeof(ODE[0])) ){
				//PWM_off();
				//stateSong = off;
			} else i++;
			break;
		
		case check: break;
		default: break;
	}
	
}
