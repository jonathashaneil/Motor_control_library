#ifndef controle_h
#define controle_h

    #include <Arduino.h>
    
    #include <Encoder.h>
    
    #define ENCODER_DO_NOT_USE_INTERRUPTS
    #include <LiquidCrystal.h> 
    #include <TimerOne.h>
    #include <Wire.h>
    #define sensor_Pressao A0
    #define botao_Mouse 13
    #define pin11 11
    #define pin12 12
    #define moduloRele A5 
    //#define motorDC_1 A4
    #define motorDC_2 A3
    #define motorDC_3 A2
    #define motorDC_4 A1

   
    void interrupcao();
    void zerar_tempo();

    class Descelularizacao {
        public:
          Descelularizacao();
          
          void Erro();
          void ON_MotorPasso();
          void MotorPasso_Pressao(float);  
          void OFF_Motores();   
          void ON_MotorDC_2();  
          void ON_MotorDC_3();
          void ON_MotorDC_4();
          void alterar_PID(float, float, float);
          void configuracao();
          void Enviar_velocidade(int);
          void motor (float, int, int, int);
          void ligar(int);
          void OFF_MotorDC();
          void serial();
          void vazaodet(int);
         

          float pressao;
          float pressao_media;
          float volts;
          float erro;
          float erro_anterior;
          float integral = 0;
          float derivada;
          int pid;
          int velocidade = 0;
          float kp = -1.4;
          float ki = -0.5;
          float kd = -0.0;
          int i;
          float tempoencher;
          float tempototal;
          float tempoesvaziar;
          float tempocritico;
          int x;
          int volume_total;
          int volume_critico;
          int tempo;
          int inicio;
          int final;
          float vazao;
          float tempocriticoesvaziar;
          float vazaoesvaziar = 70.77;
          int y;

     
          


};



#endif
