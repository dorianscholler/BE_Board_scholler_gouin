#include <unistd.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
  // on configure la vitesse de la liaison
  Serial.begin(9600);
// on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  pinMode(1,INPUT);
  pinMode(0,OUTPUT);
  
  ///on fixe la pin du capteur de luminsié en INPUT
  pinMode(2,INPUT);
  
  //on règle la LED intelligente en output
  pinMode(3,OUTPUT);

  //on règle le button en output
  pinMode(4,INPUT);

}

// la boucle de controle arduino
void Board::loop(){
  char buf[100];
  int val;
  int val_lum;///valeur enregistrée par le capteur de luminosité
  int etat_bouton;
  static int cpt=0;
  static int bascule=0;
  int i=0;
  for(i=0;i<10;i++){
    // lecture sur la pin 1 : capteur de temperature
    val=analogRead(1);
    sprintf(buf,"temperature %d",val);
    Serial.println(buf);

    //lecture sur la pin 0 : capteur de luminosité
    val_lum=analogRead(2);
    sprintf(buf,"luminosite led 1 : %d",val_lum);
    Serial.println(buf);

    //lecture sur la pin 4 : bouton on//off
    etat_bouton=analogRead(4);
    sprintf(buf,"Le bouton vaut %d",etat_bouton);
    Serial.println(buf);

    if(cpt%5==0){
      // tous les 5 fois on affiche sur l'écran la temperature
      sprintf(buf,"%d",val);
      bus.write(1,buf,100);
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

  
}



