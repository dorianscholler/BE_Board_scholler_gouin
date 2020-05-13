#ifndef MYDEVICES_H
#define MYDEVICES_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include "core_simulation.h"
#include <fstream>
// exemple de capteur analogique de temperature, ne pas oublier d'heriter de Device
class AnalogSensorTemperature: public Device {
private:
  // fait osciller la valeur du cpateur de 1
  int alea;
  // valeur de temperature mesuree
  int val;
  // temps entre 2 prises de valeurs
  int temps;
  
public:
  //constructeur ne pas oublier d'initialiser la classe mere
  AnalogSensorTemperature(int d,int  t);
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

class AnalogSensorLuminosity:public Device{
private:
    // temps enre 2 prises de valeur
    int temps;
public:
    //constructeur
   AnalogSensorLuminosity(int lum); 
   // thread representant le capteur et permettant de fonctionner independamment de la board
   virtual void run();
};

// exemple d'actionneur digital : une led, ne pas oublier d'heriter de Device
class DigitalActuatorLED: public Device {
private:
  // etat de la LED
  int state;
  // temps entre 2 affichage de l etat de la led
  int temps;
  
public:
    // initialisation du temps de rafraichiisement
  DigitalActuatorLED(int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
  //fonction pour accéder au state
  int getState(void);
  //fonction pour modifier state
  void setState(int s);
  //fonction pour récupérer le temps
  int getTemps(void);
};


class IntelligentDigitalActuatorLED : public DigitalActuatorLED{
public:
    IntelligentDigitalActuatorLED(int t);   
    virtual void run();
};


class ExternalDigitalSensorButton : public Device {
private :
  bool m_on=false;

public:
  ExternalDigitalSensorButton();
  ~ExternalDigitalSensorButton();
  bool getandsetbutton();
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

