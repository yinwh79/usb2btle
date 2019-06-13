// -*- mode: c++ -*-
#include "i2c_message.h"
#include "i2c_ring_buffer.h"
#include "log.h"
#include "state_machine.h"

#include <bluefruit.h>
#include <Wire.h>

BLEDis bledis;
BLEHidAdafruit blehid;

I2CRingBuffer rb;
StateMachine fsm(&blehid);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(PIN_WIRE_SDA, INPUT_PULLUP);
  pinMode(PIN_WIRE_SCL, INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("usb2btle booting.");

  Wire.begin(BTLE_WIREADDR);
  Wire.onReceive(wireDataReceived);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("usb2btle");

  // Configure and Start Device Information Service
  bledis.setManufacturer("Kublai Khansulting");
  bledis.setModel("devel-nrf52832-trinketm0");
  bledis.begin();

  /* Start BLE HID
   * Note: Apple requires BLE device must have min connection interval >= 20m
   * ( The smaller the connection interval the faster we could send data).
   * However for HID and MIDI device, Apple could accept min connection interval
   * up to 11.25 ms. Therefore BLEHidAdafruit::begin() will try to set the min and max
   * connection interval to 11.25  ms and 15 ms respectively for best performance.
   */
  blehid.begin();
  blehid.setKeyboardLedCallback(setKeyboardLED);

  startAdv();

  digitalWrite(LED_BUILTIN, LOW);
}

void startAdv(void)
{
  Serial.println("Advertising HID.");

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void loop() {
  waitForEvent();

  uint8_t v;
  while (rb.read(&v)) {
    dbgPrintf("got byte on rb: %02x\r\n", v);
    fsm.byteReceived(v);
  }
}

void wireDataReceived(int numBytes) {
  dbgPrintf("wireDataReceived: %u\r\n", numBytes);
  for (int i = 0; i < numBytes; i++) {
    rb.write(Wire.read());
  }
}

void setKeyboardLED(uint16_t conn_handle, uint8_t led_bitmap) {
  (void) conn_handle;

  // light up Red Led if any bits is set
  if (led_bitmap) {
    ledOn(LED_RED);
  } else {
    ledOff(LED_RED);
  }
}
