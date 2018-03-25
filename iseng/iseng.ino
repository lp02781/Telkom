#include <TinyGPS++.h>
TinyGPSPlus gps;
double latitude, longitude;

#include <SoftwareSerial.h>
SoftwareSerial SIM800L(7, 8);

String response;
int lastStringLength = response.length();

String link;

void setup() {
  Serial.begin(9600);
  Serial.println("GPS Mulai");

    SIM800L.begin(9600);  
    SIM800L.println("AT+CMGF=1");
    Serial.println("SIM800L started at 9600");
    delay(1000);
    Serial.println("Setup Complete! SIM800L is Ready!");
    SIM800L.println("AT+CNMI=2,2,0,0,0");
 
}

void loop() {
int EMPAT = 4;
  if (SIM800L.available()>0){
      response = SIM800L.readStringUntil('\n');
  }
  if(lastStringLength != response.length()){
      GPS();
      //Perintah ON
      if(response.indexOf("ON") == EMPAT){
       Serial.print("nemu");
      }
  }
}

void GPS(){
  if(Serial.available()) {
    gps.encode(Serial.read());
  }
  if(gps.location.isUpdated()) {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    link = "www.google.com/maps/place/" + String(latitude, 6) + "," + String(longitude, 6) ;
     }
}


