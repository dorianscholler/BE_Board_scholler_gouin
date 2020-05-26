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
            *ptrmem=19;
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
NoisyButton::NoisyButton(int d, int freq,int p, string n, string f):ExternalDigitalSensorButton(d,n,f),frequency(freq),pin(p){}

void NoisyButton::run(){
  while(1){
    if(ptrmem!=NULL){
        if (ifstream(file)){
            state=true;
            analogWrite(pin,frequency);
        }
        else{
            state=false;
        }
        *ptrmem=state;
    }
    sleep(delay); 
  }      
}

////////////////////////////////////ACTUATORS//////////////////////////////////////////
////classe Actuator
Actuator::Actuator(int d, int s, string n):Device(),delay(d),state(s),name(n){}


////classe explosion
Explosion::Explosion(int d, string n):Actuator(d,LOW,n){}
void Explosion::run(){
    while (1){
        if(ptrmem!=NULL){
            state=*ptrmem;
            if (state==HIGH){
                analogWrite(HP,1000);///en cas d'explosion on envoie juste un signal sonore
                sleep(1);
                analogWrite(HP,0);
            }
        }
        sleep(delay);
    }
}///on voulait également gérer un allumage des LED pour je ne sais quelle obscure raison il n'était pas pris en compte ici

///classe du moteur
DigitalActuatorMotor::DigitalActuatorMotor(int d, string n):Actuator(d,LOW,n){}
void DigitalActuatorMotor::run(){
    while(1){
        if(ptrmem!=NULL){
            state=*ptrmem;
            if (state==HIGH){
                ////on a ouvert le verrou
                cout<<name<<"est débolqué\n";
                sleep(5);
            }
            else{
                ///le verrou est fermé
            }
        }    
         sleep(delay);
    }   
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int d, string n, string col):Actuator(d,LOW,n),color(col){}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
        state=*ptrmem;
    if (state==HIGH){cout << name<< " allume : " << color<<'\n';}
    sleep(delay);
    }
}///on affiche l'état des LEDs que lorsqu'elles sont allumées


SwitchClueLED::SwitchClueLED(int d,int p, string n, string col):DigitalActuatorLED(d,n,col), pin(p){}
void SwitchClueLED::run(){
    while(1){
        if(ptrmem!=NULL)
        state=*ptrmem;
        if (state==HIGH){
            //on clignote 1 fois pour signaler que le switch 1 doit être sur on
            digitalWrite(18,HIGH);
            sleep(0.5);
            digitalWrite(pin,LOW);
            sleep(delay);
    
            //on clignote 3 fois pour signaler que le switch 3 doit être sur on
            for (int i=0;i<2;i++){
                digitalWrite(pin,HIGH);
                sleep(0.5);
                digitalWrite(pin,LOW);
                sleep(0.5);
            } 
            sleep(delay);
    
            //on clignote 4 fois pour signaler que le switch 4 doit être sur on
            for (int i=0;i<3;i++){
                digitalWrite(pin,HIGH);
                sleep(0.5);
                digitalWrite(pin,LOW);
                sleep(0.5);
            }
            sleep(delay+1); 
        }
    }
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





