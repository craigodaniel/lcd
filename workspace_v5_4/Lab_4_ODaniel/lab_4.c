/* Lab 4 ECE 382
 * Created By: Craig O'Daniel
 * 23OCT2013//25OCT2013
 */


#include <msp430.h> 
#include "lcd_lib.h"


int main(void){
	WDTCTL = WDTPW | WDTHOLD;
			char message[] = "ECE 382 is my favorite class! ";
			char message2[]= "Remember, remember the 5th of November. ";
			initSPI();
			LCDinit();
			LCDclear();
			cursorToLineOne();
			scrollString(message,message2);
			while (1){};
}





