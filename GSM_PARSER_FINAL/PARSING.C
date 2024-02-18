#include "circular_buff.h"
#include<string.h>

#define BUFFER_SIZE 50
#define MAX_MESSAGE_SIZE 50
#define NUM_VALID_RESPONSES 15

#define NUMBER_OF_COMMANDS 40 // Update according to your actual number of commands

void processCompleteMessage();

// Structure to hold command-response mappings
typedef struct
{
    const char* expectedResponsePrefix;
    void (*responseHandler)(const char*);
} CommandResponseMapping;

// Declaration of command-response mappings
CommandResponseMapping commandResponseMappings[NUMBER_OF_COMMANDS];

/*const char* validResponses[NUM_VALID_RESPONSES] = {"AT", "OK", "ERROR", "AT+CGSN", "AT+CGMR","AT+CPIN?", NULL};
void handleAT_OKResponse(const char* response)
{
    int i;
    for ( i = 0; i < NUM_VALID_RESPONSES; i++)
    {
        if (validResponses[i] == NULL)
        {
            break; // End of validResponses list
        }
        if (strcmp(response, validResponses[i]) == 0)
        {
            return;
        }
    }
    // Response is not valid, handle appropriately
}*/

void handleAT_OKResponse(const char* response)
{
    if(strcmp(response, "AT") == 0 || strcmp(response, "OK") == 0 ||strcmp(response, "ERROR") == 0 || strcmp(response, "AT+CGSN") == 0 || strcmp(response, "AT+CPIN?") == 0 || strcmp(response, "AT") == 0)
    {
        return;
    }
}

void handleResponse(const char* response)
{
    if((strncmp(response, "+CGSN:", strlen("+CGSN:")) == 0) || (strncmp(response, "+CGMR:", strlen("+CGMR:")) == 0) || (strncmp(response, "+CPIN:", strlen("+CPIN:")) == 0))
        {
            return;
        }
}
void initializeCommandResponseMappings()
{
    // Example command-response mappings
    commandResponseMappings[0].expectedResponsePrefix = "AT";
    commandResponseMappings[0].responseHandler = handleAT_OKResponse;
    commandResponseMappings[1].expectedResponsePrefix = "OK";
    commandResponseMappings[1].responseHandler = handleAT_OKResponse;
    commandResponseMappings[2].expectedResponsePrefix = "ERROR";
    commandResponseMappings[2].responseHandler = handleAT_OKResponse;

    commandResponseMappings[3].expectedResponsePrefix = "AT+CGSN";
    commandResponseMappings[3].responseHandler = handleAT_OKResponse;
    commandResponseMappings[4].expectedResponsePrefix = "+CGSN:";
    commandResponseMappings[4].responseHandler = handleResponse;

    commandResponseMappings[5].expectedResponsePrefix = "AT+CGMR";
    commandResponseMappings[5].responseHandler = handleAT_OKResponse;
    commandResponseMappings[6].expectedResponsePrefix = "+CGMR:";
    commandResponseMappings[6].responseHandler = handleResponse;

    commandResponseMappings[7].expectedResponsePrefix = "AT+CPIN?";
    commandResponseMappings[7].responseHandler = handleAT_OKResponse;
    commandResponseMappings[8].expectedResponsePrefix = "+CPIN:";
    commandResponseMappings[9].responseHandler = handleResponse;

    commandResponseMappings[7].expectedResponsePrefix = "AT+CIMI";
    commandResponseMappings[7].responseHandler = handleAT_OKResponse;



}
extern char arr[50];
void parseIncomingData()
{
    static char message[MAX_MESSAGE_SIZE];
     int messageIndex = 0;
    char data;

    while (!isBufferEmpty(&buffer))
    {
        data = readFromBuffer(&buffer);

        if (data == '\r' || data == '\n')
        {
              message[messageIndex] = '\0';   // Null-terminate the message string

        if (messageIndex > 0)    // Process the complete message
        {
             processCompleteMessage(message);
             strcpy(arr,message);
             //return message;
        }
          messageIndex = 0;  // Reset message buffer for next message
        }
        else
         {
         if (messageIndex < MAX_MESSAGE_SIZE - 1)   // Append character to message buffer if not at max size
         {
            message[messageIndex++] = data;
         }
         else
         {
            messageIndex = 0;  // Buffer overflow: discard excess data
         }
          }
    }
}

void processCompleteMessage(const char* message)
{
    int i;
    initializeCommandResponseMappings();
    // Iterate through command-response mappings to find a match
    for ( i = 0; i < NUMBER_OF_COMMANDS; i++)
    {
        if (strncmp(message, commandResponseMappings[i].expectedResponsePrefix, strlen(commandResponseMappings[i].expectedResponsePrefix)) == 0)
        {
            commandResponseMappings[i].responseHandler(message);
            return;
        }
    }
}
