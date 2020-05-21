#include <LiquidCrystal.h>
#define PIN_TRIG 	(8)
#define PIN_ECHO	(9)
#define PIN_BUZZ	(7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int hour =23;
int min=59;
int sec =40;
int day =30;
int mon =12;
int year =2019;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_BUZZ, OUTPUT);
  
  digitalWrite(PIN_TRIG, LOW);
}

void loop() {

  float beepDelay;
  long duration;
  int distance;
  
  
  digitalWrite(PIN_TRIG, LOW); 
  delayMicroseconds(5); 
  digitalWrite(PIN_TRIG, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(PIN_TRIG, LOW); 
  duration = pulseIn(PIN_ECHO, HIGH);
  
  // DATE-TIME START
  
   if(sec >= 60){
    sec=0;
    min=min+1;
   }
   if(min == 60)
   {
   min=0;
   hour=hour+1;
   }
   if(hour == 24) //daypassing
   {
     day++;
     hour = 0;
   }
   if(day==31){
   day=1;
   mon=mon+1;
   }
   if(mon==13)
   {
   mon=1;
   year=year+1;
   }
   Serial.print("Date: ");
  if (day<10)  {
    Serial.print("0");
    Serial.print(day);
  }
   else		Serial.print(day);
  Serial.print(".");
   if (mon<10) 
   {
     Serial.print("0");
     Serial.print(mon);
   }
   else		Serial.print(mon);
  Serial.print(".");
   Serial.print(year);
   Serial.print(" - Hour: ");
  if (hour<10) 
   {
     Serial.print("0");
     Serial.print(hour);
   }
   else		Serial.print(hour);
  Serial.print(":");
  if (min<10) 
   {
     Serial.print("0");
     Serial.print(min);
   }
   else		Serial.print(min);
  
  // DATE TIME END
  
  distance = (duration/2) / 29.1;
  lcd.begin(16,2);
  Serial.print(" - Distance: ");
  Serial.print(distance);
  Serial.println(" cm.");
  lcd.setCursor(0,0);
  lcd.print(distance);
  lcd.print(" CM");
  beepDelay = distance;	// Delay direcctly proportional with distance.
  lcd.setCursor(0,1);  
  
  if (distance<20 && distance>5){	
      Serial.println("It is too close.");
      lcd.print("TOO CLOSE");  
      tone(PIN_BUZZ,1000,1000);
 	  delay(beepDelay);		// Delay directly proportional with distance.
  }
  else if (distance<=100 && distance >=20){	
      Serial.println("It is close.");
    	lcd.print("CLOSE");
      tone(PIN_BUZZ,1000,500);
 	  delay(beepDelay);
  }
  else if (distance> 100)	{ 
      Serial.println("It is far.");
      lcd.print("FAR");
  	  tone(PIN_BUZZ,1000,30);
 	  delay(beepDelay);  
      noTone(PIN_BUZZ);
      delay(beepDelay);
  }  
  else if(distance<=5){
    Serial.println("Crashed :(");
    lcd.print("CAR CRASH");  //Game over sound when car crashed.
   tone(PIN_BUZZ, 500, 500);
    delay(200);
    tone(PIN_BUZZ, 300, 300);
    delay(200);
     tone(PIN_BUZZ, 200, 350);
    delay(200);
     tone(PIN_BUZZ, 200, 400);
    delay(200);
     tone(PIN_BUZZ, 225, 250);
    delay(200);
     tone(PIN_BUZZ, 200, 888);
    delay(200);
    tone(PIN_BUZZ, 700, 722);
    delay(200);
    tone(PIN_BUZZ, 200, 100); 
  }
  Serial.println("------------------------------");
  delay(1000);
  sec++;
}

 