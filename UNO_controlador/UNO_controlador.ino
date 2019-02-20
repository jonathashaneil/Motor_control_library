#include <controle.h>
Descelularizacao descel;
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
float spd = 0;

void setup() {
  descel.configuracao();
 }

 void tela_lcd(){
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(3, 1);
  //Envia o texto entre aspas para o LCD
  lcd.print("FILIPEFLOP");
  lcd.setCursor(3, 2);
  lcd.print(" LCD 16x2");
  delay(5000); 
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  } 
 }
 
void loop() {

  spd = 40;
  
  /************************
    Acionar motor de passo - velocidade / rápido
   ************************/
  //descel.ON_MotorPasso_rapido();
  //descel.Enviar_velocidade(int(spd));

  /************************
    Acionar motor de passo - velocidade / lento
   ************************/
  //descel.ON_MotorPasso_lento();
  //descel.Enviar_velocidade(spd*200);  // spd tem que ser múltiplo de 0,005
  
  /************************
    Acionar motor de passo - pressao
   ************************/
  //descel.ON_MotorPasso_rapido();
  //descel.MotorPasso_Pressao(spd);
  
  /************************
    Desligar motor de passo
   ************************/
  //descel.OFF_MotorPasso();

  /************************
    Acionar motor de corrente contínua
   ************************/
  //descel.ON_MotorDC();
  //descel.OFF_MotorDC();

  
}
