#ifndef BME280_H
#define BME280_H

#include "stm32f4xx_hal.h"

#define BME280_ADDR  (0x76 << 1)

uint8_t BME280_ReadID(I2C_HandleTypeDef *hi2c);

void BME280_Init(I2C_HandleTypeDef *hi2c);

int32_t BME280_ReadRawTemp(I2C_HandleTypeDef *hi2c);

#endif
