#include <unistd.h>
#include "core_simulation.h"
#include "vector"

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
    pinMode(pSwitch,OUTPUT);
    pinMode(pPad,OUTPUT);
    pinMode(pWire,OUTPUT);
    
    ///LED INDICE
    pinMode(pClue,OUTPUT);
    
    ///LEDS PARTIES RESOLUES
    pinMode(pSdone,OUTPUT);
    pinMode(pPdone,OUTPUT);
    pinMode(pWdone,OUTPUT);
    
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
    
    ///pin pour vérifier que le boite est fermée et pour le verrou
    pinMode(BOX,OUTPUT);
    pinMode(P_CLOSED,INPUT);
    
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
bool find(int val,vector<int> v1){
    bool found;
    for(int i=0; i<v1.size(); i++){
        if (v1[i]==val){
            found=true;
        }
    }
    return found;
}

int tab_switch[4];///table dans laquelle on va stocker la valeur des switch
int tab_s_needed[4]={1,0,1,1};///position des switch qui permet de débloquer l'étape

/////on donne le tableau de solution pour les fils
int tab_wire_needed[3]={10,140,320};
int tab_wire[4]; 
///création du tableau de note pour la mélodie
int melody[4]={200,150,450,350}; 
vector<int> tab_pin_ref_melo {9,8,14,12};
vector<int> tab_pin_used_melo;
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
                SwitchClueLED();///on lance l'indice en parallèle pour ne pas bloquer l'exéution du code
                started++;
            }  
 
            /////on met a jour le tableau des valeurs des switchs
            for (int i=0;i<4;i++){
                tab_switch[i]=analogRead(2+i);
            }


            verif_button=digitalRead(1);

            if (verif_button==1){///on rearde si une demande de vérification est faite

                if(tab_equal(tab_switch,tab_s_needed,4)){///si les switchs sont dans le bon ordre
                    digitalWrite(pSwitch,LOW);///on éteint la led rouge
                    digitalWrite(pSdone,HIGH);///on allume la led verte de résolution de l'étape
                    digitalWrite(pPad,HIGH);///on allume la led rouge de la section clavier avec son pour indiquer la prochaine zone à manipuler
                    
                    step++;///on passe à l'étape suivant
                    PlayMelody(melody,HP);///lecture de la mélodie à reproduire pendant cette lecture le programme est en attente
                }
                else{
                    erreur++;//on incrément le nombre d'erreur qui est limité à 5
                    sprintf(buf,"erreur %d/5",erreur);
                    //Serial.println(buf);
                    bus.write(1,buf,100);
                    if (erreur!=5){
                        SwitchClueLED();///on redonne l'indice visuel en lancant le clignottement des LEDs
                    }
                    else {
                        Explosion();
                    }
                }
            } 
        }
        else if (step==1){
            sprintf(buf,"laissez vous guider par la musique et enrtez le code à 4 chiffres");
            bus.write(1,buf,100);
            while (step!=2){
                for (int i=0;i<9;i++){
                    if (not(find(6+i,tab_pin_used_melo)) and digitalRead(6+i)==1){
                        tab_pin_used_melo.push_back(6+i);///on stocke les bouton activé et on les places dans un tableau
                        int value_pin=6+i;
                        envoyer_son_HP(value_pin);
                    }  
                }
                verif_button=digitalRead(30);
                if (verif_button==1){   
                    if (tab_pin_used_melo==tab_pin_ref_melo and tab_pin_used_melo.size()==4){
                        digitalWrite(pPad,LOW);///on éteint la led rouge
                        digitalWrite(pWire,HIGH);///on allume la led rouge de la section fils pour indiquer la prochaine zone à manipuler
                        digitalWrite(pPdone,HIGH);///on allume la led verte de résolution de l'étape
                        step++;    
                    }
                    else{
                        erreur++;
                        tab_pin_used_melo.clear();
                        sprintf(buf,"erreur %d/5",erreur);
                        //Serial.println(buf);
                        bus.write(1,buf,100);
                        if (erreur!=5){
                            PlayMelody(melody,HP);///lecture de la mélodie à reproduire pendant cette lecture le programme est en attente
                        }
                        else {
                            Explosion();
                            step++;
                         }    
                    }       
                }
            }
        } 
        else if (step==2){
            for (int i=0;i<3;i++){
                tab_wire[i]=analogRead(22+i);///on relève les valeurs stockée sur les pin de réception de la partie wire
            }
            verif_button=digitalRead(31);
            if (verif_button==1){
                
                if (tab_equal(tab_wire,tab_wire_needed,3)){
                   
                    digitalWrite(pWire,LOW);
                    digitalWrite(pWdone,HIGH);
                    
                    sprintf(buf,"seriez vous un enseignant incroyable?");
                    bus.write(1,buf,100);
                    
                    digitalWrite(BOX,HIGH);
                    sprintf(buf,"la boite peut maintenant être ouverte");
                    bus.write(1,buf,100);
                    
                    sleep(DELAY);
                    
                    digitalWrite(pSdone,LOW);
                    digitalWrite(pPdone,LOW);
                    digitalWrite(pWdone,LOW);
                    
                    sprintf(buf,"Pour recommencer, fermer la boite et appuyer sur start");
                    bus.write(1,buf,100);
                    
                    start_button=digitalRead(32);
                    if (start_button!=0 && digitalRead(P_CLOSED)==HIGH){
                        digitalWrite(BOX,LOW);
                        step=0;
                        started=0;
                        erreur=0;     
                    } 
                }
                else{
                    erreur++;
                    sprintf(buf,"erreur %d/5",erreur);  
                    bus.write(1,buf,100);
                    if (erreur==5){
                         Explosion(); ///on active l'explosion
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
        bus.write(1,buf,100);
        sleep(5);
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


