#include <unistd.h>
#include "core_simulation.h"

#include "mydevices.h"

// la fonction d'initialisation d'arduino
void Board::setup(){
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
    pinMode(23,OUTPUT);
    //pinMode(17,OUTPUT);
    
    ///LED INDICE
    pinMode(18,OUTPUT);
    
    ///LEDS PARTIES RESOLUES
    pinMode(19,OUTPUT);
    //pinMode(20,OUTPUT);
    //pinMode(21,OUTPUT);
    
    ///BUZZER
    pinMode(22,OUTPUT);
}


void Board::clue_switch(){
    //on clignote 1 fois pour signaler que le switch 1 doit être sur on
    digitalWrite(18,HIGH);
    sleep(1);
    digitalWrite(18,LOW);
    sleep(3);
    
    //on clignote 3 fois pour signaler que le switch 3 doit être sur on
    for (int i=0;i<2;i++){
        digitalWrite(18,HIGH);
        sleep(1);
        digitalWrite(18,LOW);
        sleep(1);
    } 
    sleep(3);
    
    //on clignote 4 fois pour signaler que le switch 4 doit être sur on
    for (int i=0;i<3;i++){
        digitalWrite(18,HIGH);
        sleep(1);
        digitalWrite(18,LOW);
        sleep(1);
    }
    sleep(5);   
}

bool tab_equal(int tab1[],int tab2[],int taille){
    bool equal=true;
    for (int i=0;i<taille;i++){
        if (tab1[i]!=tab2[i]){
            equal=false;
        }   
    }
    return equal;
}

int step=0;///permet d'empêcher les manipulation des autres blocs que celui sur lequel on est censé travailler
int started=0;///permet de savoir quand le décompte de temps a commencé

void Board::loop(){
    //char buf[100];///definition du buffer d'écriture
    int val_lum;////valeur mesurée par le capteur de luminosité
    //int started=0;///permet de savoir quand le décompte de temps a commencé
    //int step=0;///permet d'empêcher les manipulation des autres blocs que celui sur lequel on est censé travailler
    int verif_button;///stockage de l'état du bouton de vérification
    int tab_switch[4];///table dans laquelle on va stocker la valeur des switch
    int tab_s_needed[4]={1,0,1,1};///position des switch qui permet de débloquer l'étape
    
    val_lum=analogRead(0);
    cout<<endl;
    if(val_lum==0){
        cout<<"capteur de lum couvert\n";
        ////démarage du timer
        if (step==0){
            if (started==0){
                digitalWrite(15,HIGH);///on alume la diode de la section des interrupteurs
                //digitalWrite(18,HIGH);
            }
                     
            /////on met a jour le tableau des valeurs des switchs
            for (int i=0;i<4;i++){
                tab_switch[i]=analogRead(2+i);
            }
            
            verif_button=analogRead(1);
            if (verif_button==1){///on rearde si une demande de vérification est faite
                if(tab_equal(tab_switch,tab_s_needed,4)){///si les switchs sont dans le bon ordre
                    digitalWrite(15,LOW);///on éteint la led rouge
                    digitalWrite(19,HIGH);///on allume la led verte de résolution
                    digitalWrite(23,HIGH);///on allume la led rouge de la section clavier avec son
                    ////emettre un son?
                    
                    step++;///on passe à l'étape suivant
                }
                else{
                    //digitalWrite(18,HIGH);
                    ////réduction du temps
                }
            }  
        }
        else if (step==1){
            cout<<"\n ETAPE 1 CLEAR\n";
        }
        else if (step==2){
            
        }
        
    }
    else{
        cout<<"capteur de lum pas couvert\n";
    }
    cout<<endl;
    sleep(2);
           
}


