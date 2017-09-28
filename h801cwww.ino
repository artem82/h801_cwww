/*
Данный скетч работает с платой H801 для реализации двуцветного освещения
Поддержка OTA

Red Gpio: 15
Green Gpio: 13
Blue Gpio:  12

If you have a rgbw stripe check "Enable WW Channel"
WW Gpio:  14
WW Color Temp (Kelvin): 2000 //This depends on your leds but 2000 should be fine for warm white

If you have a rgbww stripe also check "Enable CW Channel"
CW Gpio:  4
CW Color Temp (Kelvin): 6000 //This depends on your leds but 6000 should be fine for cold white

Red is on GPIO15
Green is on GPIO13
Blue is on GPIO12
White 1 (W1) is on GPIO14 is WW
White 2 (W2) is on GPIO4  is CW
There are two on board LEDs, a red one on GPIO5 and a green on GPIO 1.

https://github.com/instalator/Sonoff_basic/blob/master/main.ino
https://github.com/instalator/Sonoff_basic_OTA
 *  VER 0.2
 */

#include <ESP8266WiFi.h> 
#include <PubSubClient.h>       //mqtt
#include <WiFiUdp.h>            //ota 
#include <ArduinoOTA.h>         //ota

const char* ssid = "ArtHome";
const char* password = ".........";
const char* mqtt_server = "192.168.1.101"; //Сервер MQTT

IPAddress ip(192,168,1,206); //IP модуля
IPAddress gateway(192,168,1,1); // шлюз
IPAddress subnet(255,255,255,0); // маска

WiFiClient espClient;
PubSubClient client(espClient);

/***RGBWW
#define LEDg    1
#define LEDr    5
#define REDc    15
#define GREENc  13
#define BLUEc   12
#define WW      14  //W1   2700
#define CW      4   //W2   6500
*/
#define LEDg    1
#define LEDr    5
#define REDc    15
#define GREENc  13
#define BLUEc   12
#define WW      14  //W1   2700
#define CW      4   //W2   6500

int CWvalue,WWvalue;  //шим от 0 до 1023

long previousMillis = 0;

void setup_wifi() {
  delay(10);
  // ***WIFI Setup***
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    digitalWrite(LEDg, !digitalRead(LEDg));
  }
  digitalWrite(LEDg, LOW);
}

void reconnect() {
  digitalWrite(LEDg, !digitalRead(LEDg));
  while (!client.connected()) {
    if (client.connect("ESP06Light","iobroker","1234")) {
      client.publish("iobroker/ESP06Light/connection", "true");
      client.publish("iobroker/ESP06Light/WW", "false");
      client.publish("iobroker/ESP06Light/WWbrightness", "0");
      client.publish("iobroker/ESP06Light/CW", "false");
      client.publish("iobroker/ESP06Light/CWbrightness", "0");
      client.subscribe("iobroker/ESP06Light/#");
      digitalWrite(LEDg, HIGH);
    } else {
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  String strTopic = String(topic);
  String strPayload = String((char*)payload);
  ///////////
  
  //***шим WW***
  if (strTopic == "iobroker/ESP06Light/WWbrightness"){
    WWvalue = strPayload.toInt();        
    analogWrite(WW, WWvalue);
    if (strPayload.toInt() > 0){
       client.publish("iobroker/ESP06Light/WW", "true");
    } else {
       client.publish("iobroker/ESP06Light/WW", "false");
    }    
    client.publish("iobroker/ESP06Light/WWbrightness", String(WWvalue).c_str());
  } //end if
  
  //***шим CW***
  if (strTopic == "iobroker/ESP06Light/CWbrightness"){
    CWvalue = strPayload.toInt();        
    analogWrite(CW, CWvalue);
     if (strPayload.toInt() > 0){
       client.publish("iobroker/ESP06Light/CW", "true");
    } else {
       client.publish("iobroker/ESP06Light/CW", "false");
    }    
    client.publish("iobroker/ESP06Light/CWbrightness", String(CWvalue).c_str());
  } //end if

  
  //************************************************
  if (strTopic == "iobroker/ESP06Light/WW"){
    if (strPayload == "true"){       
        analogWrite(WW, WWvalue);
    } 
    if(strPayload == "false"){
        WWvalue = 0;
        analogWrite(WW, WWvalue);
    }
    client.publish("iobroker/ESP06Light/WWbrightness", String(WWvalue).c_str());
    client.publish("iobroker/ESP06Light/WW", IntToBool(digitalRead(WW)));
  } //end if
  
  if (strTopic == "iobroker/ESP06Light/CW"){
    if (strPayload == "true"){
        //digitalWrite(CW, HIGH);
        analogWrite(CW, CWvalue);
    }
    if(strPayload == "false"){
        CWvalue = 0;
        analogWrite(CW, CWvalue);
    }
    client.publish("iobroker/ESP06Light/CWbrightness", String(CWvalue).c_str());
    client.publish("iobroker/ESP06Light/CW", IntToBool(digitalRead(CW)));
  } //end if



} // end void





/*******************************************/
/************* VOID SETUP ******************/
/*******************************************/

void setup() {
  pinMode(LEDg, OUTPUT);
  pinMode(REDc, OUTPUT);
  pinMode(GREENc, OUTPUT);
  pinMode(BLUEc, OUTPUT); 
  pinMode(WW, OUTPUT); 
  pinMode(CW, OUTPUT); 
  CWvalue = 1023;
  WWvalue = 1023;
   
  digitalWrite(LEDr, HIGH);
  Serial.begin(19200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);  

  //**********OTA*****************
  ArduinoOTA.onStart([]() {
  });
  ArduinoOTA.onEnd([]() {
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
  });
  ArduinoOTA.onError([](ota_error_t error) {
    /*Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");*/
  });
  ArduinoOTA.begin();
  delay(1000);
} 

/*******************************************/
/*********** END VOID SETUP ****************/
/*******************************************/
char* IntToBool (int r) {
    if (r > 0){
      return "true";
    } else{
      return "false";
    }
}




/*******************************************/
/************** VOID LOOP ******************/
/*******************************************/

void loop() {

ArduinoOTA.handle();
 
  if (!client.connected()){
    reconnect();
  } 
  
  client.loop(); 
  //h801start();  
  

delay(1000);  
}  //end void loop

void h801start() {


}





