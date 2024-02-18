
#include <msp430.h>
#include "circular_buff.h"

void GPIO_PORT()
{
    P2DIR = BIT5 | BIT6;  // Set all P2 pins as outputs
       P2REN = BIT5 | BIT6;  // Enable pull-up/pull-down resistors on all P2 pins
       P2OUT = 0x00;  // Set all P2 output values to 0
       P2SEL0 |= BIT5 | BIT6;     // Set P2.5 as RXD and P2.6 as TXD
       P2SEL1 &= ~(BIT5 | BIT6);  // Clear corresponding P2SEL1 bits to select primary peripheral module function
}

void UART_INIT()
{
    //P1SEL0 |= BIT4|BIT5;    //set txd and rxd
    //P1SEL1 &=~(BIT4|BIT5);

    UCA1CTLW0 |=UCSWRST;  //put uart in reset
    UCA1CTLW0 |=UCSSEL__SMCLK;     //select smclk as the clock source

    UCA1BRW = 104;  //set bauderate 104 //9600
    UCA1MCTLW= 0xD600 | UCBRF_2 | UCOS16;    //configure modulation
    UCA1CTLW0 &=~UCSWRST;  //put uart in reset
    UCA1IE |= UCRXIE;
}

void UART_SendChar(char data)
{
    while (!(UCA1IFG & UCTXIFG));           // Wait until the transmit buffer is ready
    UCA1TXBUF = data;                       // Send the character
}

void UART_SendString(const char *str)
{
    while (*str != '\0')
    {
        UART_SendChar(*str);
        str++;
    }
}

#pragma vector = USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{

    buffer.data[buffer.head] = UCA1RXBUF;      // Store received character in buffer

    buffer.head = (buffer.head + 1) % BUFFER_SIZE;    // Update buffer head
}

