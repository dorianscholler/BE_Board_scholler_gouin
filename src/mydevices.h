#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include <fstream>
#include <vector>


//////////////////////////////////////////SENSORS/////////////////////////////
////defininition d'une classe pour les capteurs
class Sensor:public Device{
protected:
    //definition du retard des capteurs
    int delay;
    //definition de l'erreur des capteurs analogiques
    int alea;
    //on va donner un nom à tout juste pour pas se perdre
    string name;
public:
    Sensor(int delay, string name);  
};

////création d'une classe qui va nous permettre de récupérer la valeur analogique reçue par une pin
class ExternalAnalogicalSensorWire:public Sensor{
private:
    int value;
    string file;///on pourra donner e argument le fichier associé
public:
    ExternalAnalogicalSensorWire(int d, int v, string n, string f);
    bool connect();
    virtual void run();    
};

////classe pour le capteur de luminosité
class AnalogSensorLuminosity:public Sensor{
private:
    string file;
public:
    //constructeur
   AnalogSensorLuminosity(int d, string n, string f); 
   //déterminer si le capteur est recouvert
   bool covered();
   // thread representant le capteur et permettant de fonctionner independamment de la board
   virtual void run();
};

///Classe pour les boutton simulé par des fichiers
class ExternalDigitalSensorButton : public Sensor {
protected :
  bool state=false;
  string file;///nous permet de placer les fichiers des bouttons poussoir là ou ça nous intéresse
public:
  ExternalDigitalSensorButton(int d, string n, string f);
  ~ExternalDigitalSensorButton();
  bool getandsetbutton();
  virtual void run();
};

/*
///Classe pour les boutton qui emettent une sonorité 
class NoisyButton : public ExternalDigitalSensorButton, public Board{
private:
    int frequency;///la fréquence associée au boutton
    int pin;///la pin du haut parleur
public:
    NoisyButton(int d, int freq,int p, string n, string f);
    virtual void run();
    
};*/

///////////////////////////////////////////ACTUATORS/////////////////////////////////////////
////definition d'une classe pour les actionneurs
class Actuator:public Device{
protected:
    int delay;
    int state;
    string name;
public:
    Actuator(int d,int s,string n);
};


///definition de la clase ui va produire l'explosion
class Explosion:public Actuator,Board{
public:
    Explosion(int d,string n);
    virtual void run();
};

////création d'un servomoteur pour gérer le vérouillage de la boite
class DigitalActuatorMotor:public Actuator{
public:
    DigitalActuatorMotor(int d, string n);
    virtual void run();
};

// exemple d'actionneur digital : une led, ne pas oublier d'heriter de Device
class DigitalActuatorLED: public Actuator {
protected:
    string color;
  
public:
  // initialisation du temps de rafraichiisement
  DigitalActuatorLED(int d, string n, string col);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};


////création d'une classe de LED qui donne un indice pour le switch
class SwitchClueLED:public DigitalActuatorLED, public Board{
    int pin;
public:
    SwitchClueLED(int d,int p, string n, string col);
    virtual void run();
};

// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];
  
public:
  // constructeur
  I2CActuatorScreen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};
#endif
