#include <Stepper.h>
#include <Wire.h>

int spd = 1;
float spd_lento = 1;
int pin11 = 11;
int pin12 = 12;
Stepper myStepper(200, 10, 9, 8, 7 );

void receiveEvent() {
  spd = Wire.read();    // receive byte as an integer
}

void setup() {
  Wire.begin(54);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  myStepper.setSpeed(100);
  pinMode(pin11, INPUT);
  pinMode(pin12, INPUT);
}

void loop() {
  
  //Situação desligado
  while(!digitalRead(pin11) && !digitalRead(pin12)){
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
  }
  
  //Situação motor de passo baixa velocidade
  while(digitalRead(pin11) && !digitalRead(pin12)){
     myStepper.setSpeed(1);
     myStepper.step(1);
     spd_lento = spd / 200.0;
     delay(300.0/spd_lento);     
  }
    
  //Situação motor de passo alta velocidade
  while(!digitalRead(pin11) && digitalRead(pin12)){
    myStepper.setSpeed(spd);
    myStepper.step(1); 
  }
}
