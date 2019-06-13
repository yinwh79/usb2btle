#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "i2c_message.h"

#include <bluefruit.h>

#include <stdint.h>

#define MAX_MSG_LEN 32

enum state_t {WAIT_FOR_TYPE, WAIT_FOR_LEN, WAIT_FOR_DATA};

class StateMachine {
public:
  StateMachine(BLEHidAdafruit *);
  void byteReceived(uint8_t);

private:
  state_t currentState;
  uint8_t message[MAX_MSG_LEN];
  uint8_t msgLen, msgCount;
  i2c_message_t msgType;

  BLEHidAdafruit *blehid;
};

#endif
