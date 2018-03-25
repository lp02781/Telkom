

/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */
 
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <gprs.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

String response, link;
int lastStringLength = response.length();

GPRS gprs;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  ss.begin(GPSBaud);
  while(!Serial);
  Serial.println("SIM800L Demo Send SMS via Seeeduino");
  gprs.preInit();
  delay(1000);
  while(0 != gprs.init()) {
      delay(1000);
      Serial.print("init error\r\n"); //pesan di Serial Monitor jika proses init module GPRS Gagal
  }  
  Serial.println("Init succes..."); //pesan di Serial Monitor jika proses init module GPRS Sukses
  delay(1000);
  
  //Format Coding Kirim SMS
  gprs.sendSMS("087784851245","Test Send SMS with Seeeduino Lib"); //define phone number and text

}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
  }
}


