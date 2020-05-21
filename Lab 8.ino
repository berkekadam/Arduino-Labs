#include <LiquidCrystal.h>

int SCREEN_TIME_SENSOR = 1000;	// 1 second for showing sensor values
int SCREEN_TIME_FIRE_STATUS  = 1000;   // 1 second for showing fire status

bool heatAlert = false;
int heatValue;
int SENSOR_TEMPERATURE_HIGH = 80; //heatstrong
float fahrenheit;
bool smokeAlert = false;
float smokeValue;
float SENSOR_GAS_EMISSION = 200;  //smoke strong
int lightValue;
int SENSOR_LIGHT_BRIGHT = 679; 
int SENSOR_LIGHT_DARK = 500 ;
int SENSOR_LIGHT_VERY_DARK = 200; 

int genelTime;
int newTime = 0; //must be defined 0 to enter the loop
int newTime2 = 0;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
}

void loop() {
  
  lcd.begin(16,2);	
	
     genelTime = millis(); //genelTime is for total time
    
    while (newTime - genelTime < SCREEN_TIME_SENSOR) {	
		newTime=millis();
      	Values();
      	delay(1000);
    }
  	
  	while (newTime2 - genelTime < SCREEN_TIME_FIRE_STATUS) {	
		newTime2=millis();
      	IsThereFire();
      	delay(1000);
    }
      		
}


void Values(){
  lcd.begin(16,2);
  heatValue = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  //heatValue=analogRead(A0);
  smokeValue=analogRead(A1);
  lightValue=analogRead(A2);
  fahrenheit = (heatValue*1.8)+32;
  lcd.setCursor(0,0);
  lcd.print("TE");
  lcd.print(":");
  lcd.print(heatValue);
  lcd.print("C");
  lcd.print("|");
  lcd.print(fahrenheit);
  lcd.print(" F");
  
  lcd.setCursor(0,1);//Line 2
  lcd.print("GS");
  lcd.print(":");
  lcd.print(smokeValue);
  lcd.print("|LS");
  lcd.print(":");
  lcd.print(lightValue);

}

void IsThereFire(){

  lcd.begin(16,2);
  heatValue = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  smokeValue=analogRead(A1);
  lightValue=analogRead(A2);
  if(heatValue>SENSOR_TEMPERATURE_HIGH){
	  heatAlert=true; //heat is Strong
  }
  else{
	  heatAlert=false; //heat is Negligable
  }
  
  if(smokeValue>SENSOR_GAS_EMISSION){
	  smokeAlert=true;
  }
  else{
	  smokeAlert=false;
  }
  
  if (heatAlert==true && smokeAlert==true && lightValue<=SENSOR_LIGHT_DARK && lightValue>SENSOR_LIGHT_VERY_DARK){
	lcd.setCursor(0,0);	  
	lcd.print("TF1 WOOD FIRE");
	lcd.setCursor(0,1);
	lcd.print("CELLULOSE OPEN");
  }
  else if (heatAlert==false && smokeAlert==true && lightValue>SENSOR_LIGHT_DARK){
	lcd.setCursor(0,0);	  
	lcd.print("TF2 OR TF3 FIRE");
	lcd.setCursor(0,1);
	lcd.print("WOOD OR COTTON");
  }
  else if (heatAlert==true && smokeAlert==true && lightValue<=SENSOR_LIGHT_VERY_DARK){
	lcd.setCursor(0,0);	  
	lcd.print("TF4 OR 5 FIRE");
	lcd.setCursor(0,1);
	lcd.print("POLYUR PR N-HEPT");
  }
  else if (heatAlert==true && smokeAlert==false){
	lcd.setCursor(0,0);	  
	lcd.print("TF 6 ETHANOL");
	lcd.setCursor(0,1);
	lcd.print("LIQUID FIRE");
  }
  else if (heatAlert==false && smokeAlert==true && lightValue<=SENSOR_LIGHT_VERY_DARK){
	lcd.setCursor(0,0);	  
	lcd.print("TF8 DECALINE");
	lcd.setCursor(0,1);
	lcd.print("LIQUID FIRE");
  }
  else{
    lcd.setCursor(0,0);	  
	lcd.print("NO FIRE DETECTED");
  }

 
}

