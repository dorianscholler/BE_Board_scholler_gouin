#include "core_simulation.h"
#include "mydevices.h"


int main(){
  // creation d'une board
  Board esp8266;
  
  // achat des senseurs et actionneurs
  AnalogSensorTemperature temperature(TEMP,DELAY,"capteur temperature");
  IntelligentDigitalActuatorLED led1(DELAY,"led 1","violet");
  I2CActuatorScreen screen;
  //création d'un capteur de luminosité
  AnalogSensorLuminosity luminosity(DELAY,"capteur de luminosite","couvert.txt");
  //LED Intelligente
  IntelligentDigitalActuatorLED led2(DELAY,"led 2","blouge");
  //senseur ExternalDigitalSensorButton
  ExternalDigitalSensorButton button(DELAY,"bouton digital","calier num");
  ///test pour les boutons avec sonorité
  NoisyButton noise(DELAY, 500, "boutton bruit", "son_actif.txt");

 

  // branchement des capteurs actionneurs
  esp8266.pin(0,led1);
  esp8266.pin(1,temperature);
  esp8266.pin(2,luminosity);
  esp8266.pin(3,led2);
  esp8266.pin(4,button);
  esp8266.pin(5,noise);
  
   esp8266.i2c(1,screen);
   
  // allumage de la carte
  esp8266.run();
  
  return 0;
}



