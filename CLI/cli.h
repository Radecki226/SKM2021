/**
 *This header contains the API for CLI application 
 *
 *The project has benn prepared by P.Radecki, A.Król and L.Wisniewska.
 *The project aim is to implement CLI to communicate between PC and STM32 MCU
 *
 */
/*INCLUDES*/
#include "stdbool.h"
#include "stm32f3xx_hal.h"

/**
 *Structure defining receive buffer
 *
 *Buffer is organised as follows:
 *
 *->buffer is char* array containing the data
 *->capacity indicates maximal number of chars stored in the buffer
 *->count is current number of chars in the buffer, it also indicates the address of the next write 
 *->full flag indicates whether the buffer is full, if full == true it is impossible to write to buffer
*/
typedef struct{
	char* buffer;
	size_t capacity;
	int count;
	bool full;
}ReceiveBuffer;



typedef struct {
	int counter;
	char *array;
	size_t size;
}Monitor;







/*Initialize buffer with array of particular size*/
void ReceiveBuffer_Init(ReceiveBuffer *receiveBuffer, char *dataBuffer, size_t dataBufferSize );

/*Set all elements of buffer to 0*/
void ReceiveBuffer_Clear(ReceiveBuffer *receiveBuffer);

/*Put char into the next position and increment counter. If buffer is full returns false, otherwise true*/
bool ReceiveBuffer_PutChar(ReceiveBuffer *receiveBuffer, char c);

/*Delete last character and decrement counter. If buffer is empty returns false, otherwise true*/
bool ReceiveBuffer_Backspace(ReceiveBuffer *receiveBuffer);

/*Executes command according to data string and reply to uart*/
void CLI_ExecuteCommand(char* data,UART_HandleTypeDef huart, Monitor *monitor);
	
/*API for command line, this function defines interface*/
void CLI_CommandLine(uint8_t* myRxData,ReceiveBuffer *receiveBuffer,UART_HandleTypeDef huart, Monitor *monitor);

/*Function initializing monitor*/
void Monitor_Init(Monitor *monitor, char* data, size_t dataSize);

/*Function responsible for adding data to monitor*/
bool Monitor_Add(Monitor *monitor, char* data, size_t dataSize);

/*Function responsible for clearing monitor array*/
void Monitor_Clear(Monitor *monitor);




