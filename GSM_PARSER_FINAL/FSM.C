#include "delay.h"
#include "parsing.h"
#include "uart.h"
#include<string.h>

typedef enum
{
    IDLE_STATE, AT_SEND, AT_CGSN, AT_CGMR, AT_CPIN, AT_CIMI,
    AT_CSQ, AT_CREG, AT_CGATT, AT_CGDCONT, AT_XIIC_1, AT_XIIC,
    AT_MQTTCONNPARAM, AT_MQTTWILLPARAM, AT_MQTTCONN, AT_MQTTSUB,
    AT_MQTTPUB, AT_MQTTSTATE, AT_MQTTDISCONN
} State;
int count=0;
State currentState = IDLE_STATE;
char arr[50];
void fsm()
{
    switch(currentState)
    {
    case IDLE_STATE:
            currentState=AT_SEND;
    case AT_SEND:
            UART_SendString("AT\r");
            delay_ms(2000);
            parseIncomingData();
            if(strcmp(arr, "OK") == 0 )
            {
                currentState = AT_CGSN;
            }
            else if(strcmp(arr, "ERROR") == 0 )
            {
                if(count<3)
                {
                    currentState=IDLE_STATE;
                    count++;
                }
                currentState = IDLE_STATE;
            }
    case AT_CGSN:
            UART_SendString("AT+CGSN\r");
            delay_ms(2000);
            parseIncomingData();
            if(strcmp(arr, "OK") == 0 )
            {
                currentState = AT_CGMR;
            }
    case AT_CGMR:
            UART_SendString("AT+CGMR\r");
            delay_ms(2000);
            parseIncomingData();
            if(strcmp(arr, "OK") == 0 )
            {
                currentState = AT_CPIN;
            }
    case AT_CPIN:
            UART_SendString("AT+CPIN?\r");
            delay_ms(2000);
            parseIncomingData();
            if(strcmp(arr, "OK") == 0 )
            {
                currentState = AT_CIMI;
            }
            else if(strcmp(arr, "ERROR") == 0 )
            {
                if(count<15)
                {
                   currentState=AT_CPIN;
                   count++;
                }
                else
                {
                currentState = IDLE_STATE;
                }
            }
    case AT_CIMI:
            UART_SendString("AT+CIMI\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_CSQ;
    case AT_CSQ:
            UART_SendString("AT+CSQ\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_CREG;
    case AT_CREG:
            UART_SendString("AT+CREG?\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_CGATT;
    case AT_CGATT:
            UART_SendString("AT+CGATT?\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_CGDCONT;
    case AT_CGDCONT:
            UART_SendString("AT+CGDCONT=1,\"IP\",\"bsnlnet\"\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_XIIC_1;
    case AT_XIIC_1:
            UART_SendString("AT+XIIC=1\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_XIIC;
    case AT_XIIC:
            UART_SendString("AT+XIIC?\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_MQTTCONNPARAM;
    case AT_MQTTCONNPARAM:
            UART_SendString("AT+MQTTCONNPARAM=\"1883\",\"dev\",\"dev@1234\"\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_MQTTWILLPARAM;
    case AT_MQTTWILLPARAM:
            UART_SendString("AT+MQTTWILLPARAM=0,1,\"hello\",byby\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_MQTTCONN;
    case AT_MQTTCONN:
            UART_SendString("AT+MQTTCONN=\"mqtt.chargebots.in:1883\",0,60\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_MQTTSUB;
    case AT_MQTTSUB:
            UART_SendString("AT+MQTTSUB=\"hello\",1\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_MQTTPUB;
    case AT_MQTTPUB:
            UART_SendString("AT+MQTTPUB=0,1,\"hello\",15523\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_MQTTSTATE;
    case AT_MQTTSTATE:
            UART_SendString("AT+MQTTSTATE?\r");
            delay_ms(2000);
            parseIncomingData();
            currentState=AT_MQTTDISCONN;
    case AT_MQTTDISCONN:
            UART_SendString("AT+MQTTDISCONN\r");
            delay_ms(2000);
            break;
    }
}







