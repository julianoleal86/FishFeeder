#include <Wire.h>
#include "RTClib.h"
#include <Servo.h>

// +5,0V supply voltage
RTC_DS3231 rtc; // (wiring: SDA(RTC)-> P0(Attiny85); SCL(RTC)-> P2(Attiny85) )
Servo servo; 
int servo_pin = 3; //(wiring: Servo(Dado)->P1(Attiny85))
int angle_opened = 45 ; // angle in degrees to open the feeder
int angle_closed = 80;// angle in degrees to close the feeder 

void setup()
{
 // Uncomment the line below only if you want to view the adjusted the rtc data
 // Serial.begin(9600); //initialize the serial monitor 
 // delay(3000);
  
 servo.attach(servo_pin);      
   if(! rtc.begin()) 
    { 
      servo.write(angle_closed);   
      while(1); 
    }
  if(rtc.lostPower())
  { // Choose only one rtc.adjust function
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
    // This line sets the RTC with an explicit date & time, for example to set January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
   } 
}
void loop() {
DateTime now = rtc.now(); // get the time now
// Uncomment the following lines to visualize the adjusted time at the serial monitor
//    Serial.print(now.hour(), DEC);
//    Serial.print(':');
//    Serial.print(now.minute(), DEC);
//    Serial.print(':');
//    Serial.print(now.second(), DEC);
//    Serial.println();

// Time setup
  if ((now.hour()== 9)||(now.hour()== 12)||(now.hour()== 19)) // hour
  {
   if(now.minute() == 26)//minute
    {    
         if(now.second() == 0)//second
          {    
           servo.write(angle_opened); 
           delay(3000); 
           servo.write(angle_closed);
           }
    } else servo.write(angle_closed); 
  }else servo.write(angle_closed);
  
}
