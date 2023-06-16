#include <SoftwareSerial.h> 

SoftwareSerial sensorSerial(12, 0);

byte request[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
unsigned char response[9];

void sensor_init() {
  sensorSerial.begin(9600);
}

int temp = 0;
int CO2 = 0;


void getValues() {

  sensorSerial.write(request, 9);
  memset(response, 0, 9);
  sensorSerial.readBytes(response, 9);
  byte crc = 0;
  for (int i = 1; i < 8; i++) {
    crc += response[i];
  }
  crc = 255 - crc;
  crc++;

  if (!(response[0] == 0xFF && response[1] == 0x86 && response[8] == crc)) {
    Serial.println("CRC error");
    
  } else {
    unsigned int HLconcentration = (unsigned int) response[2];
    unsigned int LLconcentration = (unsigned int) response[3];

    CO2 = (256*HLconcentration) + LLconcentration;
    temp = response[4]-40;
  }
}
