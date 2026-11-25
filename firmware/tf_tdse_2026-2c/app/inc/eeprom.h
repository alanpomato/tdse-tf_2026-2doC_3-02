#include <stdbool.h>

#define EEPROM_DIR_I2C 0xA0
#define EEPROM_DIR_BASE 0x0000

bool eeprom_read_it (uint16_t dir, uint8_t *buf, uint16_t n);
bool eeprom_write_it(uint16_t dir, const uint8_t *buf, uint16_t n);
