# FishFeeder
Simple Fish Feeder with  RTC based on Arduino.

At this project, it's possible to adjust the time of the fish feed during the day. 
It's was used as a micro servo 90g attached at a 3d printed enclosure, an Arduino nano, and a RTC 3231 to provide the time reference if the main power goes down and the controller is a reboot.


#include <Wire.h>
#include "RTClib.h"
#include <Servo.h>
//#include <DigiKeyboard.h>


// Alimentação do circuito em +5,0V
RTC_DS3231 rtc; //objeto do tipo RTC_DS3231 (Conexões elétricas: SDA(RTC)-> P0(Attiny85); SCL(RTC)-> P2(Attiny85) )
Servo servo; //objeto servo motor
int servo_pin = 3; //porta conectada ao servo motor (Conexões elétricas: Servo(Dado)->P1(Attiny85))
int angle_opened = 45 ; // angulo em graus do microservo para o alimentador aberto
int angle_closed = 80;// angulo em graus do microservo para o alimentador fechado

void setup()
{
  Serial.begin(9600); //INICIALIZA A SERIAL
  delay(3000);
  servo.attach(servo_pin); //servo conectado ao servo_pin 
     
   if(! rtc.begin()) 
    { 
      servo.write(angle_closed);   
      while(1); 
    }
  if(rtc.lostPower())
  {//SE RTC FOI LIGADO PELA PRIMEIRA VEZ / FICOU SEM ENERGIA / ESGOTOU A BATERIA, FAZ
    //REMOVA O COMENTÁRIO DE UMA DAS LINHAS ABAIXO PARA INSERIR AS INFORMAÇÕES ATUALIZADAS EM SEU RTC
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
   //rtc.adjust(DateTime(2018, 9, 29, 15, 00, 45)); //(ANO), (MÊS), (DIA), (HORA), (MINUTOS), (SEGUNDOS)
   } 
}

void loop() {
DateTime now = rtc.now(); 
 //Definição dos horários para acionar o alimentador
//DateTime now = rtc.now();
// Serial.print(now.year(), DEC);
//    Serial.print('/');
//    Serial.print(now.month(), DEC);
//    Serial.print('/');
//    Serial.print(now.day(), DEC);
//    Serial.print(" (");
//    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();


// Primeira abertura do alimentador às 09:00:00  mentador permanece fechado durante os outros horarios do dia
  if ((now.hour()== 9)||(now.hour()== 12)||(now.hour()== 19)) // horas
  {
   if(now.minute() == 11)//minutos
    {    
         if(now.second() == 0)//segundos
          {    
           servo.write(angle_opened); 
           delay(3000); 
           servo.write(angle_closed);
           }
    } else servo.write(angle_closed); 
  }else servo.write(angle_closed);
 
 //Segunda abertura do alimentador às 12:00:00
  if (now.hour()== 19) // horas
  {
   if(now.minute() == 11)//minutos
    {    
         if(now.second() == 0)//segundos
          {    
           servo.write(angle_opened); 
           delay(3000); 
           servo.write(angle_closed);
           }
    } else servo.write(angle_closed); 
  }else servo.write(angle_closed);

// Terceira abertura do alimentador às 20:00:00
  if (now.hour()== 19) // horas
  {
   if(now.minute() == 13)//minutos
    {    
         if(now.second() == 0)//segundos
          {    
           servo.write(angle_opened); 
           delay(3000); 
           servo.write(angle_closed);
           }
    } else servo.write(angle_closed); 
  }else servo.write(angle_closed);
}
