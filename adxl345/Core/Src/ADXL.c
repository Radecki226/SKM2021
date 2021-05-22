#include "ADXL.h"
#include "string.h"
void ADXL_Read(Adxl *hadxl, uint8_t reg, uint8_t* rxData, int num)
{
   HAL_I2C_Mem_Read (hadxl->hi2c, hadxl->addr, reg, 1, rxData, num, 10);
}

void ADXL_Write(Adxl *hadxl, uint8_t reg, uint8_t txData, int num){
	HAL_I2C_Mem_Write(hadxl->hi2c, hadxl->addr, reg, 1, &txData, num, 10);
}

void ADXL_Init(Adxl *hadxl,I2C_HandleTypeDef *hi2c, char* sensitivity, uint8_t addr){
	
	hadxl->hi2c = hi2c;
	hadxl->addr = addr;
	
	uint8_t sensitivityReg;
	/*compare strings*/
	char* g2 = "2g";
	char* g4 = "4g";
	char* g8 = "8g";
	char* g16 = "16g";
	
	/*set proper parameter*/
	if (strcmp(sensitivity,g2) == 0){
		sensitivityReg = 0x00;
		hadxl->coefficient = .0039;
	}
	else if(strcmp(sensitivity,g4) == 0){
		sensitivityReg = 0x01;
		hadxl->coefficient = .0078;
	}
	else if(strcmp(sensitivity, g8) == 0){
		sensitivityReg = 0x02;
		hadxl->coefficient = .0156;
	}
	else{
		sensitivityReg = 0x03;
		hadxl->coefficient =.0312;
	}
	
	ADXL_Write(hadxl, 0x2d, 0x00, 1); // rst all bits in power control
	ADXL_Write(hadxl, 0x2d, 0x08, 1); //measure, f=8Hz
	ADXL_Write(hadxl, 0x31, sensitivityReg, 1); //set proper sensitivity
	
	
}
void ADXL_Measure(Adxl *hadxl, float* rxData){
	uint8_t tempData[6]; 
	ADXL_Read(hadxl, 0x32, tempData, 6);
	int16_t x = tempData[0] | (uint16_t)tempData[1] << 8;
	int16_t y = tempData[2] | (uint16_t)tempData[3] << 8;
	int16_t z = tempData[4] | (uint16_t)tempData[5] << 8;
	rxData[0] = x*hadxl->coefficient;
	rxData[1] = y*hadxl->coefficient;
	rxData[2] = z*hadxl->coefficient;
}