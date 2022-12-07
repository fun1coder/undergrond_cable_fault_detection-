#define BLYNK_TEMPLATE_ID "TMPLl4tIWryV"
#define BLYNK_DEVICE_NAME "undergroundproject"
#define BLYNK_AUTH_TOKEN "XaRwHh6-n0mRFGpT_8ugttWGIxKNTX5B"
#include <SoftwareSerial.h>
SoftwareSerial mySUART(4, 5);  //D2, D1
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "guru";
char pass[] = "guru1234";
String x;
// Attach virtual serial terminal to Virtual Pin V1
WidgetTerminal terminal(V0);
BLYNK_CONNECTED() 
{
    Blynk.syncAll();
}
void setup() 
{
    Serial.begin(9600);
    mySUART.begin(9600);
    terminal.clear();
    terminal.flush();
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}
void loop() 
{
    Blynk.run();
    if(mySUART.available()>0)
  {
   //    Serial.print(mySUART.readString());
     x=mySUART.readString();
     Serial.print(x);
     terminal.print(x);
     
     
      terminal.flush();
    
  }  
   terminal.println("underground project success");
   delay(1000);
}