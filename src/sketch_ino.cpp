#include <unistd.h>
#include "core_simulation.h"


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
    pinMode(16,OUTPUT);
    pinMode(17,OUTPUT);
    
    ///LED INDICE
    pinMode(18,OUTPUT);
    
    ///LEDS PARTIES RESOLUES
    pinMode(19,OUTPUT);
    pinMode(20,OUTPUT);
    pinMode(21,OUTPUT);
    
    ///BUZZER
    pinMode(HP,OUTPUT);
    
    ///PIN en output pour le bloc de fils
    pinMode(26,OUTPUT);
    pinMode(27,OUTPUT);
    pinMode(28,OUTPUT);
    
    ///pin en input pour le bloc de fils
    pinMode(22,INPUT);
    pinMode(23,INPUT);
    pinMode(24,INPUT);
   
    
    ////petite initialisation des leds 
    ///initialisation des LED à l'état bas
    for (int i=0; i<7;i++){
        analogWrite(15+i,0);
    }   

    ///initialisation des pin de désamorçage
    analogWrite(26,10);
    analogWrite(27,140);
    analogWrite(28,320);  
    
   
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

//////definitions des variables externes à notre fonction, nécessité de faire bien attention aux mdiffications
int step=0;///permet d'empêcher les manipulation des autres blocs que celui sur lequel on est censé travailler
int started=0;///permet de savoir quand le décompte de temps a commencé


void Board::loop(){
    
    //char buf[100];///definition du buffer d'écriture
    int val_lum;////valeur mesurée par le capteur de luminosité
    int verif_button;///stockage de l'état du bouton de vérification
    int tab_switch[4];///table dans laquelle on va stocker la valeur des switch
    int tab_s_needed[4]={1,0,1,1};///position des switch qui permet de débloquer l'étape
    
    /////on donne le tableau de solution pour les fils
    int tab_wire_needed[3]={10,140,320};
    int tab_wire[4];
  
    ///création du tableau de note pour la mélodie
    int melody[9]={320,200,560,149,600,589,305,789,654};
    
    val_lum=analogRead(0);
    cout<<endl;
    if(val_lum==19){////and time !=0;
        cout<<"capteur de lum couvert\n";
        ////démarage du timer
        if (step==0){
            
            if (started==0){
                
                digitalWrite(15,HIGH);///on alume la diode de la section des interrupteurs
                digitalWrite(18,HIGH);
            }  
            
            /////on met a jour le tableau des valeurs des switchs
            for (int i=0;i<4;i++){
                tab_switch[i]=analogRead(2+i);
            }
            verif_button=analogRead(1);
            if (verif_button==1){///on rearde si une demande de vérification est faite
                if(tab_equal(tab_switch,tab_s_needed,4)){///si les switchs sont dans le bon ordre
                    digitalWrite(15,LOW);///on éteint la led rouge
                    digitalWrite(19,HIGH);///on allume la led verte de résolution de l'étape
                    digitalWrite(16,HIGH);///on allume la led rouge de la section clavier avec son pour indiquer la prochaine zone à manipuler
                    ////emettre un son?
                    
                    step++;///on passe à l'étape suivant
                    started=0;///on réinitialise pour pouvoir s'en resservir dans la prochaine étape
                    PlayMelody(melody,HP);///lecture de la mélodie à reproduire pendant cette lecture le programme est en attente
                }
                else{
                    digitalWrite(18,HIGH);
                    ////réduction du temps
                }
            } 
        }
        else if (step==1){
            verif_button=analogRead(1);
            if (verif_button==1){
                
                digitalWrite(16,LOW);///on éteint la led rouge
                digitalWrite(17,HIGH);///on allume la led rouge de la section fils pour indiquer la prochaine zone à manipuler
                digitalWrite(20,HIGH);///on allume la led verte de résolution de l'étape
                //freq=analogRead(25);
                //sprintf(buf,"temperature %d",val);
                //Serial.println(buf);

                step++;
                started=0;
            }            
        }
        else if (step==2){
            for (int i=0;i<3;i++){
                tab_wire[i]=analogRead(22+i);///on relève les valeurs stockée sur les pin de réception de la partie wire
            }
            verif_button=analogRead(1);
            if (verif_button==1){
                
                if (tab_equal(tab_wire,tab_wire_needed,3)){
                   
                    digitalWrite(17,LOW);
                    digitalWrite(21,HIGH);
                    
                    sleep(5);
                    
                    ////on arrete le timer
                }
                else{
                    ///réduction du temps
                }
            }  
        }    
    }
    else{////et temps !=0
        cout<<"capteur de lum pas couvert\n";
    }
    
    /*ELSE EXPLOSION*/
                
    sleep(1);
           
}


