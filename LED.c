int LED_display_house() {
	if(song_select > 0){
		for(int i = 0; i < 8 ;i++){
			for(int j = 0; j < 8; j++){
				
				if (house[i][j] != 0){
					if( i == 0)
					{
						row_sel = 0x80;
					}
					else if( i == 1)
					{
						row_sel = 0x40;
					}
					else if( i == 2)
					{
						row_sel = 0x20;
					}
					else if( i == 3)
					{
						row_sel = 0x10;
					}
					else if( i == 4)
					{
						row_sel = 0x08;
					}
					else if( i == 5)
					{
						row_sel = 0x04;
					}
					else if( i == 6)
					{
						row_sel = 0x02;
					}
					else if( i == 7)
					{
						row_sel = 0x01;
					}
					
					
					if( j == 0)
					{
						column_sel = 0x80;
					}
					else if( j == 1)
					{
						column_sel = 0x40;
					}
					else if( j == 2)
					{
						column_sel = 0x20;
					}
					else if( j == 3)
					{
						column_sel = 0x10;
					}
					else if( j == 4)
					{
						column_sel = 0x08;
					}
					else if( j == 5)
					{
						column_sel = 0x04;
					}
					else if( j == 6)
					{
						column_sel = 0x02;
					}
					else if( j == 7)
					{
						column_sel = 0x01;
					}
					PORTA = row_sel;
					PORTC = (~column_sel);
					
					
				}
				
			}
			row_sel = 0;
			column_sel = 0;
		}
	}
}
