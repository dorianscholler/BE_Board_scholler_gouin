#include <unistd.h>
#include "core_simulation.h"


// la fonction d'initialisation d'arduino
void Board::setup(){
 /* // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(1,INPUT);
  pinMode(0,OUTPUT);
  
  ///on fixe la pin du capteur de luminosité en INPUT
  pinMode(2,INPUT);
  
  //on règle la LED intelligente en output
  pinMode(3,OUTPUT);

  //on règle le button en output
  pinMode(4,INPUT);
  
  ///test pour NoisyButton
  pinMode(5,INPUT);*/
    
    
    ///configuration de la vitesse de liaison
    Serial.begin(9600);
    
    ///CAPTEUR DE LUMINOSITE
    pinMode(0,INPUT);
    
    ///BOUTON DE VERIFICATION
    pinMode(1,INPUT);
    
    ///BOUTONS ON OFF
    pinMode(2,INPUT);
    pinMode(3,INPUT);
    pinMode(4,INPUT);
    pinMode(5,INPUT);
    
    ///CLAVIER DIGITAL
    pinMode(6,INPUT);
    pinMode(7,INPUT);
    pinMode(8,INPUT);
    pinMode(9,INPUT);
    pinMode(10,INPUT);
    pinMode(11,INPUT);
    pinMode(12,INPUT);
    pinMode(13,INPUT);
    pinMode(14,INPUT);
    
    ///LEDS
    pinMode(15,OUTPUT);
    pinMode(16,OUTPUT);
    pinMode(17,OUTPUT);
}


/*
// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  //int val;
  int val_lum;///valeur enregistrée par le capteur de luminosité
  int son=0;
  int etat_bouton;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature
      
    //val=analogRead(1);
    //sprintf(buf,"temperature %d",val);
   // Serial.println(buf);

    //lecture sur la pin 2 : capteur de luminosité
    val_lum=analogRead(2);
    sprintf(buf,"luminosite ambiante : %d",val_lum);
    Serial.println(buf);

    
    //lecture sur le pin 5 pour récupérer la valeur de fréquence du bouton
    son=analogRead(5);
    sprintf(buf,"son du bouton %d",son);
    Serial.println(buf);    
    
    //lecture sur la pin 4 : bouton on//off
    etat_bouton=analogRead(4);
    sprintf(buf,"Le bouton vaut %d",etat_bouton);
    Serial.println(buf);
    
    
    
    if(cpt%5==0){
      // tous les 5 fois on affiche sur l'écran la temperature
      // sprintf(buf,"%d",val);
      //bus.write(1,buf,100);
        
      //toutes les 5 fois affichage également de la luminosité 
      sprintf(buf,"%d",val_lum);
      bus.write(2,buf,100);
    }
    cpt++;
    sleep(1);
  }

// on eteint et on allume la LED 1
  if (etat_bouton){
    digitalWrite(0,HIGH);
  }
  else{
    digitalWrite(0,LOW);
  }
// on eteint et on allume la LED 2
  if(bascule){
    
    digitalWrite(3,HIGH);
  }
  else{
   
    digitalWrite(3,LOW);
  }
  bascule=1-bascule;

  
}*/
void Board::loop(){
    char buf[100];///definition du buffer d'écriture
    int val_lum;////valeur mesurée par le capteur de luminosité
    
    val_lum=analogRead(0);
    if(val_lum==0){
        cout<<"capteur de lum couvert\n";
        digitalWrite(15,HIGH);
        
    }
    else{
        cout<<"capteur de lum pas couvert\n";
    }
    sleep(2);
           
}


