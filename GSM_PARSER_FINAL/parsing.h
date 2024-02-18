
#ifndef PARSING_H_
#define PARSING_H_


#define NUMBER_OF_COMMANDS 8 // Update according to your actual number of commands
void parseIncomingData();
void processCompleteMessage();
void handleAT_OKResponse(const char* response);
void handleResponse(const char* response);
void initializeCommandResponseMappings();

#endif /* PARSING_H_ */
