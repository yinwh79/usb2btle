#ifndef I2C_MESSAGE_H
#define I2C_MESSAGE_H

#include <stdint.h>

enum i2c_message_t {DBG = 0x00, KBD = 0x01, INVALID = 0xff};

const uint8_t BTLE_WIREADDR = 4;

#endif
