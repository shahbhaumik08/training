
#include <msp430.h>
void delay_ms(unsigned int ms)
{
    TA0CTL = TASSEL_1 | MC_1;        // Use ACLK as the clock source, Up mode
    TA0CCR0 = 32768 / 1000 * ms;     // Set the period for the desired delay

    while (!(TA0CTL & TAIFG));       // Wait for Timer_A to reach the desired count

    TA0CTL = 0;                      // Reset Timer_A and clear interrupt flag
    TA0CTL |= TACLR;                  // Clear Timer_A
}

