#include "bme280.h"

static BME280_CalibData calib;

int32_t t_fine;

//#include <stdio.h>
//#include <string.h>
//extern UART_HandleTypeDef huart2;
//
//void BME280_DebugCalibration(void)
//{
//    char buf[100];
//
//    sprintf(buf, "T1=%u T2=%d T3=%d\r\n",
//            calib.dig_T1, calib.dig_T2, calib.dig_T3);
//
//    HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), 100);
//}

uint8_t BME280_ReadID(I2C_HandleTypeDef *hi2c)
{
    uint8_t id;
    HAL_I2C_Mem_Read(hi2c, BME280_ADDR, 0xD0, 1, &id, 1, 100);
    return id;
}

void BME280_Init(I2C_HandleTypeDef *hi2c)
{
	uint8_t data = 0x27;
	HAL_I2C_Mem_Write(hi2c, BME280_ADDR, 0xF4, 1, &data, 1, 100);
}

int32_t BME280_ReadRawTemp(I2C_HandleTypeDef *hi2c)
{
	uint8_t data[3];
	int32_t rawTemp;

	HAL_I2C_Mem_Read(hi2c, BME280_ADDR, 0xFA, 1, data, 3, 100);

	rawTemp = 	((int32_t)data[0] << 12) |
				((int32_t)data[1] << 4)  |
				((int32_t)data[2] >> 4);

	return rawTemp;
}

void BME280_ReadCalibration(I2C_HandleTypeDef *hi2c)
{
	uint8_t data[6];

	HAL_I2C_Mem_Read(hi2c, BME280_ADDR, 0x88, 1, data, 6, 100);

	calib.dig_T1 = (uint16_t)(data[1] << 8) | data[0];
	calib.dig_T2 = (int16_t)(data[3] << 8) | data[2];
	calib.dig_T3 = (int16_t)(data[5] << 8) | data[4];
}

int32_t BME280_ReadTemperature(I2C_HandleTypeDef *hi2c)
{
	int32_t adc_T = BME280_ReadRawTemp(hi2c);

	int32_t var1 = ((((adc_T >> 3) - ((int32_t)calib.dig_T1 << 1))) *
			((int32_t)calib.dig_T2)) >> 11;

	int32_t var2 = (((((adc_T >> 4) - ((int32_t)calib.dig_T1)) *
					 ((adc_T >> 4) - ((int32_t)calib.dig_T1))) >> 12) *
				   ((int32_t)calib.dig_T3)) >> 14;

	t_fine = var1 + var2;

	return (t_fine * 5 + 128) >> 8;
}
