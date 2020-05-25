#include "core_simulation.h"
#include "mydevices.h"

int tab[NBFREQ]={320,200,560,149,600,589,305,789,654};

Buzzer buzzer(DELAY,tab,LOW,"emmetteur de son");
  
int NoisyButton::pushed(){
  if (ifstream(file)){
    nbreactif++; 
    //avoir si ca marche // 
    if (nbreactif==1 and buzzer.melodyfini){
      return frequency;
    }
    else if (nbreactif!=1 and buzzer.melodyfini==false){
      cout<<"ATTENTION : Deux boutons activés en même temps et melodie non terminée. Veuillez à appuyer sur un seul bouton en même temps et à attendre la fin de la melodie"<<endl;
      return 0;
    }
    else if (nbreactif!=1){
      cout<<"ATTENTION : Deux boutons activés en même temps. Veuillez à appuyer sur un seul bouton en même temps"<<endl;
      return 0;
    }
    else {
      cout<<"ATTENTION : Melodie non terminée. Veuillez à attendre la fin de la melodie."<<endl;
      return 0;
    }
  }
  else{
    nbreactif=0;
    return 0;
  }
}

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
  SwitchClueLED switch_clue(DELAY,18,"Led indice ","bleu");
  
  ///LEDs signalant la conclusion d'une enigme
  DigitalActuatorLED switch_done(DELAY,"switch résolu ","vert");
  DigitalActuatorLED pad_done(DELAY,"clavier résolu ","vert");
  DigitalActuatorLED wire_done(DELAY,"fils résolu ","vert");
  
  ///CREATION DES CAPTEUR DE TENSION POUR LE BLOC DE FILS
  ExternalAnalogicalSensorWire wire1(DELAY,10,"capteur analogique","connect10.txt");
  ExternalAnalogicalSensorWire wire2(DELAY,140,"capteur analogique","connect140.txt");
  ExternalAnalogicalSensorWire wire3(DELAY,320,"capteur analogique","connect320.txt");
  
  ///CREATION DE L'ECRAN
  //I2CActuatorScreen screen;
  
  ///CREATION DU CAPTEUR DE LUMINOSITE
  AnalogSensorLuminosity luminosity(DELAY,"capteur de luminosite","couvert.txt");
  
  ///CREATION DU BOUTON DE VERIFICATION
  ExternalDigitalSensorButton verif_button(DELAY,"bouton de verification","verif.txt");
  
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
  
  ///CREATION DU BUZZER
  //voir création dans mydevices pour cause probleme variable ami melodyfini

  /*
  int tab[9]={320,200,560,149,600,589,305,789,654};
  Buzzer buzzer(DELAY,tab,LOW,"emmetteur de son");
  */







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
  
  //LED INDICE
  esp8266.pin(18,switch_clue);
  
  ///LEDs signalant la conclusion d'une enigme
  esp8266.pin(19,switch_done);
  esp8266.pin(20,pad_done);
  esp8266.pin(21,wire_done);
  
  ///CONNECTIONS DES CAPTEURS POUR LES FILS
  esp8266.pin(22,wire1);
  esp8266.pin(23,wire2);
  esp8266.pin(24,wire3);
  
  //BUZZER
  esp8266.pin(25,buzzer);
  
  
  //esp8266.i2c(1,screen);
   
  //allumage de la carte
  esp8266.run();
  
  return 0;
  
}



