#include "bme280.h"

static BME280_CalibData calib;

int32_t t_fine;

#include <stdio.h>
#include <string.h>
extern UART_HandleTypeDef huart2;

void BME280_DebugCalibration(void)
{
    char buf[100];

    sprintf(buf, "P1=%u P2=%d T3=%d\r\n",
            calib.dig_P1, calib.dig_P2, calib.dig_T3);

    HAL_UART_Transmit(&huart2, (uint8_t*)buf, strlen(buf), 100);

}



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
	uint8_t data[24];

	HAL_I2C_Mem_Read(hi2c, BME280_ADDR, 0x88, 1, data, 24, 100);

	calib.dig_T1 = (data[1] << 8) | data[0];
	calib.dig_T2 = (data[3] << 8) | data[2];
	calib.dig_T3 = (data[5] << 8) | data[4];

	calib.dig_P1 = (data[7]  << 8) | data[6];
	calib.dig_P2 = (data[9]  << 8) | data[8];
	calib.dig_P3 = (data[11] << 8) | data[10];
	calib.dig_P4 = (data[13] << 8) | data[12];
	calib.dig_P5 = (data[15] << 8) | data[14];
	calib.dig_P6 = (data[17] << 8) | data[16];
	calib.dig_P7 = (data[19] << 8) | data[18];
	calib.dig_P8 = (data[21] << 8) | data[20];
	calib.dig_P9 = (data[23] << 8) | data[22];
}

int32_t BME280_CompensateTemperature(int32_t adc_T)
{
	int32_t var1, var2;

	var1 = ((((adc_T >> 3) - ((int32_t)calib.dig_T1 << 1))) *
			((int32_t)calib.dig_T2)) >> 11;

	var2 = (((((adc_T >> 4) - ((int32_t)calib.dig_T1)) *
					 ((adc_T >> 4) - ((int32_t)calib.dig_T1))) >> 12) *
				   ((int32_t)calib.dig_T3)) >> 14;

	t_fine = var1 + var2;

	return (t_fine * 5 + 128) >> 8;
}

int32_t BME280_ReadRawPressure(I2C_HandleTypeDef *hi2c)
{
	uint8_t data[3];
	int32_t rawPressure;

	HAL_I2C_Mem_Read(hi2c, BME280_ADDR, 0xF7, 1, data, 3, 100);

	rawPressure = ((int32_t)data[0] << 12) |
				  ((int32_t)data[1] << 4)  |
				  ((int32_t)data[2] >> 4);

	return rawPressure;
}

int32_t BME280_CompensatePressure(int32_t adc_P)
{
    int64_t var1, var2, p;

    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)calib.dig_P6;
    var2 = var2 + ((var1 * (int64_t)calib.dig_P5) << 17);
    var2 = var2 + (((int64_t)calib.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)calib.dig_P3) >> 8) +
           ((var1 * (int64_t)calib.dig_P2) << 12);

    var1 = (((((int64_t)1) << 47) + var1)) *
           ((int64_t)calib.dig_P1) >> 33;

    if (var1 == 0)
        return 0;

    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;

    var1 = (((int64_t)calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)calib.dig_P8) * p) >> 19;

    p = ((p + var1 + var2) >> 8) + (((int64_t)calib.dig_P7) << 4);

    return (int32_t)(p / 256); // Pa
}

