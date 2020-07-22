
#include <stdio.h>
#include <stdlib.h>

#include "main.h"





int main()
{
  

int choix;    
do
{

printf("\t\tBIENVENU DANS LE JEU DEVIN\n");
printf("--------------------------------------------------------------------------------------\n");
printf("\t\t\tMENU\n");
int continuer=1,rejouer=1, stdin=1;
printf("\t\t\t1->jouer\n\t\t\t2->remplir pesonnage\n\t\t\t3->voir les statistiques\n\t\t\t4->quitter\n");
scanf("%d",&choix);

switch(choix)
{
    case 1:
        break;

    case 2:
        
        remplir_personnage();
        rejouer=0;
        break;

    case 3: 
        affich_statistique();
        rejouer=0;
        stdin=0;
        break;

    case 4:
        rejouer= 0;  
        break;
     default:
        printf("vous n'avez pas entrer la bonne valeur\n");
        rejouer=0;
        break;        


}
    
if (rejouer==1)

{
   
    printf("VEUILLEZ PENSER A UN PERSONNAGE, NOUS LE DEVINERONS\n");
    printf("----------------------------------------------------\n");

    historique(1,0,0);

    /* compt_question:s'incrémente chaque fois qu'une question est posée*/
    
    int compt_question=0; 
    int i;
    int num_question=1;
    rejouer=0;
    continuer=1;

    /*le tableau tab stocke les réponses renseignées à chaque question: 1ere colonne->numéro des questions posées, 2eme colonne->réponses*/

    int nb_quiz=(nb_questions()*2)+1;
    int **tab=(int**)malloc(sizeof(int*)*nb_quiz);

    for(i=0;i<nb_quiz;i++)
    {
        tab[i]=(int*)malloc(sizeof(int)*2);
    }

   
    
    for(i=0;i<nb_quiz-1;i+=2)
    {
        tab[i][0]=num_question;
        tab[i][1]=0;
        tab[i+1][0]=' ';    /*permettent d'avoir un espace entre chaque réponse dans le fichier Population.txt*/
        tab[i+1][1]=' ';
        num_question++;
    }

    tab[nb_quiz-1][0]=-1;
    tab[nb_quiz-1][1]=-1;

    
    /*déclaration  et initisalisation de la liste des personnages*/

    LISTE_SIMPLE *L=(LISTE_SIMPLE*)malloc(sizeof(LISTE_SIMPLE));
    L->tete=NULL;
    init_point_par_personnage(L);       
    
    
     /*déclaration  et initisalisation de la liste des questions*/  

    ListeSimple *Li=(ListeSimple*)malloc(sizeof(ListeSimple));
    Li->tete=NULL;

    init_point_par_question(Li);
    
    /*printf("affichage question init\n");
    affichage_questions(*Li);
    printf("\n");  (mis en commentaire car elle a déjà été testée*/

    
    
     while( rejouer==0 && continuer==1)     
    {
         /*recherche la meilleure question puis l'affiche*/
      
       
        comptage(Li);
       
        int num=choix_question(Li);
       
       /* printf("La question %d sera posée\n",num);*/
     
        suppression_question(Li,num);
       
        poser_question(num);
        printf("\n");
        compt_question++;
        
        /*mise à jour des points des personnages selon la réponse du joueur,après avoir posée la question*/
        
        tab=calcul_point_par_personnage(L,num,tab);
        

        /*On commence à éliminer à partir de la 5ème question pour ne pas tout éliminer du 1er coup car les points sont initialisés à 0*/
        
        if(compt_question >=5)
        {
            Eliminer(L);
            /*printf("les personnages en lice sont:\n");
            affichage(*L);*/
        }


        /*le programme présente le  personnage qui correspond au mieux à la description du joueur :
        à la 6ème 12éme, 18éme question (chaque multiple de 6 hormis 0) le personnage au meilleur score est présenté
        
        s'il reste un seul personnage en lice ou  si toutes les questions ont été posées alors on affiche les noms de tous les personnages
        le joueur dira si son personnage y est présent ou non: si oui alors appel à la fonction ajouter_personnage sinon alors fonction ajouter_question
       
        */

        
        /*la mise a jour des reponses si le programme a trouvé juste se fait automatiquement dans la fonction personnage_trouve*/

        if( (compt_question!=0 && compt_question%6==0) || taille(*L)==1 || compt_question==nb_questions() )     
        {
            int trouve=personnage_trouve(L, tab);   /*0->pas trouvé 1->trouvé*/
           
            if(trouve==1)
            {
                 
                printf("Voulez-vous rejouer ?\n 1->oui 0->non\n");
                scanf("%d",&rejouer);
                continuer=0;
            }
            

            else
            {
                
                    if(taille(*L)!=1 && compt_question!=nb_questions())
                    {
                        
                        printf("on continue? 1->oui 0->non\n");
                        scanf("%d",&continuer);

                        if(continuer==0)
                        {
                            printf("voulez-vous rejouer ?\n 1->oui 0->non?\n");
                            scanf("%d",&rejouer);
                            
                        }
                        
                    }
                    
                    if( ( taille(*L)==1 || compt_question==nb_questions() ) && continuer!=0)
                    {
                          affich_list_pers();

                          int presence_pers;
                          printf("votre personnage figure-t-il dans la liste ?\n 1->oui 0->non\n"); scanf("%d",&presence_pers);
                         clean_stdin();
                           if(presence_pers==1 )
                           {
                               
                             
                               ajouter_question_fichier();
                               printf("voulez-vous rejouer ?\n 1->oui 0->non\n");
                               scanf("%d",&rejouer);
                               continuer=0; 
                                

                               
                            }
                            if(presence_pers==0)
                            {
                                printf("Qui était votre personnage ?\n");
                                ajouter_personnage(tab,nb_quiz);
                
                                printf("voulez-vous rejouer ?\n 1->oui 0->non\n");
                                scanf("%d",&rejouer);
                                continuer=0;

                            }
                     }

            }/*fin else*/

        }/*fin if*/
    
  }/*fin while*/


if(rejouer==0)
    {int j=0;
     for(;j<nb_quiz;j++)
        free(tab[j]);
     free(tab); 
     break;
    }
int j=0;
for(;j<nb_quiz;j++)
    free(tab[j]);
free(tab);



}/*fin while principal*/                 

 if(stdin==1)clean_stdin();  } while(choix!=4);
printf("AU REVOIR :)\n");


return 0;
}









