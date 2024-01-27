#include <msp430.h> 
void GPIO_PORT()
{
    P1DIR=0XFF;
    P1OUT=0X00;
    P1REN=0X00;
}

void ConfigureClockSystem()
{
    __bis_SR_register(SCG0);                        // Disable FLL control loop
    CSCTL3 |= SELREF__REFOCLK;                      // Set REFOCLK as the reference clock for FLL
    CSCTL1 = DCOFTRIMEN | DCOFTRIM0 | DCOFTRIM1 | DCORSEL_4;    // Set DCO frequency range to 8MHz
    CSCTL2 = FLLD_0 + 487;                          // Set FLLD = 0, FLLN = 244 for 8MHz//16mhz
    __delay_cycles(3);
    __bic_SR_register(SCG0);                        // Enable FLL control loop

    CSCTL4 = SELMS__DCOCLKDIV | SELA__REFOCLK;
}
void UART_INIT()
{
    //configure UART PINS
    P1SEL0 |= BIT4;  //pin 1.4 tx
    P1SEL1 &= ~ BIT4;

    // Configure UART module
        UCA0CTLW0 = UCSWRST;                    // Put UART in reset
        UCA0CTLW0 |= UCSSEL__SMCLK;             // Select SMCLK as the clock source

        // Set the baud rate to 104 (adjust BRW and other settings accordingly)
        UCA0BRW = 104;                          // Set the BRW value for 9600 baud rate (16MHz / 9600)
        UCA0MCTLW = 0xD600  | UCBRF_2 | UCOS16;      // Modulation UCBRSx = 0xd600, UCBRFx = 2, UCOS16

        UCA0CTLW0 &= ~UCSWRST;                  // Release UART from reset
}
void UART_SendChar(char data)
{
    while (!(UCA0IFG & UCTXIFG));           // Wait until the transmit buffer is ready
    UCA0TXBUF = data;                       // Send the character
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	PM5CTL0 &=~LOCKLPM5;   //DISABLE THE GPIO POWER ON DEFAULT HHIGH IMPEDANCE MODE TO ACTIVATE
	 GPIO_PORT();
	 ConfigureClockSystem();
	 UART_INIT();

	 while(1)
	 {
	 UART_SendChar('C');
	 UART_SendChar('h');
	     //UCA0TXBUF='A';
	     __delay_cycles(5000000);
	 }
}



