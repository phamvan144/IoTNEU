#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define sensor A1
#define led 13
#define motor 8
int rainSensor = 6;
const int DHTPIN = 2;
const int DHTTYPE = DHT11;


LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(DHTPIN, DHTTYPE);


void setup() 
{

  Serial.begin(9600);
  dht.begin();
  lcd.begin();  //khởi động màn hình LCD
  lcd.backlight();  //   Bật đèn nền
  lcd.setCursor(1,0);
  lcd.print("XIN CHAO MOI NGUOI");
  lcd.setCursor(5,1);
  lcd.print("SAU DAY LA:");
  lcd.setCursor(6, 2);
  lcd.print("HE THONG");
  lcd.setCursor(2, 3);
  lcd.print("TUOI CAY TU DONG");
  delay(1000);
  lcd.clear();
  pinMode(rainSensor, INPUT);
  pinMode(sensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(motor, OUTPUT);

}


void loop() 
{

  float doam = dht.readHumidity();
  float nhietdo = dht.readTemperature();
  int cbm= digitalRead(rainSensor);
  int dad = analogRead(sensor);
  dad = map(dad, 0, 1023, 0, 100);
  
  lcd.setCursor(0, 1);
  lcd.print("Nhiet do:");
  lcd.setCursor(11, 1);
  lcd.print(nhietdo);
  lcd.setCursor(15, 1);
  lcd.print("(C)");
  lcd.setCursor(0, 2);
  lcd.print("Do am:");
  lcd.setCursor(11, 2);
  lcd.print(doam);
  lcd.setCursor(15, 2);
  lcd.print("(%)");
  lcd.setCursor(0,3);
  lcd.print("Do am dat:");
  lcd.setCursor(11, 3);
  lcd.print(dad);
  lcd.setCursor(15, 3);
  lcd.print("(%)");

  if (cbm == LOW) 
  {
    Serial.println("Không mưa");
    lcd.setCursor(0, 0);
    lcd.print("Khong mua ");

    if (dad < 100||nhietdo <100)
      {

        lcd.setCursor(13, 0);
        lcd.print(' ');
      
      } 

    else if (dad < 10||nhietdo<10)
      {

        lcd.setCursor(12, 0);
        lcd.print(' ');
      
      }

    if (dad >= 85)
    {

      if (nhietdo >= 37 ) 
      {

        digitalWrite(led, HIGH);
        digitalWrite(motor, HIGH);
        lcd.setCursor(10,0);
        lcd.print(" Motor bat   ");
      
      }
      
      else
      {

        digitalWrite(led, LOW);
        digitalWrite(motor, LOW);
        lcd.setCursor(10, 0);
        lcd.print(" Motor tat   ");
      
      }

    }
    
    else if (dad >= 60 && dad <85)
    {

      if (nhietdo >= 32) 
      {

        digitalWrite(led, HIGH);
        digitalWrite(motor, HIGH);
        lcd.setCursor(10,0);
        lcd.print(" Motor bat   ");
      
      }
      
      else
      {
        
        digitalWrite(led, LOW);
        digitalWrite(motor, LOW);
        lcd.setCursor(10, 0);
        lcd.print(" Motor tat   ");
     
      }
    
    }

    else if (dad >= 30 && dad <60)
    {

      if (nhietdo >= 24) 
      {

        digitalWrite(led, HIGH);
        digitalWrite(motor, HIGH);
        lcd.setCursor(10,0);
        lcd.print(" Motor bat   ");
      
      }
      
      else
      {
        
        digitalWrite(led, LOW);
        digitalWrite(motor, LOW);
        lcd.setCursor(10, 0);
        lcd.print(" Motor tat   ");
     
      }
    
    }

    else 
    {

      digitalWrite(led, HIGH);
      digitalWrite(motor, HIGH);
      lcd.setCursor(10, 0);
      lcd.print(" Motor bat");
      
    }

  }
  
  else 
  {
    
    Serial.println("Có mưa");
    lcd.setCursor(0,0);
    lcd.print("Co mua ");
    lcd.print(" Motor tat   ");
    digitalWrite(led, LOW);
    digitalWrite(motor, LOW);
  
  }
  
}









