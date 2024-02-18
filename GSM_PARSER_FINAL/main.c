
#include <msp430.h>
#include<string.h>
#include "fsm.h"
#include "parsing.h"
#include "circular_buff.h"
#include "clock_conf.h"
#include "delay.h"
#include "uart.h"
#include "gsm_on.h"

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    GPIO_PORT();
    ConfigureClockSystem();
    gsm_on();
    UART_INIT();
    __enable_interrupt();  // Enable global interrupts
    cbuff_init(&buffer);

    fsm();
    while(1);
}
