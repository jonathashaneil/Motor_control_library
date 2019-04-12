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
  pinMode(moduloRele, OUTPUT);
  //pinMode(motorDC_1, OUTPUT);
  pinMode(motorDC_2, OUTPUT);
  pinMode(motorDC_3, OUTPUT);
  pinMode(motorDC_4, OUTPUT);
  //digitalWrite(motorDC_1, HIGH);
  digitalWrite(motorDC_2, HIGH);
  digitalWrite(motorDC_3, HIGH);
  digitalWrite(motorDC_4, HIGH);
  digitalWrite(pin11, LOW);
  digitalWrite(pin12, LOW);
  digitalWrite(moduloRele, LOW);
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
   //digitalWrite(motorDC_1, HIGH);
   digitalWrite(motorDC_2, HIGH);
   digitalWrite(motorDC_3, HIGH);
   digitalWrite(motorDC_4, HIGH);
   digitalWrite(pin11, LOW);
   digitalWrite(pin12, LOW);
   digitalWrite(moduloRele, LOW);
}
 
void Descelularizacao::ON_MotorDC_2(){
   digitalWrite(moduloRele, HIGH);
   digitalWrite(motorDC_3, HIGH);
   digitalWrite(motorDC_4, HIGH);
   digitalWrite(motorDC_2, LOW);
}

void Descelularizacao::ON_MotorDC_3(){
   digitalWrite(moduloRele, HIGH);
   digitalWrite(motorDC_2, HIGH);
   digitalWrite(motorDC_4, HIGH);
   digitalWrite(motorDC_3, LOW);
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


void Descelularizacao::ligar (int m){
  if(m==3){
    Descelularizacao::ON_MotorDC_3();}
  if(m==4){
    Descelularizacao::ON_MotorDC_4();}
  }

void Descelularizacao::vazaodet(int y){
  if(y==3){
    vazao = 67.93;}
  if(y==4){
    vazao = 52.04;}
    }  

void Descelularizacao::motor (float pressao, int tempo, int inicio, int final){

  Descelularizacao::vazaodet(x);
  
  tempoencher = (volume_total - volume_critico)/vazao;
  tempocritico = (volume_critico/vazao)*60000;
  tempototal = tempoencher + tempo + (volume_total - volume_critico)/vazaoesvaziar;
  tempoesvaziar = tempototal - (volume_total - volume_critico)/vazaoesvaziar;
  tempocriticoesvaziar = (volume_critico/vazaoesvaziar)*60000;
  
  lcd1.clear();

  if (inicio==1){
    ligar(x);
    Serial.println("enchimento critico motor 3");
    delay(tempocritico);
    OFF_MotorDC();
    Serial.println("desligar motoresDC");}

    zerar_tempo();
    ON_MotorPasso();
    
  while(minutos<=tempototal){
    MotorPasso_Pressao(pressao);
    Serial.println("motor de passo");
    
    lcd1.setCursor(0,0);
    lcd1.print(velocidade);
    lcd1.setCursor(7,0);
    lcd1.print(pressao);
    lcd1.setCursor(0,1);
    lcd1.print(tempo);
    
      if(inicio==1 && minutos<=tempoencher){
        ligar(x);
        Serial.println("motor 3");}
      if(minutos>tempoencher && minutos<tempoesvaziar){
        OFF_MotorDC();
        Serial.println("desligar");}
      if(final==0 && minutos>=tempoesvaziar){
        ON_MotorDC_2();
        Serial.println("motor 2");}}
  
  OFF_Motores();
  Serial.println("desligar motores");

  if(final==0){
    ON_MotorDC_2();
    Serial.println("esvaziamento critico motor 2");
    delay(tempocriticoesvaziar + 3000);
    OFF_MotorDC();
    Serial.println("fim");}
    
}

void Descelularizacao::serial(){
ON_MotorDC_4();
delay(3000);
OFF_MotorDC();
delay(6000);

// Serial.println(segundos);

//  ON_MotorDC_2();
//  Serial.println("motor2");
//  delay (2000);
//  ON_MotorDC_3();
//  Serial.println("motor3");
//  delay (2000);
//  ON_MotorDC_4();
//  Serial.println("motor4");
//  delay (2000);
//  OFF_MotorDC();
//  delay (10000);

//  while(segundos==1){
//    ON_MotorDC_4();
//    Serial.println("motor 4");}
//    OFF_Motores();
//
//  while(segundos==2){
//    ON_MotorDC_3();
//    Serial.println("motor 3");}
//    OFF_Motores();
//
//  while(segundos==3){
//    ON_MotorDC_2();
//    Serial.println("motor 2");}
//    OFF_Motores();
//
//  if(segundos>4){
//    segundos=0;}
}
