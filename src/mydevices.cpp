#include "mydevices.h"

int luminosite_environnement = 200;///definition de la variable globale

using namespace std;


////////////////////////////////SENSORS////////////////////////////////
///classe Sensor
Sensor::Sensor(int d, string n):Device(),delay(d),name(n){
alea=1;
}

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int value,int de,string n):Sensor(de,n),val(value){}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(delay);
  }
}



//classe AnalogSensorLuminosity
AnalogSensorLuminosity::AnalogSensorLuminosity(int d,string n,string f):Sensor(d,n),file(f){}

bool AnalogSensorLuminosity::covered(){
    if (ifstream(file)){;
        return true;
    }
    else{
        return false;
    }
}

void AnalogSensorLuminosity::run(){
  while(1){
    if(ptrmem!=NULL){
        if (covered()){
            *ptrmem=0;
        }
        else{
        *ptrmem=luminosite_environnement;
        }
    }
    sleep(delay);
  }
}

///classe ExternalDigitalSensorButton
//constructeur
ExternalDigitalSensorButton::ExternalDigitalSensorButton(int d, string n, string f) : Sensor(d,n), file(f){}
//destructeur
ExternalDigitalSensorButton::~ExternalDigitalSensorButton(){}

bool ExternalDigitalSensorButton::getandsetbutton(){
  if (ifstream(file)){
    state=true;  
  }
  else{
    state=false;
  }
  return(state);
}

void ExternalDigitalSensorButton::run(){
  while(1){
    if(ptrmem!=NULL){
      *ptrmem=getandsetbutton();
    }
    sleep(delay); 
  }        
}

 
//Classe pour les bouttons qui emettent une sonorité

NoisyButton::NoisyButton(int d, int freq, string n, string f):ExternalDigitalSensorButton(d,n,f),frequency(freq){}

int NoisyButton::pushed(){
    if (ifstream(file)){
        return frequency;
    }
    else{
        return 0;
    }
}

void NoisyButton::run(){
  while(1){
    if(ptrmem!=NULL){
        *ptrmem=pushed();
    }
    sleep(delay); 
  }        
}




////////////////////////////////////ACTUATORS//////////////////////////////////////////
////classe Actuator
Actuator::Actuator(int d, int s, string n):Device(),delay(d),state(s),name(n){}
int Actuator::getState(){return state;}
void Actuator::setState(int s){state=s;}


////classe explosion
Explosion::Explosion(int d, int s, string n):Actuator(d,s,n){}



/////classe Timer
Timer::Timer(int d, int s, int c, int u, string n):Actuator(d,s,n),counter(c),update(u){}

void ErrorReduction(){}

void Timer::run(){}



//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int d, string n, string col):Actuator(d,LOW,n),color(col){}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW){cout << name<< " eteint\n";}
    else{cout << name<< " allume : " << color<<'\n';}
    sleep(delay);
    }
}

/*
SwitchClueLED::SwitchClueLED(int d, string n, string col):DigitalActuatorLED(d,n,col){}
void SwitchClueLED::run(){
    while(1){
        if(ptrmem!=NULL)
        state=*ptrmem;
        if (state==HIGH){
             //on clignote 1 fois pour signaler que le switch 1 doit être sur on
            //digitalWrite(18,HIGH);
            //sleep(1);
            digitalWrite(18,LOW);
            sleep(delay);
    
            //on clignote 3 fois pour signaler que le switch 3 doit être sur on
            for (int i=0;i<2;i++){
                digitalWrite(18,HIGH);
                sleep(1);
                digitalWrite(18,LOW);
                sleep(1);
            } 
            sleep(delay);
    
            //on clignote 4 fois pour signaler que le switch 4 doit être sur on
            for (int i=0;i<3;i++){
                digitalWrite(18,HIGH);
                sleep(1);
                digitalWrite(18,LOW);
                sleep(1);
            }
            sleep(delay+1); 
        }
    }
}*/


//class IntelligentDigitalActuatorLED
IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int d, string n, string col):DigitalActuatorLED(d,n,col){}

void IntelligentDigitalActuatorLED::run(){
    int old_State=LOW;
    while(1){
        if(ptrmem!=NULL)
          state=*ptrmem;
        if (state==LOW){
            cout << "LED " << color<< " SMART LED LOW\n";
            if (old_State==HIGH){
                luminosite_environnement-=50;
            }
        }
        else{
            cout <<"LED " << color<< " SMART LED HIGH\n";
            if(old_State==LOW){
                luminosite_environnement+=50;
            }
        }
        old_State=state;
        sleep(delay);
    }
}



////class Noise pour l'émission de son
Buzzer::Buzzer(int d, int freq, int s, string n):Actuator(d,s,n),frequency(freq){}
void Buzzer::makeNoise(int freq){
    frequency=freq;
    cout<<frequency<<'\n';
}

// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){}

void I2CActuatorScreen::run(){
  while(1){
    if ( (i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout <<"---screen :"<< buf << endl;
    }
    sleep(1);
    }
}




