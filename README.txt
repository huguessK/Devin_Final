
JEU: LE DEVIN 

Equipes

Gaël LEMIERE: Github RobinFarges
Hugues KOUAKOU: Github huguessK
Octavian OLIVIER: Github Octavski
Robin FARGES: Github GaelLemi

Objectifs

Développer un jeu, comportant une interface graphique, où l’ordinateur devine le personnage auquel l’utilisateur pense. L’ordinateur posera une suite de questions et tentera d’en déduire le choix de personnage du joueur. 
Il sera possible d’ajouter manuellement un personnage dans le jeu. Cela permettra d’étoffer notre base de donnée au fur et à mesure.


Description

Un PERSONNAGE est définit par son nombre de points, son numéro dans la base de données Populations.txt et un pointeur vers le PERSONNAGE suivant : une liste simplement chaînée nous a donc été utile pour stocker tous les personnages.

Une QUESTION est définit par son nombre de points (pertinence), son numéro dans la base de données questions.txt et un pointeur vers la QUESTION suivante : une liste simplement chaînée nous a donc été utile pour stocker toutes questions. 

Le principe est de sélectionner la meilleure question (la plus pertinente), de la poser puis de calculer le nombre de points de chaque personnage en fonction de la réponse renseignée par l’utilisateur (entre 0 et 5). Une fois une question posée, on la supprime de la liste chaînée qui stocke les questions pour ne pas la reposer. Au fur et à mesure que la partie avance, on élimine les personnages dont le score est très faible (<=10) on présente le personnage au meilleur score à l’utilisateur qui dira si le programme a trouvé juste ou pas: 2 cas se présente dès lors.

Cas 1: Le programme a trouvé juste
Dans ce cas on met à jour le vecteur réponses correspondant au personnage deviné (remplacement des 0 par les réponses renseignées), on lui propose de rejouer.

Cas 2: Le programme n’a pas trouvé juste
Dans ce cas, on lui propose de continuer sur une seconde série de questions et le cycle reprend. S’il arrive qu’il n’y ait plus aucune question à poser ou qu’il reste un seul personnage en lice et que le programme n’a toujours pas trouvé le bon personnage alors, on 
affiche à l’utilisateur tous les noms des personnages dans notre base de données: Si son personnage s’y trouve alors on lui demande quelle question aurait permis de deviner son 


personnage et si son personnage n’est pas dans la liste alors on lui demande de saisir le nom de son personnage.
Suite à la saisie de son personnage, le vecteur réponse correspondant au personnage sont automatiquement mis à jour avec les réponses renseignées durant la partie.


Pour compiler le projet


make  
./code



pour effacer les fichiers objets générés par la compilatio: make clean


Amélioration

Lier le code C à l’interface graphique codée en (Python Tkinter, C GTK+ ...) pour avoir une meilleure expérience utilisateur.
