/**
 *This header contains API for ADXL345 digital accelerometer
 *
 *Using specified Adxl structure allows programmer to logically separate the module from mcu peripherals 
 *
 *The project has been prepared by P.Radecki, A.Król and L.Wisniewska
 *
 */
#include "stm32f7xx_hal.h"

/*Typedef Adxl is structure responsible of keeping all crucial information regarding the particalr module*/
typedef struct Adxl{
	I2C_HandleTypeDef *hi2c;
	float coefficient;
	uint8_t addr;
} Adxl;

/*Reads num bytes of data from registers [reg,reg+num) and store it in rxData array*/
void ADXL_Read(Adxl *hadxl, uint8_t reg, uint8_t* rxData, int num);

/*Writes num bytes of data from txData to registers [reg,reg+num)*/
void ADXL_Write(Adxl *hadxl, uint8_t reg, uint8_t txData, int num);

/*Function is responsible for bonding adxl instance to proper port and address*/
void ADXL_Init(Adxl *hadxl,I2C_HandleTypeDef *hi2c, char* sensitivity, uint8_t addr);

/*Measures acceleration stored in registers 0x32-0x37*/
void ADXL_Measure(Adxl *hadxl, float* rxData);