/*Ajout en tete de liste d'un personnage
paramètres: la liste chainée des personnages et N° dans le fichier population du personnage à ajouter
son nombre de point est initialisé à 0*/

void ajout_personnage(LISTE_SIMPLE *L,int n)
{
	
    /*on cree le personnage */

    PERSONNAGE*ptr=(PERSONNAGE*)malloc(sizeof(PERSONNAGE));
	
	ptr->nbre_points=0;
	ptr->suivant=NULL;

    ptr->num_personnage=n;
    
   
    /*chainage et ajout en tete de liste*/

    ptr->suivant=L->tete;
    L->tete=ptr;



}








/*Récupère le nombre de personnages qu'il y a dans le fichier population.txt*/

int nb_personnages()
{
	FILE *file;
	int nb_pers=0;
	int car;
	
	file=fopen("Population.txt","r");
	if(file==NULL)printf("ouverture Population.txt ERREUR\n");
	else
		{
			while((car=fgetc(file))!=EOF)
				{
					if(car==45 && fgetc(file)==49)nb_pers++;			/*ascii(-)=45, ascii(1)=49*/
				}
		}
	fclose(file);
	return nb_pers;

}





/*au début on crée une liste simplement chaîné de tous les personnages du fichier population.txt*/
	



void init_point_par_personnage(LISTE_SIMPLE *L)
{
	

	int num_personnage=1;
	int n_pers=nb_personnages();
	while(num_personnage <= n_pers)
		ajout_personnage(L,num_personnage++);
		

}



/*Affiche le contenu de la liste: peut nous servir pour une autre fonction*/


void affichage(LISTE_SIMPLE L)
{	
	
	
	
	PERSONNAGE *P=L.tete;
	if(P==NULL)return;
	printf("N°\t points\n");
	while(P!=NULL)
	{
		
		
		printf("%d\t %d \n",P->num_personnage,P->nbre_points);
		P=P->suivant;

	}
	

}







/*supprime de la liste un personnage au rang   int rang */


