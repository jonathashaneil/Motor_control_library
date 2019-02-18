#include "controle.h"

Descelularizacao::Descelularizacao(){}

/*
void requestEvent()
{
  Wire.write(30);
}*/

void Descelularizacao::Erro(){
	
}

void Descelularizacao::configuracao(){
  Serial.begin(9600);
  Wire.begin();
  pinMode(botao_Mouse, INPUT);
  pinMode(pin11, OUTPUT);
  pinMode(pin12, OUTPUT);
  digitalWrite(pin11, LOW);
  digitalWrite(pin12, LOW);
  pinMode(moduloRele, OUTPUT);
  //pinMode(motorDC_1, OUTPUT);
  pinMode(motorDC_2, OUTPUT);
  pinMode(motorDC_3, OUTPUT);
  pinMode(motorDC_4, OUTPUT);
  digitalWrite(moduloRele, LOW);
  //digitalWrite(motorDC_1, HIGH);
  digitalWrite(motorDC_2, HIGH);
  digitalWrite(motorDC_3, HIGH);
  digitalWrite(motorDC_4, HIGH);
}

void Descelularizacao::Enviar_velocidade(int speed){ 
   Wire.beginTransmission(54);
   Wire.write(speed);
   Wire.endTransmission(); 
}


 
void Descelularizacao::ON_MotorPasso(){
   digitalWrite(pin11, HIGH);
   digitalWrite(pin12, HIGH);
}

void Descelularizacao::MotorPasso_Pressao(float setpoint_pressao){
  pressao_media = 0;
  for (i=0; i<10000; i++)
  {
    volts = analogRead(sensor_Pressao) * 0.0049;
    pressao = ((volts/5.0) - 0.04)/0.09;
    pressao_media = pressao + pressao_media;  
  }
  pressao_media = pressao_media/i + 0.1511;
  erro = pressao_media - setpoint_pressao;
  if (erro>-1 && erro<1)  integral = erro + integral;
  derivada = (erro-erro_anterior);
  pid = kp*erro  + ki*integral + kd*derivada;
  velocidade = velocidade + pid;
  if (velocidade > 180) 
     velocidade = 180;
  if (velocidade < 1) 
     velocidade = 1;
  erro_anterior = erro;
  Descelularizacao::Enviar_velocidade(velocidade);
  if (abs(integral) > 10000)  Descelularizacao::Erro();        
}

void Descelularizacao::OFF_Motores(){
   digitalWrite(pin11, LOW);
   digitalWrite(pin12, LOW);
   digitalWrite(moduloRele, LOW);
   //digitalWrite(motorDC_1, HIGH);
   digitalWrite(motorDC_2, HIGH);
   digitalWrite(motorDC_3, HIGH);
   digitalWrite(motorDC_4, HIGH);
}
 
void Descelularizacao::ON_MotorDC(){
   digitalWrite(moduloRele, HIGH);
   digitalWrite(motorDC_2, LOW);
}

void Descelularizacao::alterar_PID(float novo_kp,float novo_ki,float novo_kd){
   kp = novo_kp;
   ki = novo_ki;
   kd = novo_kd;
}

int Descelularizacao::teste(int x){
   return x+2;
}
