#include <TinyGPS++.h>
#include <SoftwareSerial.h>
 
TinyGPSPlus gps;
 
SoftwareSerial ss(10, 11);
SoftwareSerial SIM900(2, 3);
 
char text[180];
char latitude[12];
char longitude[12];
 
void setup()
{
  Serial.begin(115200);
  SIM900.begin(9600);
  delay(2000);
  ss.begin(9600);
  delay(2000);
 
}
 
void loop()
{
   ss.listen();
   delay(2000);
    while (ss.available() > 0) {
    gps.encode(ss.read());
 
  if (gps.location.isUpdated())
  {
        strcpy(text, "comgooglemaps://?q=");
        dtostrf(gps.location.lat(), 1, 6, latitude);
        strcat(text,latitude);
        strcat(text,",");
        dtostrf(gps.location.lng(), 1, 6, longitude);
        strcat(text,longitude);
        delay(200);
        sendSMS(); 
        delay(2000);
  }
 } 
}
 
void sendSMS()
{
  Serial.println(text);
  Serial.println("sending SMS");
  SIM900.listen();
  delay(300);
  SIM900.print("AT+CMGF=1\r");                                                     
  delay(100);
  SIM900.println("AT+CMGS=\"phone number\"");                                     
  delay(100);
  SIM900.println(text);        // message to send
  delay(100);
  SIM900.println((char)26);                     
  delay(100);
  SIM900.println();
  delay(9000);
}