void suppression_personnage(LISTE_SIMPLE *L, int rang)
{
	PERSONNAGE *ptr_cour, *ptr_prec;
	int i;
	if (rang == 1) 
		{
			ptr_cour = L->tete;
			L->tete = ptr_cour->suivant;
			free(ptr_cour);
		} 
	else 
	{
	i = 1;
	ptr_prec = L->tete;
	while (i != rang-1) 
		{
			i++;
			ptr_prec = ptr_prec->suivant;
		}
	ptr_cour = ptr_prec->suivant;
	ptr_prec->suivant = ptr_cour->suivant;
	free(ptr_cour);
	}
}	

	


/*retourne le nombre de personnages à éliminer (critere d'élimination: nombre de points<10)*/



int nbre_a_eliminer(LISTE_SIMPLE L)
{
	int nb=0;
	PERSONNAGE *ptr=L.tete;
	while(ptr!=NULL)
	{
		if(ptr->nbre_points <10) nb++;
		ptr=ptr->suivant;
	}



return nb;
}	






/*supprime tout personnage dont le nombre de points est < 10   de la liste des personnages en lice*/

void Eliminer (LISTE_SIMPLE *L)
{
	
	/*cretaion d'un tableau dynamique et stocke les rangs dans la liste, des personnages à éliminer */

	int nbre= nbre_a_eliminer(*L) ;	
	if(nbre==0)return;
	int *position=(int*)malloc(sizeof(int)*nbre);
	
	int i=0;
	

	PERSONNAGE *ptr=L->tete;
	while(ptr!=NULL)
	{
		
		if(ptr->nbre_points <10) 
			{
				position[i]=ptr->num_personnage;
				i++;
			}	
		ptr=ptr->suivant;
	}


	/*elimination, appel à la fonction suppression(LISTE_SIMPLE *L, int rang) */
	
	for(i=0;i<nbre;i++)
	{
			int a=0; int test=0;
			PERSONNAGE *ptr=L->tete;
			while(ptr!=NULL && test!=1)
			{
			  a++;
			  if(ptr->num_personnage==position[i] )
				{
					suppression_personnage(L,a );
					
					test=1;
					
					
				}
		
				
			  ptr=ptr->suivant;
			}
	}


	/*libération de la mémoire allouée */

	free(position);

}		



/******Fonction calcul point par personnage**********/

/*cette fonction retourne le nombre de personnage encore en lice(peut servir dans une autre fonction)*/

int taille(LISTE_SIMPLE L)
{
	PERSONNAGE *ptr=L.tete;
	int t=0;
	while(ptr!=NULL)
	{
		t++;
		ptr=ptr->suivant;
	}
	return t;
}

/*cette fonction prend en paramètre un pointeur sur un PERSONNAGE, le N° du PERSONNAGE dans le fichier Population.txt
ainsi que la réponse entrée par le joueur(entre 0---5) puis calcul et met à jour son nombre de point suite à une question*/


void point(PERSONNAGE*ptr,int num,int reponse,int meill_question)
{
	

	FILE *flux=fopen("Population.txt","r");
	if(flux==NULL)
		{
			printf("ouverture fichier Population.txt ERREUR");
			return;
		}
	
	int i=1;
	int test=0; 
	int car;

	if(i==num);   /*on passe à la suite de la procédure*/
	
	else
		{
			
			/*on se positionne dans le fichier Population.txt, sur la ligne du PERSONNAGE*/
			
			while( (car=fgetc(flux))!=EOF  && test!=1)
			{
			
				if(car==45 && fgetc(flux)==49)			/*ascii(-)=45, ascii(1)=49*/
				{
					i++;
					if(i==num)test=1;

					/*on se met à la ligne du personnage*/
					while(car!='\n' && car!=EOF)
						car=fgetc(flux);
						
				}


			}
		}


		/*On recupère la réponse correspondante à la question */
		
		car=fgetc(flux);
		test=0;
		while(  car!=EOF && test!=1)
		{
			if(car=='|')
			{
				
				fseek(flux,(meill_question-1)*2,SEEK_CUR);
				car=fgetc(flux);
				test=1;

			}
			if(test==0)
				car=fgetc(flux);
		}	

		fclose(flux);
		
		/*calcul et mise à jour du point du PERSONNAGE: on pourra modifier cette notation de points si elle convient pas*/
		car=car-'0';
		/*printf("la rep dans le fichier du personnage %d à la question %d est =%d\n",num,meill_question,car);*/
		

		if(reponse==car)
			ptr->nbre_points +=30;
		
		else if(reponse-car==1 || reponse-car==-1)		/*ecart abs de 1 entre la reponse donnée et celle attendue*/
			ptr->nbre_points +=20;

		else if(reponse-car==2 || reponse-car==-2)
			ptr->nbre_points +=10;
		
		else if(reponse-car==3 || reponse-car==-3)
			ptr->nbre_points -=10;

		else 											/* ecart abs de 4 reponse-car==4 || reponse-car==-4 */
			ptr->nbre_points -=20;

	

}



