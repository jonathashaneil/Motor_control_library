#include "controle.h"
float spd = 40;
Descelularizacao descel;


void setup() {
  // put your setup code here, to run once:
    descel.configuracao();
    
descel.tempo = 15; //Em minutos
descel.x = 3; //Qual motor será utilizado para enchimento
descel.inicio[10] = "encher";
descel.final[10] = "esvaziar";
descel.volume_total = 400; //Em mL
descel.volume_critico = 50; //Em mL

}

void loop() {
  // put your main code here, to run repeatedly:
  
  descel.motor(descel.pressao,descel.tempo,descel.inicio[10],descel.final[10]);
  


}
