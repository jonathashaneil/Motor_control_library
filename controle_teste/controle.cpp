#include "controle.h"

    
    int segundos=0;
    int minutos=0;
    int tempo;

    LiquidCrystal lcd1 (3,4,10,11,12,13);

void interrupcao(){

  segundos++;
  if(segundos>=10){minutos++; segundos=0;}
}

void zerar_tempo(){
 segundos=0;
 minutos=0;
}

byte tempo_def(unsigned long t){

  if(minutos>=t){return 0;}
  else {return 1;}  
}

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
  Timer1.initialize(6000000);
  Timer1.attachInterrupt(interrupcao);
  lcd1.begin(16,2);



  
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
  if (abs(integral)   > 10000)  Descelularizacao::Erro();        
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
 
void Descelularizacao::ON_MotorDC_2(){
   digitalWrite(moduloRele, HIGH);
   digitalWrite(motorDC_2, LOW);
   digitalWrite(motorDC_3, HIGH);
   digitalWrite(motorDC_4, HIGH);
}

void Descelularizacao::ON_MotorDC_3(){
   digitalWrite(moduloRele, HIGH);
   digitalWrite(motorDC_2, HIGH);
   digitalWrite(motorDC_3, LOW);
   digitalWrite(motorDC_4, HIGH);
}

void Descelularizacao::ON_MotorDC_4(){
   digitalWrite(moduloRele, HIGH);
   digitalWrite(motorDC_2, HIGH);
   digitalWrite(motorDC_3, HIGH);
   digitalWrite(motorDC_4, LOW);
}

void Descelularizacao::OFF_MotorDC(){
   digitalWrite(motorDC_2, HIGH);
   digitalWrite(motorDC_3, HIGH);
   digitalWrite(motorDC_4, HIGH);
  }

void Descelularizacao::alterar_PID(float novo_kp,float novo_ki,float novo_kd){
   kp = novo_kp;
   ki = novo_ki;
   kd = novo_kd;
}

int Descelularizacao::teste(int 

x){
   return x+2;
}

void Descelularizacao::ligar (int m){
  if(m=3){
    Descelularizacao::ON_MotorDC_3();
    vazao = 67.9260292694;}
  if(m=4){
    Descelularizacao::ON_MotorDC_4();
    vazao = 52.039549061;}
  }

void Descelularizacao::motor (float pressao, int tempo, char inicio[10], char final[10]){

  tempoencher = volume_total/vazao;
  tempocritico = volume_critico/vazao;
  tempototal = (volume_total/vazao) + tempo + (volume_total/vazao);
  tempocriticoesvaziar = volume_critico/vazaoesvaziar;
  tempoesvaziar = tempototal - tempocriticoesvaziar;
  
  lcd1.clear();
  zerar_tempo();


  if (inicio=="encher"){
    Descelularizacao::ligar(x);
    delay(tempocritico);
    Descelularizacao::OFF_MotorDC();}

  while(minutos<tempototal){
    Descelularizacao::MotorPasso_Pressao(pressao);
    
    lcd1.setCursor(0,0);
    lcd1.print(velocidade);
    lcd1.setCursor(7,0);
    lcd1.print(pressao);
    lcd1.setCursor(0,1);
    lcd1.print(tempo);
    
      if(inicio=="encher" && minutos<tempoencher){
        Descelularizacao::ligar(x);}
      if(minutos>tempoencher){
        Descelularizacao::OFF_MotorDC();}
      if(final=="esvaziar" && minutos>tempoesvaziar){
        Descelularizacao::ON_MotorDC_2();}}
  
  Descelularizacao::OFF_Motores();

  if(final=="esvaziar"){
    Descelularizacao::ON_MotorDC_2();
    delay(tempocritico + 3000);
    Descelularizacao::OFF_MotorDC();}
    
}

  
  
  
