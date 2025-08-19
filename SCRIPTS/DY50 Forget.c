#include <Adafruit_Fingerprint.h>
#include <Arduino.h>
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

void setup(){
  Serial2.begin(57600, SERIAL_8N1, 16, 17);
  Serial.begin(57600);
  delay(100);
  Serial.println("\nVergessenator\n");
  finger.begin(57600);//Unless you change using an internal command, you must use this rate

  if (finger.verifyPassword()) {
    Serial.println("Authenticated!");}
  else {
    Serial.println("Unauthenticated :(");
    while (1) { delay(1); }
  }}

uint8_t readnumber(void) {
  uint8_t num = 0;
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}

uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;

  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
  }
  return p;
}

void loop(){
  Serial.println("Please type in the ID # (from 1 to 127) you want to delete...");
  uint8_t id = readnumber();
  if (id == 0) {// ID #0 not allowed, try again!
     return;
  }
  Serial.print("Deleting ID #");
  Serial.println(id);
  deleteFingerprint(id);
}