/*Calcul et met à jour le nombre de points de chaque personnage apès une question*/

int** calcul_point_par_personnage(LISTE_SIMPLE *L, int meill_question, int** tab)
{
	
	
	
	int reponse=-1;						
	int i=0;

	
	while(reponse>5 || reponse<0)
	{
		printf("Entrer votre réponse entre 0-5:\n0->pour la non connaissance de la bonne réponse\n1->sûrement\n2->probablement oui\n3->ne sais pas\n4->probablement non\n5->sûrement pas\n");scanf("%d",&reponse);			
	
		while(tab[i][0]!=meill_question)i++;

		tab[i][1]=reponse;
		
	}

	


	PERSONNAGE *ptr=L->tete;
	while(ptr!=NULL)
	{
		point(ptr,ptr->num_personnage,reponse,meill_question);
		ptr=ptr->suivant;
	}
	
return tab;
}







/*Ajout en tete de liste d'une question
son nombre de point est initialisé à 0*/

void ajout_question(ListeSimple *L,int n)
{

    /*on cree la question */

    QUESTION*ptr=(QUESTION*)malloc(sizeof(QUESTION));

	ptr->nbre_points=0;
	ptr->suivant=NULL;

    ptr->num_question=n;


    /*chainage et ajout en tete de liste*/

    ptr->suivant=L->tete;
    L->tete=ptr;

}

/*au début on crée une liste simplement chaîné de toutes les questions du fichier questions.txt*/


void init_point_par_question(ListeSimple *L)
{

	int num_question=1;
	int n_quest=nb_questions();
	while(num_question <= n_quest)
		ajout_question(L,num_question++);


}



/*Récupère le nombre de questions qu'il y a dans le fichier questions.txt*/


int nb_questions()
{
	FILE *file;
	int nb_quest=0;
	int car;
	file=fopen("questions.txt","r");
	if(file==NULL)printf("ouverture questions.txt ERREUR\n");
	else
		{
			while((car=fgetc(file))!=EOF)
				{
					if(car=='\n')nb_quest++;
				}
		}
	fseek(file,0,SEEK_SET);	/*remise du curseur au début*/
	fclose(file);
	return nb_quest;

}

/*Récupère le nombre de questions qu'il y a dans la liste chainée*/

int nb_question_chaine(QUESTION *tete)
{
    int i;
    if(tete==NULL)
    {
        return 0;
    }
    else{
        i=1+nb_question_chaine(tete->suivant);
        return i;
    }
}



/*Affiche le contenu de la liste: peut nous servir pour une autre fonction*/


void affichage_questions(ListeSimple L)
{



	QUESTION *Q=L.tete;
	if(Q==NULL)return;
	printf("N°\t points\n");
	while(Q!=NULL)
	{


		printf("%d\t %d \n",Q->num_question,Q->nbre_points);
		Q=Q->suivant;

	}


}


/*supprime de la liste une question numero num
on trouve son rang dans la liste chainée avant */


void suppression_question(ListeSimple *L, int num)
{
	QUESTION *ptr_cour, *ptr_prec;
	int rang=1;
	ptr_cour=L->tete;
	while(ptr_cour->num_question!=num)
	{
        rang++;
        ptr_cour=ptr_cour->suivant;
	}
	int i=1;
	if (rang == 1)
		{
			ptr_cour = L->tete;
			L->tete = ptr_cour->suivant;
			free(ptr_cour);
		}
	else
	{
	ptr_prec = L->tete;
	while (i != rang-1)
		{
			i++;
			ptr_prec = ptr_prec->suivant;
		}
	ptr_cour = ptr_prec->suivant;
	ptr_prec->suivant = ptr_cour->suivant;
	free(ptr_cour);
	}
}

