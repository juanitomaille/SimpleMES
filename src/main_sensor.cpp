#include <Arduino.h>
#include <Wire.h>
int pin_lum_1 = 0; // capteur branché sur le port A0
int pin_lum_2 = 1; // capteur branché sur le port A1
int pin_lum_3 = 2; // capteur branché sur le port A2
int capteur_lum_1 = 0; // valeur analogique de la luminosité
int capteur_lum_2 = 0; // valeur analogique de la luminosité
int capteur_lum_3 = 0; // valeur analogique de la luminosité
int l1 = 0; // bit de lumière ou non
int l2 = 0;
int l3 = 0;

float level = 500.0; // valeur de luminosité de bascule 

char code[4]; // concaténation des 3 valeurs de capteur : 100 -> capteur 1 allumé seul, 001  -> capteur 3 allumé seul



void requestEvent() {
  Wire.write(code); // envoi des données
  Serial.print("Request from I2C, ANSWER : ");
  Serial.println(code);  
}



void setup(void) {
  Serial.begin(9600); // démarrer la liaison série
  Wire.begin(2); // démarrer i2c bus addresse 2
  Wire.onRequest(requestEvent); // register event
}

void loop(void) {
  
  capteur_lum_1 = analogRead(pin_lum_1); 
  capteur_lum_2 = analogRead(pin_lum_2);
  capteur_lum_3 = analogRead(pin_lum_3);

//float analog_lum = (float)(1023 - sensorValue) * 10 / sensorValue; // Résistance du capteur en Kilo ohms -> formule au cas ou


  if( capteur_lum_1 > level)
  {
    l1 = 1;
  }
  else l1 = 0;

  if( capteur_lum_2 > level)
  {
    l2 = 1;
  } 
  else l2 = 0;

  if( capteur_lum_3 > level)
  {
    l3 = 1;
  }
  else l3 = 0;

  snprintf(code, 4, "%d%d%d", l1, l2, l3);




  Serial.print("C1= ");
  Serial.print(capteur_lum_1); 
  Serial.print(" / ");
  Serial.print("C2= ");
  Serial.print(capteur_lum_2); 
  Serial.print(" / ");
  Serial.print("C3= ");
  Serial.print(capteur_lum_3); 
  Serial.println(" | ");
  Serial.print("Code=");
  Serial.println(code);  


  delay(500);
}