#include "mydevices.h"

int luminosite_environnement = 200;///definition de la variable globale

using namespace std;


////////////////////////////////SENSORS////////////////////////////////
///classe Sensor
Sensor::Sensor(int d, string n):Device(),delay(d),name(n){
alea=1;
}


//classe ExternalAnalogicalSensorWire
ExternalAnalogicalSensorWire::ExternalAnalogicalSensorWire(int d, int v, string n, string f):Sensor(d,n),value(v),file(f){}

bool ExternalAnalogicalSensorWire::connect(){
    if (ifstream(file)){;
        return true;
    }
    else{
        return false;
    }
}
void ExternalAnalogicalSensorWire::run(){
    while(1){
        if(ptrmem!=NULL){
            if (connect()){
                *ptrmem=value;
            }
            else{
                *ptrmem=0;
            }
        }
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



NoisyButton::NoisyButton(int d, int freq, string n, string f):ExternalDigitalSensorButton(d,n,f), Board(),frequency(freq){}
///////////// test probleme varibale melodi fini voir board.cpp

/*
  int NoisyButton::pushed(){
    if (ifstream(file)){
      nbreactif++; 
      //avoir si ca marche // quand reinitialisé la variale qui compte le nombre de bouton ?
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
*/
void NoisyButton::run(int pin){
  while(1){
    if(pushed()!=0){
      analogWrite(pin,pushed());
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


SwitchClueLED::SwitchClueLED(int d,int p, string n, string col):DigitalActuatorLED(d,n,col), pin(p){}
void SwitchClueLED::run(){
    while(1){
        if(ptrmem!=NULL)
        state=*ptrmem;
        if (state==HIGH){
            //on clignote 1 fois pour signaler que le switch 1 doit être sur on
            //digitalWrite(18,HIGH);
            //sleep(1);
            digitalWrite(pin,LOW);
            sleep(delay);
    
            //on clignote 3 fois pour signaler que le switch 3 doit être sur on
            for (int i=0;i<2;i++){
                digitalWrite(pin,HIGH);
                sleep(1);
                digitalWrite(pin,LOW);
                sleep(1);
            } 
            sleep(delay);
    
            //on clignote 4 fois pour signaler que le switch 4 doit être sur on
            for (int i=0;i<3;i++){
                digitalWrite(pin,HIGH);
                sleep(1);
                digitalWrite(pin,LOW);
                sleep(1);
            }
            sleep(delay+1); 
        }
    }
}

////class Noise pour l'émission de son
Buzzer::Buzzer(int d, int *frequencies, int s, string n):Actuator(d,s,n),Board(),m_frequencies(frequencies){}

void Buzzer::Liremelody(int *freq, int pin){
  for(int i=0 ; i<NBFREQ+1;i++){
    analogWrite(pin,freq[i]);
    sleep(1);
  }
melodyfini=true;
}
/*
void Buzzer::makeNoise(int freq){
    frequency=freq;
    cout<<frequency<<'\n';
}

void Buzzer::run(){
  while(1){
    if(ptrmem!=NULL)
      *ptrmem=;
      cout<<freq;
      sleep(delay);
    }
}
*/

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