/*Compte le nombre de points pour chaques questions de la liste chainée*/

void comptage (ListeSimple *L)
{
    QUESTION *ptr=L->tete;
    while(ptr!=NULL)
    {
        ptr->nbre_points=(nb_rep(ptr->num_question,1)+1)*(nb_rep(ptr->num_question,2)+1)*(nb_rep(ptr->num_question,3)+1)*(nb_rep(ptr->num_question,4)+1)*(nb_rep(ptr->num_question,5)+1);
        ptr=ptr->suivant;
    }
}

/*Retourne le nombre de personnages qui ont la réponse rep à la question numéro :int question*/


int nb_rep (int question, int rep)
{

	int car, nb_reponses=0;
	FILE *file;
	file=fopen("Population.txt","r");
	if(file==NULL)printf("ouverture Population.txt ERREUR\n");
	car=fgetc(file);
	while(  car!=EOF)
	{
		if(car=='|')
		{

			fseek(file,(question-1)*2,SEEK_CUR);
			if( (car=fgetc(file)) == rep +'0') nb_reponses++;

			while( car !='\n') car=fgetc(file);

		}

		car=fgetc(file);
	}
fclose(file);
return nb_reponses;
}


/* Retourne le rang de la queston avec le nombre de points le plus élevé */

int choix_question(ListeSimple *L)
{
    int num=0;
    QUESTION *ptr=L->tete;
    int score=0;
    while(ptr!=NULL)
    {
        if(ptr->nbre_points>score)
        {
            score=ptr->nbre_points;
            num=ptr->num_question;
        }
        ptr=ptr->suivant;
    }
    return num;

}


/*Affiche la question numéro rang*/

void poser_question(int rang)
{
    FILE *file;
    int i=1;
	int car;
	file=fopen("questions.txt","r");
	if(file==NULL)printf("ouverture questions.txt ERREUR\n");
	else
		{
			while((car=fgetc(file))!=EOF)
				{
                    if(i==rang)
                    {
                        while(car!='\n')
                        {
                            printf("%c",car);
                            car=fgetc(file);
                        }
                        printf("\n");
                        break;
                    }
					if(car=='\n')i++;
				}
		}
	fclose(file);
}




/*retourne 1: si le personnage a bien été deviné
retourne 0: si le personnage n'a pas bien été deviné
retourne -1 si ouverture impossible du fichier
tab est un tableau 2d qui contient sur la 1ere colonne les N°questions et des espaces
                                   sur la 2èm colonne les réponses renseignées au fur et à mesure de la partie*/



int personnage_trouve(LISTE_SIMPLE *L, int** tab)
{
	
	PERSONNAGE *ptr=L->tete;
	
	
	int max_point=0, num_pers;
	int test=0; 
	int car;
	int i=1;
	int trouve=0;
	
/*on récupère le numéro du personnage qui a le plus grand nombre de points*/
	
	while(ptr!=NULL)
	{
		if(ptr->nbre_points >=max_point) 
		{
			max_point=ptr->nbre_points;
			num_pers=ptr->num_personnage;
		}
		ptr=ptr->suivant;
	}	
	
		
	FILE *flux=fopen("Population.txt","r");		
	if(flux==NULL)
		{
			printf("ouverture Population.txt ERREUR\n");
			return -1;
		}
	
	
	if(num_pers==1);   /*on passe à la suite de la procédure*/
	
	else
		{
			

				
		/*on se positionne dans le fichier Population.txt, sur la ligne du PERSONNAGE*/
			
			while( (car=fgetc(flux))!=EOF  && test!=1)
			{
			
				if(car==45 && fgetc(flux)==49)			/*ascii(-)=45, ascii(1)=49: indique la fin d'un vecteur réponses*/
				{
					i++;
					if(i==num_pers)test=1;

					/*on se met à la ligne du personnage*/
					while(car!='\n' && car!=EOF)
						car=fgetc(flux);
							
				}

			}
		}


	/*suite de la procédure*/

	/*On affiche le nom du personnage qu'on a trouvé (celui avec le plus grand nombre de points parmi ceux en lice)*/
	
	fseek(flux,-1,SEEK_CUR);
	 printf("Votre personnage est: ");
	while( (car=fgetc(flux))!=EOF && car!='|')
	{
		
		printf("%c",car);
		
	}

   printf("\n");
   

    /*On demande si le personnage est le bon*/
    int choix;
    printf("Est-ce votre personnage ?\n");
    printf("1->oui  0->non");scanf("%d",&choix);
    if(choix==1)
    {
    	mise_a_jour_rep(tab,num_pers);	
    	historique(0,1,0);
    	trouve=1;	
    	
   		
    	
    }	

    else	/*si le programme n'a pas trouvé le bon personnage*/
    {
    	
    		trouve=0;
    	/*on met -10000 au score du personnage pour qu'il soit retiré de la liste des personnages en lice*/
    		ptr=L->tete;
    		while(ptr!=NULL)
    		{
    			if(ptr->num_personnage==num_pers)
    			{
    				ptr->nbre_points=-10000;
    				break;
    			}
    			ptr=ptr->suivant;
    		}
    	
    }
fclose(flux);   
return trouve;

}




