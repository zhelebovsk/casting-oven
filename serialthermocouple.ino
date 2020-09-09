#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;
float delta = 10.0;
float T0 = 0.0;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  pinMode(7, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Oven start");
  // wait for MAX chip to stabilize
  delay(1000);
}

void loop() {
  // basic readout test, just print the current temp
   if (Serial.available() > 0) {
          float T0 = Serial.read();
    }
    
   float T = thermocouple.readCelsius();
   
   if (T0 - T > - delta) {
          digitalWrite(LED_BUILTIN, HIGH);
          digitalWrite(7, HIGH);  
          Serial.print('ON  ');
   }

   if (T0 - T < delta) {
          digitalWrite(LED_BUILTIN, LOW);
          digitalWrite(7, LOW);  
          Serial.print('OFF ');
   }
   
   Serial.print(millis()/1000.0/60.0, 'min: ');
   Serial.println(T);
   
    
   // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
   delay(500);
}
