#include <Arduino.h>

#include "CAN.h"
#include "canopen.h"

canopen::CAN_DUINO can_due;

void voltages()
{
    canopen::CANFrame f;
    can_due.read(f, 8, 0x210D, 2);
    can_due.write(f);
    delay(1);
    CAN_Frame message;
    while(CAN.available()){
      message = CAN.read();
      if(message.id == 1416)
      {
        Serial.print("Voltages:");
        Serial.print(message.data[4]/10);
        Serial.println('V');
      }
    }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  CAN.begin(500000);
  Serial.println("CAN began.");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available() > 0)
    switch (Serial.read())
    {
      case 'v': voltages(); break;
    }

}