/*sauvegarde 
incrémente de 1 le nombre de parties jouées: historique(1,0,0)
incrémente de 1 le nombre de  personnages bien dévinés: historique(0,1,0)
incrémente de 1 le nombre de personnages rajoutés:    historique(0,0,1)
le fichier historique.txt contient dans l'ordre le nombre de parties jouées, le nombre de  personnages bien dévinés,  le nombre de personnages rajoutés
*/



void historique(int partie_joue,int bien_devine,int rajoute)
{
	FILE *flux=NULL;
	flux = fopen("historique.txt","r+");
	
	
	if(flux==NULL){
		printf("ouverture impossible\n");
		return;
		}

	int *tab=(int*)malloc(sizeof(int)*3);
	fscanf(flux,"%d",tab);
	fscanf(flux,"%d",tab+1);
	fscanf(flux,"%d",tab+2);
	tab[0]+=partie_joue;
	tab[1]+=bien_devine;
	tab[2]+=rajoute;
	fseek(flux,0,SEEK_SET);
	fprintf(flux,"%d",tab[0]);
	fputc(' ',flux);
	fprintf(flux,"%d",tab[1]);
	fputc(' ',flux);
	fprintf(flux,"%d",tab[2]);
	fclose(flux);
	free(tab);

}





/*affiche le nom du personnage N°num_pers: si int num_pers=3 il affichera le nom du personnage N°3 du fichier Population.txt */


void affich_nom_personn(int num_pers)

{
	int car;
	int test=0;
	int i=1;

	FILE *flux=fopen("Population.txt","r");


	if(flux==NULL)
	{
		printf("ouverture Population.txt ERREUR\n");
		return;
	}


	if(num_pers==1);   /*on passe à la suite de la procédure*/
	
	else
		{
			

				
		/*on se positionne dans le fichier Population.txt, sur la ligne du PERSONNAGE*/
			
			while( (car=fgetc(flux))!=EOF  && test!=1)
			{
			
				if(car==45 && fgetc(flux)==49)			/*ascii(-)=45, ascii(1)=49  : indicateur de la fin d'un vecteur réponses*/
				{
					i++;
					if(i==num_pers)test=1;

					/*on se met à la ligne du personnage*/
					while(car!='\n' && car!=EOF)
						car=fgetc(flux);
							
				}

			}
		}


	/*suite de la procédure*/

	/*On affiche le nom du personnage */
	
	fseek(flux,-1,SEEK_CUR);
	while( (car=fgetc(flux))!=EOF && car!='|')
	{
		printf("%c",car);
	}

    
    printf("\n");
    
    fclose(flux);

}


/*affiche la liste des noms de tous les personnages du fichier Population.txt*/

void affich_list_pers()
{
	int nb_pers=nb_personnages();
	int i=1;
	while(i<=nb_pers)
	{
		affich_nom_personn(i);
		i++;
	}
}



/*mise à jour des réponses (est appellée quand le programme devine bien un personnage)
le tabeau 2d a été défini dans le main:il mémorise les réponses entrées par le joueur pour chaque question*/

/*int num_pers: est le numéro du personnage dans le fichier Population.txt bien déviné*/


