/*
 * motor.c
 *
 *  Created on: Nov 20, 2013
 *      Author: C15Craig.ODaniel
 */

#include <msp430.h>
#include "motor.h"


void createLeftForwardPulse()
{
	    TA1CTL &= ~(MC1|MC0);            // stop timer A1

	    TA1CTL |= TACLR;                // clear timer A1

	    TA1CTL |= TASSEL1;           // configure for SMCLK

	    TA1CCR0 = 100;                // set signal period to 100 clock cycles (~100 microseconds)
	    TA1CCR1 = 50;                // set duty cycle to 50/100 (50%)

	    TA1CCTL1 |= OUTMOD_7;        // set TACCTL1 to Reset / Set mode
	    TA1CCTL0 |= OUTMOD_5;

	    TA1CTL |= MC0;                // count up


	    }
void createLeftBackwardPulse()
{
	    TA1CTL &= ~(MC1|MC0);            // stop timer A1

	    TA1CTL |= TACLR;                // clear timer A1

	    TA1CTL |= TASSEL1;           // configure for SMCLK

	    TA1CCR0 = 100;                // set signal period to 100 clock cycles (~100 microseconds)
	    TA1CCR1 = 0;                // set duty cycle to 0/100 (00%)

	    TA1CCTL0 |= OUTMOD_7;        // set TACCTL0 to Reset MODE
	    TA1CCTL1 |= OUTMOD_4;

	    TA1CTL |= MC0;                // count up


	    }

void createRightForwardPulse()
{
    TA0CTL &= ~(MC1|MC0);            // stop timer A0

    TA0CTL |= TACLR;                // clear timer A0

    TA0CTL |= TASSEL1;           // configure for SMCLK

    TA0CCR0 = 100;                // set signal period to 100 clock cycles (~100 microseconds)
    TA0CCR1 = 50;                // set duty cycle to 50/100 (50%)

    TA0CCTL1 |= OUTMOD_7;        // set TACCTL1 to Reset / Set mode
    TA0CCTL0 |= OUTMOD_5;

    TA0CTL |= MC0;                // count up

}

void createRightBackwardPulse()
{
    TA0CTL &= ~(MC1|MC0);            // stop timer A0

    TA0CTL |= TACLR;                // clear timer A0

    TA0CTL |= TASSEL1;           // configure for SMCLK

    TA0CCR0 = 100;                // set signal period to 100 clock cycles (~100 microseconds)
    TA0CCR1 = 0;                // set duty cycle to 50/100 (50%)

    TA0CCTL0 |= OUTMOD_7;        // set TACCTL0 to Reset MODE
    TA0CCTL1 |= OUTMOD_4;

    TA0CTL |= MC0;                // count up

}




void moveRightWheelBackward(){
	P1DIR |= BIT1;            // TA0CCR0 on P1.1
	P1SEL |= BIT1;                // TA0CCR0 on P1.1

	createRightBackwardPulse();

}

void moveRightWheelForward(){
	P1DIR |= BIT2;            // TA0CCR1 on P1.2
	P1SEL |= BIT2;                // TA0CCR1 on P1.2
//	P1OUT &= ~BIT1;
	createRightForwardPulse();

}

void moveLeftWheelForward(){
	P2DIR |= BIT1;                // TA1CCR1 on P2.1
	P2SEL |= BIT1;                // TA1CCR1 on P2.1
//	P2OUT &= ~BIT0;				// Clear P2.0
	createLeftForwardPulse();

}

void moveLeftWheelBackward(){
	P2DIR |= BIT0;                // TA1CCR0 on P2.0
	P2SEL |= BIT0;                // TA1CCR0 on P2.0
//	P2OUT &= ~BIT2;				// Clear P2.2
	createLeftBackwardPulse();

}

void moveForward(){
	moveRightWheelForward();
	moveLeftWheelForward();
}

void moveBackward(){
	moveRightWheelBackward();
	moveLeftWheelBackward();
}

void turnLeft(){
	moveRightWheelForward();
	moveLeftWheelBackward();
}

void turnRight(){
	moveRightWheelBackward();
	moveLeftWheelForward();
}

void stopLeft(){
	P1OUT &= ~BIT2|~BIT1;
}

void stopRight(){
	P2OUT &= ~BIT0|~BIT1;


}

void stopMoving(){
	stopRight();
	stopLeft();
}


