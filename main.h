

/*UN presonnage est representé par son N° dans le fichier population.txt et son nombre de points*/

typedef struct personnage{
	int nbre_points;
	int num_personnage;
	struct personnage * suivant;
}PERSONNAGE;


/*tete de la liste chainée des personnages*/

typedef struct 
{
 PERSONNAGE *tete;
}LISTE_SIMPLE;


/*Une question est representé par son N° dans le fichier question.txt et son nombre de points pour la question à venir*/

typedef struct question{
	int nbre_points;
	int num_question;
	struct question * suivant;
}QUESTION;


/*tete de la liste chainée des questions*/

typedef struct
{
 QUESTION *tete;
}ListeSimple;




int nombre_questions();
int nb_rep (int question, int rep);
void ajout_personnage(LISTE_SIMPLE *L,int n);
int nb_personnages();
void init_point_par_personnage(LISTE_SIMPLE *L);
void affichage(LISTE_SIMPLE L);
void suppression_personnage(LISTE_SIMPLE *L, int rang);
int nbre_a_eliminer(LISTE_SIMPLE L);
void Eliminer (LISTE_SIMPLE *L);
int taille(LISTE_SIMPLE L);
void point(PERSONNAGE*ptr,int num,int reponse,int meill_question);
int** calcul_point_par_personnage(LISTE_SIMPLE *L,int meill_question,int** tab);
void ajout_question(ListeSimple *L,int n); 
void init_point_par_question(ListeSimple *L);
int nb_questions();
int nb_question_chaine(QUESTION *tete);
void affichage_questions(ListeSimple L);
void suppression_question(ListeSimple *L, int num);
void comptage (ListeSimple *L);
int nb_rep (int question, int rep);
int choix_question(ListeSimple *L);
void poser_question(int rang);
int personnage_trouve(LISTE_SIMPLE *L, int** tab);
void historique(int partie_joue,int bien_devine,int rajoute);
void affich_nom_personn(int num_pers);
void affich_list_pers();
void mise_a_jour_rep(int** tab, int num_pers);
void copy_with_0();
void ajouter_question_fichier();	
void ajouter_personnage(int** tab,int nb_quiz);
void clean_stdin() ;
void remplir_personnage();
void affich_statistique();


