#include "i2c_ring_buffer.h"

#include <SimplyAtomic.h>

I2CRingBuffer::I2CRingBuffer(): head(0), tail(0) {}

bool I2CRingBuffer::read(uint8_t *v) {
  ATOMIC() {
    if (this->head == this->tail) {
      return false;
    }

    *v = this->buf[this->head];
    this->head = (this->head + 1) % RINGBUFLEN;
    return true;
  }
}

void I2CRingBuffer::write(uint8_t v) {
  ATOMIC() {
    this->buf[this->tail] = v;
    this->tail = (this->tail + 1) % RINGBUFLEN;
  }
}