void mise_a_jour_rep(int** tab, int num_pers)
{
	int car;
	int test=0;
	int i=1;
	

	FILE *flux=fopen("Population.txt","r+");		


	if(flux==NULL)
	{
		printf("ouverture Population.txt ERREUR\n");
		return;
	}

	/*on se positionne à la ligne du personnage*/
    
	if(num_pers==1);   /*on passe à la suite de la procédure*/
	
	else
		{
			

				
		/*on se positionne dans le fichier Population.txt, sur la ligne du PERSONNAGE*/
			
			while( (car=fgetc(flux))!=EOF  && test!=1)
			{
			
				if(car==45 && fgetc(flux)==49)			/*ascii(-)=45, ascii(1)=49: indicateur de la fin d'un vecteur réponses*/
				{
					i++;
					if(i==num_pers)test=1;

					/*on se met à la ligne du personnage*/
					while(car!='\n' && car!=EOF)
						car=fgetc(flux);
							
				}

			}
		}


	
		/*on avance jusqu'à trouver le debut du vecteur reponse,le caracatre | */
		car=fgetc(flux);
		test=0;
		while(  car!=EOF && test!=1)
		{
			if(car=='|')test=1;
				
			if(test==0)
				car=fgetc(flux);
		}	


		
	i=0;	

	/*mise à jour des rep: remplacement des 0 par les reponses renseignées*/
    
    while((car=fgetc(flux))!=45 && car!=EOF)		/*ascii(-)=45*/
	{
		i++;
		if(car-'0'==0)
		{
			fseek(flux,-1,SEEK_CUR);
			fputc(tab[i-1][1]+'0',flux);
		}
	}



fclose(flux);
}



/*permet de rajouter un personnage: les réponses correspondant au personnage rajouté sont celles renseignées au cours de la partie
les réponses aux questions qui n'ont pas été posées sont mises à 0 */


void ajouter_personnage(int** tab,int nb_quiz)
{
	FILE *flux=NULL;
	FILE *dest=NULL;
	char personnage[100];
	int car;
	int espace=32;	
	char barre='|';
	flux=  fopen("Population.txt","r+");
	dest= fopen("dest.txt","w+");
	
	/*vérification après ouverture*/
	if(flux==NULL || dest==NULL)
	{
		printf("ouverture impossible\n");
		return;
	}
		
	
	printf("Ecrivez le nom de votre personnage\n");
	scanf("%[^\n]",personnage);

	
	fprintf(dest,"%s",personnage);
	fputc(espace,dest);
	fputc(espace,dest);
	fputc(espace,dest); 
	fputc(barre,dest);


	int z=0;
	/*le vecteur de réponse coorespond à ceux renseignées par le jouer, stocké dans tab */
	while(tab[z][0]!=-1)
	{
		int car=tab[z][1];
		if(car==32 || car==80)fputc(espace,dest);
		else
			fputc(car+'0',dest);
		z++;
	}

fputc('-',dest);
fputc('1',dest);	
fputc('\n',dest);


car=fgetc(flux);
do
{
	fputc(car,dest);
}while(  (car=fgetc(flux))!=EOF  );




fclose(flux);
fclose(dest);
	
remove("Population.txt");
rename("dest.txt","Population.txt");
historique(0,0,1);

}


/*fonction permettant d'effacer le buffer lorsqu'il y a 2 scanf qui se suivent, il y a un problème avec l'un des scanf sans cette fonction*/			

void clean_stdin() 
{ 
    int c; 
  
    do { 
        c = getchar(); 
    } while (c != '\n' && c != EOF); 
}			


/*Permet de mettre la réponse correspondante à la nouvelle question rajoutée à 0 pour tous les vecteurs réponses*/

void copy_with_0()
{
	FILE *src=fopen("Population.txt","r");
	FILE*dest=fopen("dest.txt","w+");
	int car;
	if(src==NULL || dest==NULL)
	{
		printf("erreur ouverture\n");return;
	}
car=fgetc(src);	
do
{
	
	if(car=='-')
		{
			
			if(fgetc(src)=='1')
			{
			
			fputc('0',dest);
			fputc(' ',dest);
			fputc('-',dest);
			fputc('1',dest);
			
			
			}
			else
				fseek(src,-1,SEEK_CUR);

		}

	else
		fputc(car,dest);


}while((car=fgetc(src))!=EOF);
	
fclose(src);
fclose(dest);	

remove("Population.txt");

rename("dest.txt","Population.txt");	

}


/*permet de rajouter une question*/

