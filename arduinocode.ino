#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
SoftwareSerial mySUART(8,9);
LiquidCrystal lcd(2,3,4,5,6,7);

#define sensor A1

#define relay1 10
#define relay2 11
#define relay3 12

#define buzzer 13  

int read_ADC;
int distance=0;
float disvalue=0;


byte symbol[8] = {
        B00000,
        B00100,
        B00100,
        B00100,
        B11111,
        B01110,
        B00100,
        B00000};

void setup() {
pinMode(sensor,INPUT); 

pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
digitalWrite(relay1,HIGH);
digitalWrite(relay2,HIGH);
digitalWrite(relay3,HIGH);

pinMode(buzzer, OUTPUT);
 Serial.begin(9600);
  mySUART.begin(9600);

lcd.createChar(1, symbol);
    
lcd.begin(16, 2);
lcd.clear();
lcd.setCursor(0, 0); // set the cursor to column 0, line 2
lcd.print("3 Phase UG Cable");
lcd.setCursor(0, 1); // set the cursor to column 0, line 2
lcd.print("Fault  Detection");
delay(2000);
lcd.clear();
}

void loop(){

int r=0,y=0,b=0;
distance=0;
  
lcd.setCursor(1,0);
lcd.print("R");
lcd.write(1);  

lcd.setCursor(7,0);
lcd.print("Y");
lcd.write(1); 

lcd.setCursor(13,0);
lcd.print("B");
lcd.write(1); 
        
digitalWrite(relay1,LOW);
digitalWrite(relay2,HIGH);
digitalWrite(relay3,HIGH);  
delay(500);

data();
lcd.setCursor(0,1);
if(distance>0){lcd.print(disvalue); lcd.print("KM  "); r=distance;
mySUART.print("R-phase : ");
mySUART.print(disvalue);
mySUART.print("KM");
  
  }
else{lcd.print(" NF ");
mySUART.print("R phase : no fault");}
 
digitalWrite(relay1,HIGH);
digitalWrite(relay2,LOW);
digitalWrite(relay3,HIGH);  
delay(500);

data();

lcd.setCursor(6,1);
if(distance>0){lcd.print(disvalue); lcd.print("KM  "); y=distance;
mySUART.print("   Y-phase : ");
mySUART.print(disvalue);
mySUART.print("KM");}
else{lcd.print(" NF ");
mySUART.print("   Y phase : no fault");}

digitalWrite(relay1,HIGH);
digitalWrite(relay2,HIGH);
digitalWrite(relay3,LOW);  
delay(500);

data();

lcd.setCursor(12,1);
if(distance>0){lcd.print(disvalue); lcd.print("KM  ");b=distance;
mySUART.print("   B-phase : ");
mySUART.print(disvalue);
mySUART.print("KM");}
else{lcd.print(" NF ");
mySUART.print("   B phase : no fault");
}
delay(1000);
lcd.clear();
delay(1000);

if(r==y&&y==b&&b==r&&r>0&&y>0&&b>0)
{
 lcd.setCursor(1,0);
 lcd.print("Type of Fault");
 lcd.setCursor(1,1);
  lcd.print("L-L-L or LLL-G");
  mySUART.write("    Type of fault : L-L-L or l-l-l-g fault\n");
 
  r=y=b=0;
    delay(2000);
  lcd.clear();
}
else if(r==y||y==b||b==r)
{
  if((r>0&&y>0)||(y>0&&b>0)||(b>0&&r>0)){
  lcd.setCursor(1,0);
lcd.print("Type of Fault");
lcd.setCursor(1,1);
  lcd.print("L-L or L-L-G");
   mySUART.write("    Type of fault : L-L or l-l-g fault\n");
 
  r=y=b=0;
    delay(2000);
  lcd.clear();
  }
  else if(r>0||y>0||b>0)
  {
    lcd.setCursor(1,0);
lcd.print("Type of Fault");
lcd.setCursor(1,1);
  lcd.print("L-G");
   mySUART.write("    Type of fault : L-G fault\n");
  r=y=b=0;
    delay(2000);
  lcd.clear();
  }
  else
  {
     lcd.setCursor(1,0);
lcd.print("NO Fault");
 mySUART.write("    No fault detected\n");
lcd.setCursor(1,1);
lcd.print("Detected");
  r=y=b=0;
    delay(2000);
  lcd.clear();
  }
}



}


void data(){
read_ADC = analogRead(sensor);  
distance = read_ADC/100;
disvalue= read_ADC/100.00  ;



if(distance>=9)distance = 0;


if(distance>0){

digitalWrite(buzzer,HIGH);
delay(200);
digitalWrite(buzzer,LOW);  
delay(200);
 }
}