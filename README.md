# BE_C++_Casse tête

COMPILATION:
-Commencez par cloner le git avec l'URL : https://github.com/dorianscholler/BE_Board_scholler_gouin.git
-Placez vous dans le répertoire ainsi crée.
-Retirer tous les .txt et les placez sur le bureau de façon à ce qu'ils soient facilement accessibles
-Dans dossier du git lancer la commande ./compile_linux.sh


LANCEMENT:
Une fois le programme compilé, utiliser la commande ./arduino dans le répertoire du git afin de lancer l'application

COMPOSITION:
Nottre boîte se compose de trois parties :

-Un bloc composé de 4 interrupteurs, de trois LED, une rouge, une verte et une bleue et d'un bouton de vérification. Lorsque cette partie est disponible, la LED rouge s'allume. A partir de e moment il faut mettre les switchs dans la bonne position et appuyer sur le bouton de vérification. Si les interrupteurs sont bien placés, la LED verte s'allume, une mélodie retentie  et la LED rouge de la prochaine partie à manipuler s'allume. Si la combinaison est la mauvaise lecompteur d'erreur augmente de 1 et il faut réessayer. A 5 erreur le casse tête émet n son toute les LEDs rouges clignottent et il faut appuyer sur le bouton start pour recommencer. 

Indice : au déput de la partie des switch la LED bleur clignonte 1 ois pour indiquer l'activation du premier interrupteur, 3 fois pour le troisième et 4 fois pour le quatrième. Cette indice est redonné en cas d'erreur. 

-Un bloc composé d'un clavier digital et d'un Haut parleur. Lorsque la première partie est résolue, une mélodie retentit. Chacun des bouton du clavier numérique produit une des notes de cette mélodie. Il faut donc comme pour un Simon reproduire la melodie avec le clavier et appuyer sur le bouton de vérification une fois que l'on pense avoir réussi.

Indice: l'indice est redonné en cas d'erreur.

-Un bloc composé de 6 pins, 3 disposant d'un câble et 3 pouvant en accueillir un. Il faut associer à chacun des trois pin libre un fil. Après avoir appuyer sur le bouton de vérification de la partie, si l'agencement est le bon, le puzzle est résolu. 

Indice : pas d'indice ici, juste de la chance.  

FICHIERS .TXT:
On retrouve parmis les fichiers .txt:
-4 fichiers switchi.txt avec i allant de 1 à 4. 
-9 fichiers i.txt avec i allant de 1 à9.
-3 fichier connecti.txt avec i={10,140,320}.
-3 fichiers verifi.txt avec i allant de 1 à 4.
-1 fichier start.txt.
-1 fichier couvert.txt

Ces fichiers texts permettent de simuler des interraction avec le casse-tête, il est donc nécessaire de placer ou d'enlever ces fichiers du dossier dans le quel se trouve le dossier source et le fichier ./compile_linux.sh.

FONCTIONNEMENT : 

Pour commencer, il faut couvrir le capteur de luminosité avec couvert.txt. Si le capteur n'est pas couvert, rien ne peut être manipulé.

Pour l'étape 1, il faut placer les fichiers switch 1, 3 et 4.txt puis verif1.txt.

Pour l'étape 2,

Pour l'étape 3, on place les fochiers connect 10, 140 et 320.txt suivit du fichier verif3.txt.

En cas d'échec retirez les fichiers et remplacez les par start.txt pour pouvoir recommencer. Une fois la partie relancée enlevé le start.txt.

