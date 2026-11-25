#include "main.h"
#include "eeprom.h"


extern I2C_HandleTypeDef hi2c1;

bool eeprom_read_it (uint16_t dir, uint8_t *buf, uint16_t n){

	return ( HAL_I2C_Mem_Read_IT(&hi2c1, EEPROM_DIR_I2C, dir, I2C_MEMADD_SIZE_16BIT, (uint8_t *)buf, n) == HAL_OK );



}



bool eeprom_write_it(uint16_t dir, const uint8_t *buf, uint16_t n){

	return ( HAL_I2C_Mem_Write_IT(&hi2c1, EEPROM_DIR_I2C, dir, I2C_MEMADD_SIZE_16BIT, (uint8_t *)buf, n) == HAL_OK );


}
