#ifndef BME280_H
#define BME280_H

#include "stm32f4xx_hal.h"

#define BME280_ADDR  (0x76 << 1)

typedef struct {
	uint16_t dig_T1;
	int16_t	 dig_T2;
	int16_t  dig_T3;

    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;

    uint8_t  dig_H1;
    int16_t  dig_H2;
    uint8_t  dig_H3;
    int16_t  dig_H4;
    int16_t  dig_H5;
    int8_t   dig_H6;
} BME280_CalibData;

uint8_t BME280_ReadID(I2C_HandleTypeDef *hi2c);

void BME280_Init(I2C_HandleTypeDef *hi2c);
void BME280_ReadCalibration(I2C_HandleTypeDef *hi2c);

int32_t BME280_ReadRawTemp(I2C_HandleTypeDef *hi2c);
int32_t BME280_CompensateTemperature(int32_t adc_T);

int32_t BME280_ReadRawPressure(I2C_HandleTypeDef *hi2c);
int32_t BME280_CompensatePressure(int32_t adc_P);

int32_t BME280_ReadRawHumidity(I2C_HandleTypeDef *hi2c);
int32_t BME280_CompensateHumidity(int32_t adc_H);

#endif
