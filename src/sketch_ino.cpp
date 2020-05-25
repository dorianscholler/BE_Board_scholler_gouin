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
    pinMode(30,INPUT);
    pinMode(31,INPUT);
    
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
    
    ///pin pour le bouton start
    pinMode(32,INPUT);
   
    ////explosion définie comme input 
    analogWrite(29,INPUT);
    
    ////petite initialisation des leds 
    ///initialisation des LED à l'état bas
    for (int i=0; i<7;i++){
        analogWrite(15+i,0);
    }   
    
    ///initialisation de l'explosion 
    analogWrite(29,0);

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


int tab_switch[4];///table dans laquelle on va stocker la valeur des switch
int tab_s_needed[4]={1,0,1,1};///position des switch qui permet de débloquer l'étape

/////on donne le tableau de solution pour les fils
int tab_wire_needed[3]={10,140,320};
int tab_wire[4]; 
///création du tableau de note pour la mélodie
int melody[9]={300,200,500,100,600,700,400,800,900};  
//////definitions des variables externes à notre fonction, nécessité de faire bien attention aux mdiffications
int step=0;///permet d'empêcher les manipulation des autres blocs que celui sur lequel on est censé travailler
int started=0;///permet de savoir quand le décompte de temps a commencé
int erreur=0;

void Board::loop(){
    char buf[100];///definition du buffer d'écriture
    int val_lum;////valeur mesurée par le capteur de luminosité
    int verif_button;///stockage de l'état du bouton de vérification
    int start_button;///detecte l'activation du bouton start
    
      
    val_lum=analogRead(0);
    cout<<endl;
    if(val_lum==19 && erreur<5){
        cout<<"capteur de lum couvert\n";
        ////démarage du timer
        if (step==0){
            
            if (started==0){
                digitalWrite(pSwitch,HIGH);///on alume la diode de la section des interrupteurs
                digitalWrite(pClue,HIGH);///on lance l'indice en parallèle pour ne pas bloquer l'exéution du code
            }  
            
            /////on met a jour le tableau des valeurs des switchs
            for (int i=0;i<4;i++){
                tab_switch[i]=analogRead(2+i);
            }
            verif_button=analogRead(1);
            if (verif_button==1){///on rearde si une demande de vérification est faite
                if(tab_equal(tab_switch,tab_s_needed,4)){///si les switchs sont dans le bon ordre
                    digitalWrite(pSwitch,LOW);///on éteint la led rouge
                    digitalWrite(pSdone,HIGH);///on allume la led verte de résolution de l'étape
                    digitalWrite(pPad,HIGH);///on allume la led rouge de la section clavier avec son pour indiquer la prochaine zone à manipuler
                    
                    step++;///on passe à l'étape suivant
                    PlayMelody(melody,HP);///lecture de la mélodie à reproduire pendant cette lecture le programme est en attente
                }
                else{
                    erreur++;
                    sprintf(buf,"erreur %d/5",erreur);
                    Serial.println(buf);
                    if (erreur!=5){
                        digitalWrite(pClue,HIGH);///on redonne l'indice visuel en lancant le clignottement des LEDs
                    }
                    else {
                        analogWrite(29,HIGH); ///on active l'explosion
                                        
                        ////on allume toutes les led rouges
                        digitalWrite(pSwitch,HIGH);
                        digitalWrite(pPad,HIGH);
                        digitalWrite(pWire,HIGH);
                        
                        ///et on éteint toutes les autres
                        digitalWrite(pSdone,LOW);
                        digitalWrite(pPdone,LOW);
                        digitalWrite(pWdone,LOW);
                    }
                }
            } 
        }
        else if (step==1){
            verif_button=analogRead(30);
            if (verif_button==1){
                
                digitalWrite(pPad,LOW);///on éteint la led rouge
                digitalWrite(pWire,HIGH);///on allume la led rouge de la section fils pour indiquer la prochaine zone à manipuler
                digitalWrite(pPdone,HIGH);///on allume la led verte de résolution de l'étape
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
            verif_button=analogRead(31);
            if (verif_button==1){
                
                if (tab_equal(tab_wire,tab_wire_needed,3)){
                   
                    digitalWrite(pWire,LOW);
                    digitalWrite(pWdone,HIGH);
                    
                    sleep(5);
                }
                else{
                    erreur++;
                    sprintf(buf,"erreur %d/5",erreur);
                    Serial.println(buf);                    
                    if (erreur==5){
                        digitalWrite(29,HIGH); ///on active l'explosion
                        
                        ////on allume toutes les led rouges
                        digitalWrite(pSwitch,HIGH);
                        digitalWrite(pPad,HIGH);
                        digitalWrite(pWire,HIGH);
                        
                        ///et on éteint toutes les autres
                        digitalWrite(pSdone,LOW);
                        digitalWrite(pPdone,LOW);
                        digitalWrite(pWdone,LOW);
                    }         
                }  
            }    
        }
    }
    else if (erreur<5){////et temps !=0
        cout<<"capteur de lum pas couvert\n";
    }
    else{
        ///si il y eu les 5 erreur on quitte tout il faut recommencer
        sprintf(buf,"Vous avez échoué");
        Serial.println(buf);
         
        ///on éteint toutes les LED restantes
        digitalWrite(pSwitch,LOW);
        digitalWrite(pPad,LOW);
        digitalWrite(pWire,LOW);
        
        start_button=digitalRead(32);
        if (start_button!=0){
            step=0;
            started=0;
            erreur=0;     
        }  
    }
    sleep(1);        
}


