#include <msp430.h> 
#include "motor.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	

	while (1){
		moveForward();
		__delay_cycles(1000000);
		moveBackward();
		__delay_cycles(1000000);















	}
}
