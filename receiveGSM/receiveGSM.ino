
#include <SoftwareSerial.h>

String Grsp;
SoftwareSerial gsm(8,7); // RX, TX

void setup() {
  Serial.begin(9600);
  Serial.println("Testing GSM SIM800L");
  gsm.begin(9600);
  gsm.println("AT"); //checking
  delay(1000);
  gsm.println("AT+CMGF=1");  //Set to Text mode
  delay(1000);
  gsm.println("AT+CNMI=1, 2, 0, 0, 0"); //Set to notification for new message, New message indication
}

void loop() {
  if(gsm.available()) {
    //Check if GSM Send any data
    Grsp = gsm.readString(); //Read data received from SIM800L GSM Module
    Serial.print(Grsp);
    delay(500);  
  }
}
