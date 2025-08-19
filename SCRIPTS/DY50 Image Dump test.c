//Photo Dump
#include <Adafruit_Fingerprint.h>
#include <Arduino.h>
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);
unsigned char buffer[40032]={0};
void setup()
{
  Serial2.begin(57600, SERIAL_8N1, 16, 17);
  Serial.begin(57600);
  delay(100);
  Serial.println("\n\ Picture Taker and Uploader");
  finger.begin(57600);//Unless you change using an internal command, you must use this rate

  if (finger.verifyPassword()) {
    Serial.println("Authenticated!");
  } else {
    Serial.println("Unauthenticated :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);
}

void loop()                  
{
  delay(50);
  int p = -1;
  Serial.print("Waiting for finger\n");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    case -1:
      Serial.println("Packet did not return anything");
    default:
      Serial.println("Unknown error");
      break;
    }
  }

unsigned char text[]="texto";

Serial.print("Attempting to Send\n");//Expecting aproximatelly 288 packets of 128 bytes of image which each carry 2 pixels + 11 bytes of head and tail each/packet
int i=0,starttime = millis();         // (288*128)+(288*11)=40032
p = finger.upImage();
if (p == FINGERPRINT_OK) {
    while (i < 40032&&(millis()-starttime)<10000) {
        if (Serial2.available()) {
          buffer[i] = Serial2.read();
          //printf("%i,", i);
          //printf("%i\n", buffer[i]);/
          i++;
} } }
printf("\nThat's what we got:\n");
for (i=0;i<40032;i++){
  printf("%i,",buffer[i]);
} 

printf("\nThat's the end\n");
}