void ajouter_question_fichier()		
{
	FILE *flux=NULL;
	char *question=(char*)malloc(sizeof(char)*100);
	flux = fopen("questions.txt","a+");
	
	
	if(flux==NULL){
		printf("ouverture impossible\n");
		return;
		}
	
	
	printf("Quelle question aurait permise de deviner votre personnage ?\n");
	scanf("%[^\n]",question);
	
	fseek(flux,0,SEEK_END);
	fprintf(flux,"%s\n",question);
	
	fclose(flux);
	
	free(question);
	
	copy_with_0();	/*permet de compléter le vecteur réponse de chaque personnage avec 0 (vu qu'on a rajouté une question)*/
	
}




void remplir_personnage()
{
	
	/*le tableau tab stocke les réponses renseignées à chaque question: 1ere colonne->numéro des questions posées, 2eme colonne->réponses*/

    int i; int t=0;
    int num_question=1;
    int nb_quiz=(nb_questions()*2)+1;
    int **tab=(int**)malloc(sizeof(int*)*nb_quiz);

    for(i=0;i<nb_quiz;i++)
    {
        tab[i]=(int*)malloc(sizeof(int)*2);
    }

   
    
    for(i=0;i<nb_quiz-1;i+=2)
    {
        tab[i][0]=num_question;
        tab[i][1]=0;
        tab[i+1][0]=' ';    /*permettent d'avoir un espace entre chaque réponse dans le fichier Population.txt*/
        tab[i+1][1]=' ';
        num_question++;
    }

    tab[nb_quiz-1][0]=-1;
    tab[nb_quiz-1][1]=-1;

/*On pose les questions correspondant à son personnage*/
int quiz=nb_questions();
i=1;
while(i<=quiz)
{
	poser_question(i);
	i++;
	int reponse=-1;						

	
	while(reponse>5 || reponse<0)
	{
		printf("Entrer votre réponse entre 0-5\n");scanf("%d",&reponse);			/*on invite le personnage à entrer sa réponse (entre 0----5)*/

		tab[t][1]=reponse;
		t+=2;
		
	}

}

clean_stdin();

/*ajout du personnage et des réponses correspondantes*/
	FILE *flux=NULL;
	FILE *dest=NULL;
	char personnage[100];
	int car;
	int espace=32;	
	char barre='|';
	flux=  fopen("Population.txt","r+");
	dest= fopen("dest.txt","a+");
	
	/*vérification après ouverture*/
	if(flux==NULL || dest==NULL)
	{
		printf("ouverture impossible\n");
		return;
	}
		
	
	printf("Ecrivez le nom de votre personnage\n");
	scanf("%[^\n]",personnage);

	fseek(dest,0,SEEK_END);	
	fprintf(dest,"%s",personnage);

	fputc(espace,dest);
	fputc(espace,dest);
	fputc(espace,dest); 
	fputc(barre,dest);

	
	int z=0;
	/*le vecteur de réponse coorespond à ceux renseignées par le jouer, stocké dans tab */
	while(tab[z][0]!=-1)
	{
		int car=tab[z][1];
		if(car==32 || car==80)fputc(espace,dest);
		else
			fputc(car+'0',dest);
		z++;
	}
	
fputc('-',dest);
fputc('1',dest);	
fputc('\n',dest);


car=fgetc(flux);
do
{
	fputc(car,dest);
}while(  (car=fgetc(flux))!=EOF  );




fclose(flux);
fclose(dest);
	
remove("Population.txt");
rename("dest.txt","Population.txt");
historique(0,0,1);

/*libération de la mémoire*/
int j=0;
for(;j<nb_quiz;j++)
    free(tab[j]);
free(tab);
}



 void affich_statistique()
 {
 	FILE * flux=fopen("historique.txt","r");
 	if(flux==NULL)
 	{
 		printf("ouverture hist*.txt erreur\n"); return;
 	}
 
 	int *tab=(int*)malloc(sizeof(int)*3);
	fscanf(flux,"%d",tab);
	fscanf(flux,"%d",tab+1);
	fscanf(flux,"%d",tab+2);
	
	printf("statistiques\n");
	printf("nombre de parties jouées: %d\nnombre de personnages bien devinées: %d\nnombre de personnages rajoutées: %d\n",tab[0],tab[1],tab[2]);

	free(tab);

 }











