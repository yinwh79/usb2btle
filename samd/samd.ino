// -*- mode: c++ -*-

#include "i2c_message.h"

#include <hidboot.h>
#include <usbhub.h>
#include <Wire.h>

#ifdef ADAFRUIT_TRINKET_M0
#include <Adafruit_DotStar.h>

const uint8_t NUMPIXELS = 1;
const uint8_t DATAPIN = 7;
const uint8_t CLOCKPIN = 8;

Adafruit_DotStar px(NUMPIXELS, DATAPIN, CLOCKPIN);


void initTXLED() {
}

void turnOffTXLED() {
  px.clear();
  px.show();
}

void turnOnTXLED() {
  px.setPixelColor(0, 63, 63, 0);
  px.show();
}
#else // ADAFRUIT_TRINKET_M0
void initTXLED() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void turnOffTXLED() {
  digitalWrite(LED_BUILTIN, HIGH);
}

void turnOnTXLED() {
  digitalWrite(LED_BUILTIN, LOW);
}
#endif // ADAFRUIT_TRINKET_M0

void dbg(char *msg) {
  uint8_t len = strlen(msg);

  Wire.beginTransmission(BTLE_WIREADDR);
  Wire.write(DBG);
  Wire.write(len);
  Wire.write(msg);
  Wire.endTransmission();
}

class KeyboardRaw: public KeyboardReportParser {
public:
  void Parse(HID *hid, uint32_t is_rpt_id, uint32_t len, uint8_t *buf);
};

void KeyboardRaw::Parse(HID *hid, uint32_t is_rpt_id, uint32_t len, uint8_t *buf) {
  turnOnTXLED();

  KeyboardReportParser::Parse(hid, is_rpt_id, len, buf);

  Wire.beginTransmission(BTLE_WIREADDR);
  Wire.write(KBD);
  Wire.write(len);
  Wire.write(buf, len);
  Wire.endTransmission();

  turnOffTXLED();
}

USBHost usb;
USBHub hub(&usb);
HIDBoot<HID_PROTOCOL_KEYBOARD> hidKeyBoard(&usb);
KeyboardRaw parser;

void setup() {
  initTXLED();
  turnOffTXLED();

  Wire.begin();

  dbg("Booting\r\n");

  if (usb.Init()) {
    dbg("USB Host did not start!\r\n");
    while (true) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(125);
      digitalWrite(LED_BUILTIN, LOW);
      delay(125);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(125);
      digitalWrite(LED_BUILTIN, LOW);
      delay(125);

      delay(500);
    }
  }

  hidKeyBoard.SetReportParser(0, &parser);
}

void loop() {
  asm("wfe \n");
  usb.Task();
}
