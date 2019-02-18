#include <RTClib.h> // Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
int valve = 1;
int v1 = 2;
int v2 = 3;
int value=0;
const int hygrometer = A0;
RTC_DS1307 rtc;
void setup () 
{ pinMode(v1,OUTPUT);
  pinMode(v2,OUTPUT);
  Serial.begin(9600);
  digitalWrite(v1,0);
  digitalWrite(v2,0);

  if (! rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) 
  {
    Serial.println("Wait for the pump to start!");
  }
  
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
    //rtc.adjust(DateTime(2019, 2, 17, 0, 36, 0));// to set the time manualy 
  
}

void loop () 
{   //Serial.print("Select The Field to be irrigated 1 or 2\n");
    

    DateTime now = rtc.now();
    String time_from_user="10:18";
    delay(1000);
    String DateTimeString= String(now.hour(),DEC) + ":"+String(now.minute(),DEC);
    Serial.print(DateTimeString+"\n");
    if(DateTimeString==time_from_user)
    { if(valve == 1)
      { value = analogRead(hygrometer);   //Read analog value 
        value = constrain(value,400,1023);  //Keep the ranges!
        value = map(value,400,1023,100,0);  //Map value : 400 will be 100 and 1023 will be 0
        while(1)
        { if(value<80)
          { value = analogRead(hygrometer);   //Read analog value 
            value = constrain(value,400,1023);  //Keep the ranges!
            value = map(value,400,1023,100,0);  //Map value : 400 will be 100 and 1023 will be 0
            Serial.println("Irrigating The Field");
            Serial.print("Soil humidity: ");
            Serial.println(value);
            digitalWrite(v1,1);
            digitalWrite(v2,0);
            delay(1000);
          } 
          else
          {
              Serial.println("Stopped Irrigating The Field");
              Serial.print("Soil humidity: ");
              Serial.println(value);
              delay(5000);
              digitalWrite(v1,0);
              digitalWrite(v2,0);
              break;
          }
        }
        delay(500);
      }
      else if(valve == 2)
      
      { Serial.print("field 2 is being irrigated");
        digitalWrite(v2,1);
        digitalWrite(v1,0);
      while(1)
        { if(value<50)
          { Serial.println("Irrigating The Field");
            digitalWrite(v1,1);
            digitalWrite(v2,0);
            delay(1000);
          } 
          else
          {
              Serial.println("Stopped Irrigating The Field");
              delay(5000);
              break;
          }
        } 
      }
    }    
}
    
