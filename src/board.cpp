#include "core_simulation.h"
#include "mydevices.h"


int main(){
    /*/
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
   */
    
  // creation d'une board
  Board esp8266;
  
  ///achat des senseurs et actionneurs
  ///AnalogSensorTemperature temperature(TEMP,DELAY,"capteur temperature");
  
  ///CREATION DES LEDS
  DigitalActuatorLED led_switch(DELAY,"la led des switch ","rouge");
  DigitalActuatorLED led_pad(DELAY,"la led du clavier ","rouge");
  DigitalActuatorLED led_wire(DELAY,"la led des fils ","rouge");
  
  ///CREATION DE L'ECRAN
  I2CActuatorScreen screen;
  
  ///CREATION DU CAPTEUR DE LUMINOSITE
  AnalogSensorLuminosity luminosity(DELAY,"capteur de luminosite","couvert.txt");
  
  ///CREATION DU BOUTON DE VERIFICATION
  ExternalDigitalSensorButton verif_button(DELAY,"bouton de verification","verification.txt");
  
  ///CREATION DES BOUTONS ON OFF
  ExternalDigitalSensorButton switch1(DELAY,"bouton 1","switch1.txt");
  ExternalDigitalSensorButton switch2(DELAY,"bouton 2","switch2.txt");
  ExternalDigitalSensorButton switch3(DELAY,"bouton 3","switch3.txt");
  ExternalDigitalSensorButton switch4(DELAY,"bouton 4","switch4.txt");
  
  ///CREATION DU CLAVIER AVEC SON
  NoisyButton digi1(DELAY,100,"bouton digital 1","1.txt");
  NoisyButton digi2(DELAY,200,"bouton digital 2","2.txt");
  NoisyButton digi3(DELAY,300,"bouton digital 3","3.txt");
  NoisyButton digi4(DELAY,400,"bouton digital 4","4.txt");
  NoisyButton digi5(DELAY,500,"bouton digital 5","5.txt");
  NoisyButton digi6(DELAY,600,"bouton digital 6","6.txt");
  NoisyButton digi7(DELAY,700,"bouton digital 7","7.txt");
  NoisyButton digi8(DELAY,800,"bouton digital 8","8.txt");
  NoisyButton digi9(DELAY,900,"bouton digital 9","9.txt");
  
  ///BRANCHEMENT SUR LES PINS
  //capteur de luminosité
  esp8266.pin(0,luminosity);
  
  //bouton de verification
  esp8266.pin(1,verif_button);
  
  //bouton on/off
  esp8266.pin(2,switch1);
  esp8266.pin(3,switch2);
  esp8266.pin(4,switch3);
  esp8266.pin(5,switch4);
  
  //clavier digital
  esp8266.pin(6,digi1);
  esp8266.pin(7,digi2);
  esp8266.pin(8,digi3);
  esp8266.pin(9,digi4);
  esp8266.pin(10,digi5);
  esp8266.pin(11,digi6);
  esp8266.pin(12,digi7);
  esp8266.pin(13,digi8);
  esp8266.pin(14,digi9);
  
  //LEDS
  esp8266.pin(15,led_switch);
  esp8266.pin(16,led_pad);
  esp8266.pin(17,led_wire);
  
  
  esp8266.i2c(1,screen);
   
  //allumage de la carte
  esp8266.run();
  
  return 0;
  
}



