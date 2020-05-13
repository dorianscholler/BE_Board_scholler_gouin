#include "mydevices.h"

int luminosite_environnement = 200;///definition de la variable globale

using namespace std;

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):Device(),val(t),temps(d){
  alea=1;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}
//classe AnalogSensorLuminosity
AnalogSensorLuminosity::AnalogSensorLuminosity(int d):Device(),temps(d){}

void AnalogSensorLuminosity::run(){
  while(1){
    if(ptrmem!=NULL){
      *ptrmem=luminosite_environnement;
    }
    sleep(temps);
  }
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

int DigitalActuatorLED::getState(){return state;}

int DigitalActuatorLED::getTemps(){return temps;}

void DigitalActuatorLED::setState(int s){state=s;}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
    cout << "((((allume))))\n";
    sleep(temps);
    }
}

//class IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t):DigitalActuatorLED(t){}

void IntelligentDigitalActuatorLED::run(){
    int old_State=LOW;
    while(1){
        if(ptrmem!=NULL)
          DigitalActuatorLED::setState(*ptrmem);
        if (DigitalActuatorLED::getState()==LOW){
            cout << "((((eteint))))\n";
            if (old_State==HIGH){
                luminosite_environnement-=50;
            }
        }
        else{
            cout << "((((allume))))\n";
            if(old_State==LOW){
                luminosite_environnement+=50;
            }
        }
        old_State=DigitalActuatorLED::getState();
        sleep(DigitalActuatorLED::getTemps());
    }
}
//constructeur
ExternalDigitalSensorButton::ExternalDigitalSensorButton() : Device(){
}
//destructeur
ExternalDigitalSensorButton::~ExternalDigitalSensorButton(){}

bool ExternalDigitalSensorButton::getandsetbutton(){
  if (ifstream("on.txt")){
    m_on=true;  
  }
  else{
    m_on=false;
  }
  return(m_on);
}

void ExternalDigitalSensorButton::run(){
  while(1){
    if(ptrmem!=NULL){
      *ptrmem=getandsetbutton();
    }
    sleep(3); 
  }        
}

  



// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){}

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}




