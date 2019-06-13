#include "state_machine.h"

#include "i2c_message.h"
#include "log.h"

#include <Arduino.h>

StateMachine::StateMachine(BLEHidAdafruit *blehid): currentState(WAIT_FOR_TYPE), blehid(blehid) {}

void StateMachine::byteReceived(uint8_t inByte) {
  dbgPrint("inByte=");
  dbgPrintln(inByte);

  switch (this->currentState) {
  case WAIT_FOR_TYPE:
    switch (inByte) {
    case KBD:
      digitalWrite(LED_BUILTIN, HIGH);
      this->msgType = KBD;
      break;

    case DBG:
      dbgPrint("T-M0: ");
      this->msgType = DBG;
      break;

    default:
      this->msgType = INVALID;
      Serial.printf("Invalid message type: %ud.\r\n", inByte);
    }

    this->currentState = WAIT_FOR_LEN;
    break;

  case WAIT_FOR_LEN:
    dbgPrintf("msg len: %u\r\n", inByte);
    this->msgLen = inByte;
    this->msgCount = 0;

    if (this->msgLen == 0) {
      this->currentState = WAIT_FOR_TYPE;
    } else {
      this->currentState = WAIT_FOR_DATA;
    }
    break;

  case WAIT_FOR_DATA:
    dbgPrintf("data: %02x\r\n", inByte);
    switch (this->msgType) {
    case KBD:
      this->message[this->msgCount++ % sizeof(this->message)] = inByte;
      break;

    case DBG:
      dbgPrint(inByte);
      break;
    }

    if (this->msgCount == this->msgLen) {
      switch (this->msgType) {
      case KBD:
        dbgPrintln("sending kbd report");
        this->blehid->keyboardReport(this->message[0], &this->message[2]);
        digitalWrite(LED_BUILTIN, LOW);
        break;

      case DBG:
        dbgPrintln();
        break;
      }
      this->currentState = WAIT_FOR_TYPE;
    }
    break;

  default:
    Serial.printf("Invalid message state: %ud.\r\n", this->currentState);
    break;
  }
}
