#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include <fstream>



//////////////////////////////////////////SENSORS/////////////////////////////
////defininition d'une classe pour les capteurs
class Sensor:public Device{
protected:
    //definition du retard des capteurs
    int delay;
    //definition de l'erreur des capteurs
    int alea;
    //on va tout nommer pour plus de clarté
    string name;
public:
    Sensor(int delay, string name);  
};




// exemple de capteur analogique de temperature, ne pas oublier d'heriter de Device
class AnalogSensorTemperature: public Sensor {
private:
  // valeur de temperature mesuree
  int val;
public:
  //constructeur ne pas oublier d'initialiser la classe mere
  AnalogSensorTemperature(int  value, int de, string n);
  // thread representant le capteur et permettant de fonctionner independamment de la board
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



///Classe pour les boutton qui emettent une sonorité 
class NoisyButton : public ExternalDigitalSensorButton{
private:
    ///int value; pas sûr qu'on en ai besoin
    int frequency;
public:
    NoisyButton(int d, int freq, string n, string f);
    int pushed(); 
    virtual void run();
    
};



///////////////////////////////////////////ACTUATORS/////////////////////////////////////////
////definition d'une classe pour les actionneurs
class Actuator:public Device{
protected:
    int delay;
    int state;
    string name;
public:
    Actuator(int d,int s,string n);
    int getState();
    void setState(int s);
};


///definition de la clase ui va produire l'explosion
class Explosion:public Actuator{
public:
    Explosion(int d,int s,string n);
};



////definition de la classe pour le Timer
class Timer:public Actuator{
private:
    int counter;
    int update;///valeur à soustraire au timer en cas d'erreur
public:
    Timer(int d, int s, int c,int u,string n);
    /*void ErrorReduction();
    void Start();
    void Stop();*/
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

/*
////création d'une classe de LED qui donne un indice pour le switch
class SwitchClueLED:public DigitalActuatorLED{
public:
    SwitchClueLED(int d, string n, string col);
    virtual void run();
};*/


////mise à jour de la classe des led intelligentes mais on va pas s'en servir
class IntelligentDigitalActuatorLED : public DigitalActuatorLED{
public:
    IntelligentDigitalActuatorLED(int d, string n, string col);   
    virtual void run();
};

////Classe permettant l'émission de son pour, la mélodie, la résolution d'une partie du puzzle et pour l'explosion
class Buzzer :public Actuator{
private:
    int frequency;
public:
    Buzzer(int d, int freq, int s, string n);
    void makeNoise(int freq);
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

