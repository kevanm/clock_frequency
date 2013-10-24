#include <msp430.h> 
#include "lcd.h"
/*
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    char string[] = {'E','C','E',' ','3', '8', '2',' ','i','s',' ','m','y',' ','f','a','v','o','r','i','t','e',' ','c','l','a','s','s','!',' ',' '};
	char string2[] = {'B','a','n','a','n','a',' ','p','h','o','n','e',' ',' '};
    char message1[] = {'B','u','t','t','o','n',' ','1',' ',' ',' '};
    char message2[] = {'B','u','t','t','o','n',' ','2',' ',' ',' '};
    char message3[] = {'B','u','t','t','o','n',' ','3',' ',' ',' '};
    char message[] = {'M','e','s','s','a','g','e','?'};
    char button[] = {'P','r','e','s','s','1','2','3'};

    initSPI();
	LCDinit();
	LCDclear();

	 configureP1PinAsButton(BIT1|BIT2|BIT3);         // configure pins 1, 2, and 3 as buttons
     P1DIR |= BIT0|BIT6;                    // set launchpad LEDs to output


	while (1)
	{
         LCDtop();
         writeString( message, 8 );
         LCDbottom();
         writeString( button, 8 );

		 char buttons[] = {BIT1, BIT2, BIT3};
		 char pressedButton = pollP1Buttons(buttons, 3);

         switch (pressedButton)
         {
            case BIT1:
            	P1OUT ^= BIT0|BIT6;
                waitForP1ButtonRelease(BIT1);

        		while(1)
        		{
                LCDtop();
        		writeString( string, 31 );
        		LCDbottom();
        		writeString( message1, 11 );


        		scrollString( string, 31 );
        		scrollString( message1, 11 );
        		_delay_cycles(250000);
        		}
            break;
            case BIT2:

            	P1OUT ^= BIT0|BIT6;
                waitForP1ButtonRelease(BIT2);

                while(1)
                {
        		LCDtop();
        		writeString( string, 31 );
        		LCDbottom();
        		writeString( message2, 11 );


        		scrollString( string, 31 );
        		scrollString( message2, 11 );
        		_delay_cycles(250000);
                }
            break;
            case BIT3:
                // toggle LEDs and wait for release
            	P1OUT ^= BIT0|BIT6;
                waitForP1ButtonRelease(BIT3);

                while(1)
                {
                LCDtop();
        		writeString( string, 31 );
        		LCDbottom();
        		writeString( message3, 11 );


        		scrollString( string, 31 );
        		scrollString( message3, 11 );
        		_delay_cycles(250000);
                }
            break;
         }




	}


	//
	//    while (1) {
	//
	//    }
}
