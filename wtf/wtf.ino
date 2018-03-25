#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <string.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

SoftwareSerial SIM800L(8, 7); // RX | TX
SoftwareSerial ss(RXPin, TXPin);

double longtitude, latitude;
char msg[] = "lol";
String Grsp;
char command[] = "GPS";
int result = 2;
int compare = 1;
TinyGPSPlus gps;

void setup() {
    Serial.begin(9600);
    SIM800L.begin(9600);  
    ss.begin(GPSBaud);
    
    setStart();
    setReceive();
}
 
void loop() {
  gpsData();
  receiveSMS();
  //Grsp.c_str();
  if(Grsp.indexOf("GPS") == 0){
    result = 1;
  }
      
  //Serial.print(compare);
  delay(1000);

  sendGPS();
}

void receiveSMS(){
   if(SIM800L.available()) {
    Grsp = SIM800L.readString(); //Read data received from SIM800L GSM Module
    Serial.print(Grsp);
    delay(500);  
  }
}

void gpsData(){
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      //Serial.print("Latitude= "); 
      //Serial.print(gps.location.lat(), 6);
      latitude = gps.location.lat();
      //Serial.print(" Longitude= "); 
      //Serial.println(gps.location.lng(), 6);
      latitude = gps.location.lng();
    }
    delay(1000);
  }
}

void setStart(){
    while(!Serial);    
  
    //Serial.println("Arduino with Module GSM is ready");
    //Serial.println("Module dimulai pada serial komunikasi 9600");
    delay(1000);
    //Serial.println("SIM800L SIAP DIGUNAKAN!");
   
    //Serial.println("Set format SMS ke ASCII"); 
    SIM800L.write("AT+CMGF=1\r\n");
    delay(1000); 
 
    //Serial.println("SIM800 Set SMS ke Nomor Tujuan");
    SIM800L.write("AT+CMGS=\"087784851245\"\r\n");
    delay(1000);
   
    //Serial.println("Module mengirimkan SMS ke no tujuan");
    SIM800L.write(msg); 
    delay(1000);
   
    //Serial.println("Ketik pada keyboard Ctrl+Z atau ESC > keluar menu ini");
    SIM800L.write((char)26);
    delay(1000); 
    //Serial.println("SMS Selesai Dikirim!");
}

void setReceive(){
    //Serial.println("Testing GSM SIM800L");
    SIM800L.begin(9600);
    SIM800L.println("AT"); //checking
    delay(1000);
    SIM800L.println("AT+CMGF=1");  //Set to Text mode
    delay(1000);
    SIM800L.println("AT+CNMI=1, 2, 0, 0, 0"); //Set to notification for new message, New message indication
}

void sendGPS(){
    if(result = 1){
      while(!Serial);    
      delay(1000);
   
      SIM800L.write("AT+CMGF=1\r\n");
      delay(1000); 
  
      SIM800L.write("AT+CMGS=\"087784851245\"\r\n");
      delay(1000);
   
      SIM800L.write(longtitude);
      SIM800L.write(latitude);
      delay(1000);
      result = 2;
    }  
}


