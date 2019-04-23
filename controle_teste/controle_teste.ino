#include "controle.h"

float spd = 40;
int encher = 1;
int esvaziar = 0;
Descelularizacao descel;


void setup() {
  // put your setup code here, to run once:
  descel.configuracao(); 
  descel.tempo = 1; //Em minutos
  descel.x = 3; //Qual motor será utilizado para enchimento
  descel.inicio = encher;
  descel.final = esvaziar;
  descel.volume_total = 30; //Em mL
  descel.volume_critico = 10; //Em mL

}


void loop() {
  // put your main code here, to run repeatedly:
  
descel.motor(descel.pressao,descel.tempo,descel.inicio,descel.final);

// descel.serial();

//  descel.ON_MotorDC_2();
//  delay (2000);
//  descel.ON_MotorDC_3();
//  delay (2000);
//  descel.ON_MotorDC_4();
//  delay (2000);
//  descel.OFF_Motores();
//  delay (10000);

}
