
#include <msp430.h>
#include "delay.h"
void gsm_on()
{
    delay_ms(2000);     //delay 2 sec
    P2DIR |= BIT7;      //set 2.7 direction
    P2OUT &=~BIT7;      // on gsm
    delay_ms(2000);     //delay 2 sec
    P2OUT |= BIT7;      // off gsm
    delay_ms(10000);    //delay 10 sec
}

