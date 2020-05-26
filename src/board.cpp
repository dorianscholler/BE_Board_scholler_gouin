#include "core_simulation.h"
#include "mydevices.h"

int main(){
      
  // creation d'une board
  Board esp8266;
  
  ///achat des senseurs et actionneurs
  ///AnalogSensorTemperature temperature(TEMP,DELAY,"capteur temperature");
  
  ///CREATION DES LEDS
  DigitalActuatorLED led_switch(DELAY,"led switch ","rouge");
  DigitalActuatorLED led_pad(DELAY,"led clavier ","rouge");
  DigitalActuatorLED led_wire(DELAY,"led fils ","rouge");
  
  ///LED indice
  SwitchClueLED switch_clue(DELAY_C,18,"Led indice ","bleu");
  
  ///LEDs signalant la conclusion d'une enigme
  DigitalActuatorLED switch_done(DELAY,"switch résolu ","vert");
  DigitalActuatorLED pad_done(DELAY,"clavier résolu ","vert");
  DigitalActuatorLED wire_done(DELAY,"fils résolu ","vert");
  
  ///CREATION DES CAPTEUR DE TENSION POUR LE BLOC DE FILS
  ExternalAnalogicalSensorWire wire1(DELAY,10,"capteur analogique","connect10.txt");
  ExternalAnalogicalSensorWire wire2(DELAY,140,"capteur analogique","connect140.txt");
  ExternalAnalogicalSensorWire wire3(DELAY,320,"capteur analogique","connect320.txt");
  
  ///CREATION DE L'ECRAN
  I2CActuatorScreen screen;
  
  ///CREATION DU CAPTEUR DE LUMINOSITE
  AnalogSensorLuminosity luminosity(FAST,"capteur de luminosite","couvert.txt");
  
  ///CREATION DU BOUTON DE VERIFICATION
  ExternalDigitalSensorButton verif_b1(DELAY,"bouton de verification","verif1.txt");
  ExternalDigitalSensorButton verif_b2(DELAY,"bouton de verification","verif2.txt");
  ExternalDigitalSensorButton verif_b3(DELAY,"bouton de verification","verif3.txt");
  
  ///Bouton Start
  ExternalDigitalSensorButton start(DELAY,"bouton start","start.txt");
  
  ///CREATION DES BOUTONS ON OFF
  ExternalDigitalSensorButton switch1(DELAY,"bouton 1","switch1.txt");
  ExternalDigitalSensorButton switch2(DELAY,"bouton 2","switch2.txt");
  ExternalDigitalSensorButton switch3(DELAY,"bouton 3","switch3.txt");
  ExternalDigitalSensorButton switch4(DELAY,"bouton 4","switch4.txt");
  
  ///CREATION DU CLAVIER AVEC SON
  NoisyButton digi1(DELAY,50,HP,"bouton digital 1","1.txt");
  NoisyButton digi2(DELAY,100,HP,"bouton digital 2","2.txt");
  NoisyButton digi3(DELAY,150,HP,"bouton digital 3","3.txt");
  NoisyButton digi4(DELAY,200,HP,"bouton digital 4","4.txt");
  NoisyButton digi5(DELAY,250,HP,"bouton digital 5","5.txt");
  NoisyButton digi6(DELAY,300,HP,"bouton digital 6","6.txt");
  NoisyButton digi7(DELAY,350,HP,"bouton digital 7","7.txt");
  NoisyButton digi8(DELAY,400,HP,"bouton digital 8","8.txt");
  NoisyButton digi9(DELAY,450,HP,"bouton digital 9","9.txt");
 
  
  ///CREATION DE L'EXLOSION
  Explosion explode(DELAY,"explosion");
  
  ///CREATION DU SERVO MOTEUR QUI SERT DE VERROU POUR LA BOITE
  DigitalActuatorMotor lock(FAST,"verrou");
  //bouton pour vérifier que la boite est fermée
  ExternalDigitalSensorButton closed(FAST,"la boite est fermée","closed.txt");

  ///BRANCHEMENT SUR LES PINS
  //capteur de luminosité
  esp8266.pin(0,luminosity);
  
  //bouton de verification
  esp8266.pin(1,verif_b1);
  esp8266.pin(30,verif_b2);
  esp8266.pin(31,verif_b3);
  
  //bouton on/off
  esp8266.pin(2,switch1);
  esp8266.pin(3,switch2);
  esp8266.pin(4,switch3);
  esp8266.pin(5,switch4);
  
  //bouton start
  esp8266.pin(32,start);
  
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
  esp8266.pin(pSwitch,led_switch);
  esp8266.pin(pPad,led_pad);
  esp8266.pin(pWire,led_wire);
  
  //LED INDICE
  esp8266.pin(pClue,switch_clue);
  
  ///LEDs signalant la conclusion d'une enigme
  esp8266.pin(pSdone,switch_done);
  esp8266.pin(pPdone,pad_done);
  esp8266.pin(pWdone,wire_done);
  
  ///CONNECTIONS DES CAPTEURS POUR LES FILS
  esp8266.pin(22,wire1);
  esp8266.pin(23,wire2);
  esp8266.pin(24,wire3);
  
  ///connection du capteur d'exposion
  esp8266.pin(29,explode);
  
  ///connection du verrou et du bouton pour vérifier si la boite est fermée
  esp8266.pin(BOX,lock);
  esp8266.pin(P_CLOSED,closed);
  
  esp8266.i2c(1,screen);
   
  //allumage de la carte
  esp8266.run();
  
  return 0;
  
}



