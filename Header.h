#ifndef HEADER_H
#define HEADER_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*fonctions*/
typedef struct une_liste_de_mots *Liste;

struct une_liste_de_mots
{
	char *mot;
	Liste mots_suivants;
};

typedef struct un_noeud Noeud;

struct un_noeud
{
	Liste liste;
	Noeud *fils[8];
};


/*création arbre*/
Liste initialise_liste(char *mot); /*ok*/
Noeud* initialise_noeud(); /*ok*/

void transforme_la_chaine_en_chiffres(char *chaine, int *chiffre, int N); /*crée le chemin*/ /*ok*/
int transforme_le_caractere_en_chiffre(char carac); /*ok*/

void ajoute_le_mot_au_noeud(int *chemin, char *le_mot, Noeud *arbre, int N); 

//void afficher_arbre(Noeud* arbre, GtkLabel* label_mot);
void afficher_liste(Liste liste, GtkTextView* text_view);


Noeud* construit_arbre();

/*interface utilisateur*/
char* demande_a_l_utilisateur_la_chaine_de_chiffre();

void parcours_arbre(Noeud* arbre, char* code, GtkLabel* label_code);

void t9(char* code, GtkLabel* label_code);

char* lire_chaine(char* msg);

/*destruction arbre*/
void detruire_liste(Liste liste);
void detruire_arbre(Noeud* arbre);


G_MODULE_EXPORT void on_window1_realize(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_window1_destroy(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_button2_clicked(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_button3_clicked(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_button4_clicked(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_button5_clicked(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_button6_clicked(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_button7_clicked(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_button8_clicked(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_button9_clicked(GtkObject *object, gpointer user_data);
G_MODULE_EXPORT void on_button10_clicked(GtkObject *object, gpointer user_data);
void ajoute_chiffre_bouton_au_label(int valeur_chiffre_bouton);
void rafraichir_affichage();

#endif