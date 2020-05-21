#include <LiquidCrystal.h>

int SCREEN_DEFAULT_TIME = 7000; //7000 msecs equals 7 sec
int SCREEN_INFO_TIME  = 3000; //3000 msecs equals 3 sec

int genelTime;
int newTime = 0; //must be defined to enter the loop
int newTime2;
int hour=23;
int min=59;
int sec=50;
int day=30;
int mon=12;
int year=2020;
int daypointer=2;
int daypasser=1;
int buttonState = 0;

 char DowTr [7] [7] = {  { "Pzt" },  { "Sal" },  { "Car" },  { "Per" },  { "Cum" },  { "Cts" },  { "Paz" },
  };

char DowEng [7] [7] = { { "Mon" }, { "Tue" }, { "Wed" }, { "Thu" }, { "Fri" }, { "Sat" }, { "Sun" },
 };

boolean  AMPM = true; // PM is true
boolean  Language = true; // English is True
int buttonPin = 8;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT);
}

void loop() {
  
  lcd.begin(16,2);	
  
  if(Language == true){ //ENGLISH
    
    genelTime = millis(); //genelTime is for total time
    
    while (genelTime - newTime < SCREEN_DEFAULT_TIME) {	
		newTime=millis(); //newTime is for keeping the time passed under Default format
      		if (newTime - genelTime > SCREEN_DEFAULT_TIME){ //Info screen after 7 seconds
              newTime2=millis(); //newTime2 is for keeping the time passed under Info format
              
              while (newTime2-newTime < SCREEN_INFO_TIME){ // This inner loop is for 3 seconds for info screen
                EngInf(); //info screen
                buttonState = digitalRead(buttonPin);
                 if (buttonState == HIGH) {
                         Language = !Language;
                      }
                delay(500);
                newTime2=millis();
                } //inside while 
               		if (newTime2-newTime > SCREEN_INFO_TIME){ //if time passed under inner loop passes 3 secs, break
                  	break;
              		}  		  
            }
     			EngDef(); //Default Screen
      			buttonState = digitalRead(buttonPin);
                 if (buttonState == HIGH) {
                         Language = !Language;
                      }
      			delay(1000); //delay to visualize properly
      
    }
  }
	
  else if(Language == false){ //TURKISH
    genelTime = millis();
    while (genelTime - newTime < SCREEN_DEFAULT_TIME) {	
		newTime=millis();
      		if (newTime - genelTime > SCREEN_DEFAULT_TIME){ 
              newTime2=millis();
              while (newTime2-newTime < SCREEN_INFO_TIME){ 
                TurInf();
                buttonState = digitalRead(buttonPin);
                 if (buttonState == HIGH) {
                         Language = !Language;
                      }
                delay(500);
                 
                newTime2=millis();
              } 
              	if (newTime2-newTime > SCREEN_INFO_TIME){
                  break;
                }
            }
      
     	TurDef();
      		buttonState = digitalRead(buttonPin);
      		if (buttonState == HIGH) {
                       Language = !Language;
            }
        delay(1000);
      		
    }
  }
}

void EngDef(){

  lcd.begin(16,2);
  
  sec=sec+1;
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
   daypasser = daypasser+1;
     hour=0;
     day++;
     daypointer++;
     if (daypointer==7) {
      daypointer =0;
   }
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
  if(year==year+1)
  {
   year= year+1;
  }
  
   if (hour>11){
    AMPM = true;
  }
  else if(hour<=11){
   AMPM = false;   
  }

  lcd.setCursor(0,0);
  if((hour%12)<10 && AMPM==true){
    if(hour==0){
      lcd.print("12");
    }
    else{
  lcd.print("0");
  lcd.print(hour %12);
    }
    }
  else if ((hour%12)<10 && AMPM==false){
    lcd.print("12");
  }
  else{
    lcd.print(hour %12);
  }
  lcd.print(":");
  if(min<10)lcd.print("0");
  lcd.print(min);
  lcd.print(":");
  if(sec<10)lcd.print("0");
  lcd.print(sec);
  
  if(AMPM) lcd.print(" PM");
  else lcd.print(" AM");

  lcd.print("  ENG");

  lcd.setCursor(0,1);//Line 2

  if(day<10)lcd.print("0");
  lcd.print(day);
  lcd.print(".");
  if(mon<10)lcd.print("0");
  lcd.print(mon);
  lcd.print(".");

  lcd.print(year);


  lcd.print("   ");
  lcd.print(DowEng[daypointer]);

}


void EngInf(){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("HH");
  lcd.print(":");
  lcd.print("MM");
  lcd.print(":");
  lcd.print("SS");

  lcd.print(" 12H ENG");

  lcd.setCursor(0,1);//Line 2

  lcd.print("DD");
  lcd.print(".");
  lcd.print("MM");
  lcd.print(".");

  lcd.print("YY");


  lcd.print("   ");
  lcd.print("  DOW");

}

void TurInf(){
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("HH");
  lcd.print(":");
  lcd.print("MM");
  lcd.print(":");
  lcd.print("SS");

  lcd.print(" 24H TUR");

  lcd.setCursor(0,1);//Line 2

  lcd.print("DD");
  lcd.print(".");
  lcd.print("MM");
  lcd.print(".");

  lcd.print("YY");


  lcd.print("   ");
  lcd.print("  DOW");

}


void TurDef(){
    lcd.begin(16,2);
    sec=sec+1;
    if(sec==60){
     sec=0;
     min=min+1;
    }
    if(min==60)
    {
     min=0;
     hour=hour+1;
    }
    if(hour == 24)//daypassing
    {
     hour=0;
	 day=day+1;
     daypasser = daypasser+1;
     if (daypasser >1) {
       daypasser =0;
       daypointer++;
       if (daypointer==7) {
        daypointer =0;
       }
     }
     AMPM= !AMPM;
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
    if(year==year+1)
    {
     year= year+1;
    }

	


    lcd.setCursor(0,0);
    if(hour<10)lcd.print("0");
    lcd.print(hour);
    lcd.print(":");
    if(min<10)lcd.print("0");
    lcd.print(min);
    lcd.print(":");
    if(sec<10)lcd.print("0");
    lcd.print(sec);

    lcd.print("     TUR");

    lcd.setCursor(0,1);//Line 2

    if(day<10)lcd.print("0");
    lcd.print(day);
    lcd.print(".");
    if(mon<10)lcd.print("0");
    lcd.print(mon);
    lcd.print(".");

    lcd.print(year);


    lcd.print("   ");
    lcd.print(DowTr[daypointer]);



}