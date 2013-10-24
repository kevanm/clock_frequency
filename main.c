#include <msp430.h> 
#include "lcd.h"
/*
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    char string[] = {'E','C','E',' ','3', '8', '2',' ','i','s',' ','m','y',' ','f','a','v','o','r','i','t','e',' ','c','l','a','s','s','!',' ',' '};
	char string2[] = {'B','a','n','a','n','a',' ','p','h','o','n','e',' ',' '};
    initSPI();
	LCDinit();
	LCDclear();



	while (1)
	{
		LCDtop();
		writeString( string, 31 );
		LCDbottom();
		writeString( string2, 14 );


		scrollString( string, 31 );
		scrollString( string2, 14 );
		_delay_cycles(250000);

	}


}
