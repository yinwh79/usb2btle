#ifndef I2C_RING_BUFFER_H
#define I2C_RING_BUFFER_H

#include <stdint.h>

#define RINGBUFLEN 256

class I2CRingBuffer {
public:
  I2CRingBuffer();

  bool read(uint8_t *);
  void write(uint8_t);

private:
  volatile uint8_t buf[RINGBUFLEN];
  volatile uint8_t head;
  volatile uint8_t tail;
};

#endif
