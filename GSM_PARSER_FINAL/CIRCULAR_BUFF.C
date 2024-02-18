
#define BUFFER_SIZE 50

typedef struct
{
    char data[BUFFER_SIZE];
    volatile unsigned int head;
    volatile unsigned int tail;
}CircularBuffer;

CircularBuffer buffer; // Declare a circular buffer instance

void cbuff_init(CircularBuffer *buffer)     //initialize head=0 and tail=0
{
    buffer->head = 0;
    buffer->tail = 0;
}

// Function to check if circular buffer is empty
int isBufferEmpty(CircularBuffer* buffer)
{
    return buffer->head == buffer->tail;
}

// Function to check if circular buffer is full
int isBufferFull(CircularBuffer* buffer)
{
    return (buffer->head + 1) % BUFFER_SIZE == buffer->tail;
}

// Function to read a character from the circular buffer
char readFromBuffer(CircularBuffer* buffer)
{
    char data = '\0';

    if (!isBufferEmpty(buffer))
    {
        data = buffer->data[buffer->tail];
        buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
    }
    return data;
}

// Function to write a character to the circular buffer
void writeToBuffer(CircularBuffer* buffer, char data)
{
    if (!isBufferFull(buffer))
    {
        buffer->data[buffer->head] = data;
        buffer->head = (buffer->head + 1) % BUFFER_SIZE;
    }
}


