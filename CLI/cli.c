/*INCLUDES*/
#include "cli.h"
#include "main.h"
#include "string.h"

/****************************************************GLOBAL VARIABLES*******************************************************************************/
char* ip = "192.168.1.1";
char* info = "Microcontroller: STM32L053\r\n"
			 "Series: NUCLEO";
char* help = "Available commands:\r\n"
								"ip - shows the IP address of the device\r\n"
								"info - shows information about the device\r\n"
								"status ??";


/**************************************************DEFINITIONS from cli.h header********************************************************************/
void ReceiveBuffer_Init(ReceiveBuffer *receiveBuffer, char *dataBuffer, size_t dataBufferSize ){
	receiveBuffer->buffer = dataBuffer;
	receiveBuffer->capacity = dataBufferSize;
	receiveBuffer->count = 0;
	receiveBuffer->full = false;
}
void ReceiveBuffer_Clear(ReceiveBuffer *receiveBuffer){

	for(size_t i=0; i < receiveBuffer->count; i++)
		receiveBuffer->buffer[i] = 0;
	receiveBuffer->count = 0;
	receiveBuffer->full = false;

}
bool ReceiveBuffer_PutChar(ReceiveBuffer *receiveBuffer, char c){
	if(receiveBuffer->full == true)
		return false;
	receiveBuffer->buffer[receiveBuffer->count] = c;
	receiveBuffer->count++;
	if(receiveBuffer->count == receiveBuffer->capacity)
		receiveBuffer->full = true;
	return true;
}
bool ReceiveBuffer_Backspace(ReceiveBuffer *receiveBuffer){
	if(receiveBuffer->count == 0)
		return false;
	receiveBuffer->buffer[receiveBuffer->count-1] = 0;
	receiveBuffer->count--;
	if(receiveBuffer->count < receiveBuffer->capacity)
		receiveBuffer->full = false;
	return true;
}

void CLI_ExecuteCommand(char* data,UART_HandleTypeDef huart){

		uint8_t terminator[] = {'\r','\n',0};
		char *unrecognizedCommand = "Unrecongnized Command";

		if(strcmp(data,"ip") == 0){
			HAL_UART_Transmit(&huart, (uint8_t*)ip, strlen(ip), 10);
			HAL_UART_Transmit(&huart,terminator,3,10);
		}
		else if(strcmp(data,"info") == 0){
			HAL_UART_Transmit(&huart, (uint8_t*)info, strlen(info), 10);
			HAL_UART_Transmit(&huart,terminator,3,10);
		}
		else if(strcmp(data,"help") == 0){
			HAL_UART_Transmit(&huart, (uint8_t*)help, strlen(help), 10);
			HAL_UART_Transmit(&huart,terminator,3,10);
		}
		else{
			HAL_UART_Transmit(&huart, (uint8_t*)unrecognizedCommand, strlen(unrecognizedCommand), 10);
			HAL_UART_Transmit(&huart,terminator,3,10);
		}
}


void CLI_CommandLine(uint8_t* myRxData,ReceiveBuffer *receiveBuffer,UART_HandleTypeDef huart){

	uint8_t currentChar = myRxData[0];
	uint8_t terminator[] = {'\r','\n',0};

	switch(currentChar){
		case 127:
			if(ReceiveBuffer_Backspace(receiveBuffer) == true)
				HAL_UART_Transmit(&huart ,myRxData, 1, 10);
			break;
		case '\r':
			HAL_UART_Transmit(&huart,terminator,3,10);
			CLI_ExecuteCommand(receiveBuffer->buffer, huart);
			HAL_UART_Transmit(&huart,terminator,3,10);
			ReceiveBuffer_Clear(receiveBuffer);
			break;
		default:
			if(ReceiveBuffer_PutChar(receiveBuffer, currentChar) == true)
					HAL_UART_Transmit(&huart, myRxData, 1, 10);
			break;
	}
}
