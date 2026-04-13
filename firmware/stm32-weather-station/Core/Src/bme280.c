#include "bme280.h"

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
