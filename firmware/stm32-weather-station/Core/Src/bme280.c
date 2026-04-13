#include "bme280.h"

uint8_t BME280_ReadID(I2C_HandleTypeDef *hi2c)
{
    uint8_t id;
    HAL_I2C_Mem_Read(hi2c, BME280_ADDR, 0xD0, 1, &id, 1, 100);
    return id;
}
