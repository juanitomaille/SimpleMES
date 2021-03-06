/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
* Visit the website for more information：https://docs.m5stack.com/en/core/core2
*
* describe：MQTT.
* date：2021/11/5
*******************************************************************************
*/
#include "M5Core2.h"
#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

// Configure the name and password of the connected wifi and your MQTT Serve host.

const char* ssid = "FACTORYBOX";
const char* password = "Jm9r5F3W";
const char* mqtt_server = "factorybox";

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
char data[3];
char code[3]; // Color of column : 000 = no color; 100 = green, 010 = orange, 001 = red

void setupWifi();
void callback(char* topic, byte* payload, unsigned int length);
void reConnect();


void setupWifi() {
  delay(10);
  M5.Lcd.printf("Connecting to %s",ssid);
  WiFi.mode(WIFI_STA);  //Set the mode to WiFi station mode.  
  WiFi.begin(ssid, password); //Start Wifi connection.  

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.printf("\nSuccess\n");
}

void callback(char* topic, byte* payload, unsigned int length) {
  M5.Lcd.print("Message arrived [");
  M5.Lcd.print(topic);
  M5.Lcd.print("] ");
  for (int i = 0; i < length; i++) {
    M5.Lcd.print((char)payload[i]);
  }
  M5.Lcd.println();
}

void reConnect() {
  while (!client.connected()) {
    M5.Lcd.print("Attempting MQTT connection...");
    // Create a random client ID.  
    String clientId = "M5Stack-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect.  尝试重新连接
    if (client.connect(clientId.c_str())) {
      M5.Lcd.printf("\nSuccess\n");
      // Once connected, publish an announcement to the topic.  
      client.publish("M5Stack", "hello world");
      // ... and resubscribe.  
      client.subscribe("M5Stack");
    } else {
      M5.Lcd.print("failed, rc=");
      M5.Lcd.print(client.state());
      M5.Lcd.println("try again in 5 seconds");
      delay(5000);
    }
  }
}




float t = 19;



void setup() {

  M5.begin(true,true,true,true,kMBusModeInput); // initialization of M5 with external I2C enabled (4th true) :: kMBusModeInput permit to power core2 by pins
  setupWifi(); // concrens wifi setup
  client.setServer(mqtt_server, 1883);  //Sets the MQTT server details.  
  client.setCallback(callback); //Sets the message callback function for MQTT

  M5.Lcd.setTextColor(YELLOW);  //Set the font color to yellow. 
  M5.Lcd.setTextSize(1);  //Set the font size to 2.  
  M5.Lcd.println("PME4.0 - Machine State -DEBUG"); //Print a string on the screen.  
  delay(3000);
  M5.Lcd.fillScreen( BLACK ); //Make the screen full of black (equivalent to clear() to clear the screen). 
  M5.Lcd.setTextColor(WHITE);  //Set the font color to yellow. 

  Wire.begin(32, 33); // external I2C.  
}


int textColor=WHITE;


void loop() {
  


  //MQTT communication
  if (!client.connected()) {
    reConnect();
  }
  client.loop();  //MQTT : This function is called periodically to allow clients to process incoming messages and maintain connections to the server.

  unsigned long now = millis(); //Obtain the host startup duration.  
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    //snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value); //Format to the specified string and store it in MSG.  
    //msg = String(t).c_str();
    //M5.Lcd.print("Publish message: ");
    //M5.Lcd.println(String(t).c_str());
    client.publish("M5Stack/temp", String(t).c_str());  //Publishes a message to the specified topic.  

  }

  Wire.requestFrom(2, 3);   // L'adresse du arduino sera 2
  int i = 0;
  while(Wire.available())    // slave may send less than requested
  {
    char c = Wire.read();    // receive a byte as character
    data[i] = c;
    i = i + 1 ; 
  }

  int vert = data[0] - '0'; // method to convert char in int
  int orange = data[1] - '0';
  int rouge = data[2] - '0';

  M5.Lcd.setTextSize(2);  //Set the font size to 2. 
  int hauteur_txt = 110;
  
  if (vert == 1 && orange == 0 && rouge == 0 ){
    textColor=BLACK;
    M5.Lcd.setTextColor(textColor,GREEN); //Set the foreground color of the text to textColor and the background color to BLACK. 
    M5.Lcd.fillScreen( GREEN ); //Make the screen full of black (equivalent to clear() to clear the screen). 
    M5.Lcd.setCursor(30,hauteur_txt);
    M5.Lcd.print("MACHINE EN PRODUCTION");
  }
  else if (orange == 1 && vert == 0 && rouge == 0){
    textColor=BLACK;
    M5.Lcd.setTextColor(textColor,YELLOW); //Set the foreground color of the text to textColor and the background color to BLACK. 
    M5.Lcd.fillScreen( YELLOW ); //Make the screen full of black (equivalent to clear() to clear the screen). 
    M5.Lcd.setCursor(60,hauteur_txt);
    M5.Lcd.print("MACHINE EN PAUSE");
  }
  else if (rouge == 1 && vert == 0 && orange == 0){
    textColor=RED;
    M5.Lcd.setTextSize(4);
    M5.Lcd.setTextColor(textColor,BLACK); //Set the foreground color of the text to textColor and the background color to BLACK. 
    M5.Lcd.fillScreen( BLACK ); //Make the screen full of black (equivalent to clear() to clear the screen). 
    M5.Lcd.setCursor(110,hauteur_txt);
    M5.Lcd.print("ARRET");
  }
  else if (vert == 1 && rouge == 1 && orange ==0 ){
    textColor=BLACK;
    M5.Lcd.setTextColor(textColor,YELLOW); //Set the foreground color of the text to textColor and the background color to BLACK.
    M5.Lcd.fillScreen( YELLOW ); //Make the screen full of black (equivalent to clear() to clear the screen). 
    M5.Lcd.setCursor(60,hauteur_txt); 
    M5.Lcd.print("MACHINE EN PAUSE");
  }
  else if (vert == 0 && rouge == 0 && orange == 0){
    M5.Lcd.setTextSize(4);
    textColor=WHITE;
    M5.Lcd.setTextColor(textColor,BLACK); //Set the foreground color of the text to textColor and the background color to BLACK. 
    M5.Lcd.fillScreen( BLACK ); //Make the screen full of black (equivalent to clear() to clear the screen). 
    M5.Lcd.setCursor(60,hauteur_txt);
    M5.Lcd.print("NO SIGNAL");
  }

  else {
    textColor=WHITE;
    M5.Lcd.setTextSize(4);
    M5.Lcd.setTextColor(textColor,RED); //Set the foreground color of the text to textColor and the background color to RED. 
    M5.Lcd.fillScreen( RED ); //Make the screen full of black (equivalent to clear() to clear the screen). 
    M5.Lcd.setCursor(100,hauteur_txt);
    M5.Lcd.print("ERREUR");
  }
  delay(1000);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,0);

}
