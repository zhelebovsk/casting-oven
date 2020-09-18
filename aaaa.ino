
#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;
float delta = 1.0;
float T0;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  T0 = 100.0;
  pinMode(7, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Oven start");
  // wait for MAX chip to stabilize
  delay(1000);
}

void loop() {
  // basic readout test, just print the current temp
   if (Serial.available() > 1) {
         T0 = Serial.readString().toFloat();
         // Serial.println(T0);
    }
   float T = thermocouple.readCelsius();
   if (T0 - T > delta) {
          digitalWrite(LED_BUILTIN, HIGH);
          digitalWrite(7, HIGH);  
          Serial.println("ON  ");
   }

   if (T0 - T < - delta) {
          digitalWrite(LED_BUILTIN, LOW);
          digitalWrite(7, LOW);  
          Serial.println("OFF ");
   }
   
   Serial.print(millis()/1000.0/60.0);
   Serial.println(" min");
   
   Serial.print("Purpose: ");
   Serial.print(T0);
   Serial.println(" degC");
   
   Serial.print("Sensor: ");
   Serial.print(T);
   Serial.println(" degC");

   Serial.println();
    
   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
   delay(1000);
}
