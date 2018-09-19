#include <stdio.h>   /* sprintf */
#include <stdlib.h>  /* atoi */
#include <string.h>  /* strlen, strcmp */
#include <ctype.h>   /* isdigit */
#include <math.h>
#include <gtk/gtk.h>
#include "Header.h"

extern GtkBuilder *builder;

Noeud* arbre;
GtkTextView *text_view;


#define MAX_LIGNE 100



void afficher_liste(Liste liste, GtkTextView* text_view)
{
	GtkLabel *label_code = GTK_LABEL(gtk_builder_get_object(builder, "label2"));
	const char* code;
	code = gtk_label_get_text(label_code);

	GtkTextBuffer* buff = gtk_text_buffer_new(NULL);
	
	int i=0;
	GtkTextIter* j = malloc(12 * sizeof(GtkTextIter));
	//char msgtot[1024];
	char msg[16];
	Liste tmp = liste;
	while (tmp != NULL)
	{
		sprintf_s(msg, 16, "%s",tmp->mot);
		gtk_text_buffer_get_iter_at_offset(buff, j, i);
		gtk_text_buffer_insert(buff, j, msg, -1);
		tmp = tmp->mots_suivants;
	}
	
	gtk_text_view_set_buffer(text_view, buff);
	free(j);
}

void afficher_arbre(Noeud* arbre, GtkTextView* text_view)
{
	int i;
	if (arbre != NULL)
	{
		afficher_liste(arbre->liste, text_view);
		for (i = 0; i < 8; i++)
		{
			afficher_arbre(arbre->fils[i], text_view);
		}
	}
}

Liste initialise_liste(char *mot) /*ok*/
{
	Liste ma_liste = malloc(sizeof(struct une_liste_de_mots));
	ma_liste->mot = (char *)malloc((sizeof(char))*(strlen(mot) + 1));
	if ((ma_liste->mot) == NULL)
	{
		perror("Allocation memoire");
		exit(1);
	}
	strcpy_s(ma_liste->mot, strlen(mot) + 1, mot);
	ma_liste->mots_suivants = NULL;
	return ma_liste;
	
}

Noeud* initialise_noeud() /*ok*/
{
	int i;
	Noeud *box = malloc(sizeof(struct un_noeud));
	box->liste = NULL;
	for (i = 0; i < 8; i++)
	{
		box->fils[i] = NULL;
	}
	return box;
}

int transforme_le_caractere_en_chiffre(char carac) /*ok*/ /*essayer avec la structure switch*/
{

	if ((carac == 'a') || (carac == 'b') || (carac == 'c'))
	{
		return 2;
	}
	else if ((carac == 'd') || (carac == 'e') || (carac == 'f'))
	{
		return 3;
	}
	else if ((carac == 'g') || (carac == 'h') || (carac == 'i'))
	{
		return 4;
	}
	else if ((carac == 'j') || (carac == 'k') || (carac == 'l'))
	{
		return 5;
	}
	else if ((carac == 'm') || (carac == 'n') || (carac == 'o'))
	{
		return 6;
	}
	else if ((carac == 'p') || (carac == 'q') || (carac == 'r') || (carac == 's'))
	{
		return 7;
	}
	else if ((carac == 't') || (carac == 'u') || (carac == 'v'))
	{
		return 8;
	}
	else if ((carac == 'w') || (carac == 'x') || (carac == 'y') || (carac == 'z'))
	{
		return 9;
	}
	else
	{
		return -1;
	}

	return 0;
}

void transforme_la_chaine_en_chiffres(char *chaine, int *chiffre, int N)
/*ok --> met les touches correspondant à la chaine dans un tableau de chiffres de taille N*/
{
	char *pt;
	pt = chaine;
	int i;

	for (i = 0; i < N; i++)
	{
		chiffre[i] = transforme_le_caractere_en_chiffre(*(pt + i));
	}

}

void ajoute_le_mot_au_noeud(int *chemin, char *le_mot, Noeud *arbre, int N) /*N=taille du chemin*/
{
	int i;
	Noeud *cur_box = arbre;
	Liste old_list;

	for (i = 0; i < N - 1; i++)
	{
		int valeur_chemin = chemin[i] - 2;

		/*printf(" > %d ", chemin[i]);*/

		/*va cherche le noeud correspondant*/

		if (cur_box->fils[valeur_chemin] == NULL)
		{
			cur_box->fils[valeur_chemin] = initialise_noeud();
		}

		cur_box = cur_box->fils[valeur_chemin];
	}

	/*printf("ajoute mot %s\n", le_mot);*/

	/*ajoute le mot en fin de liste du noeud*/
	old_list = cur_box->liste;
	cur_box->liste = initialise_liste(le_mot);
	cur_box->liste->mots_suivants = old_list;

}

void parcours_arbre(Noeud* arbre, char* code, GtkLabel* label_code)
{
	unsigned int i;
	Noeud* noeud = arbre;

	char* chaine;
	chaine = code;

	unsigned int len = strlen(chaine);

	for (i = 0; i < len  && noeud != NULL; i++)
	{
		/*printf("adresse de chaine %s\n", &chaine);*/

		int numero_fils = *(chaine + i) - 50;

		/*printf("numero fils %d\n", numero_fils);*/
		noeud = noeud->fils[numero_fils];
	}

	if (noeud == NULL && i < len) 
	{
		int i = 0;
		GtkTextIter* j = malloc(12 * sizeof(GtkTextIter));
		GtkTextBuffer* message = gtk_text_buffer_new(NULL);
		gtk_text_view_set_buffer(text_view, message);
		gtk_text_buffer_get_iter_at_offset(message, j, i);
		gtk_text_buffer_insert(message, j, "Plus de mot correspondant", -1);
		gtk_text_view_set_buffer(text_view, message);
		free(j);
	}
	else if (noeud != NULL && noeud->liste != NULL)
	{
		afficher_liste(noeud->liste, text_view);
	}
	else
	{
		int i = 0;
		GtkTextIter* j = malloc(12 * sizeof(GtkTextIter));
		GtkTextBuffer* message = gtk_text_buffer_new(NULL);
		gtk_text_view_set_buffer(text_view, message);
		gtk_text_buffer_get_iter_at_offset(message, j, i);
		gtk_text_buffer_insert(message, j, "Pas de mot correspondant", -1);
		gtk_text_view_set_buffer(text_view, message);
		free(j);
	}
	
}

void t9(char* code, GtkLabel* label_code)
{
	
	parcours_arbre(arbre, code, label_code);

}

G_MODULE_EXPORT void on_window1_realize(GtkObject *object, gpointer user_data)
{
	GtkLabel *label2 = GTK_LABEL(gtk_builder_get_object(builder, "label2"));

	char init_label[1] = { '\0' };
	gtk_label_set_text(label2, init_label);

	arbre = construit_arbre();
	text_view = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "textview1"));

}

void detruire_liste(Liste liste)
{
	if (liste != NULL)
	{
		detruire_liste(liste->mots_suivants);
		free(liste->mot);
		free(liste);
	}
}

void detruire_arbre(Noeud* arbre)
{
	int i;
	if (arbre != NULL){
		for (i = 0; i < 8; i++)
		{
			detruire_arbre(arbre->fils[i]);
		}
		detruire_liste(arbre->liste);
		free(arbre);
	}
}

G_MODULE_EXPORT void on_window1_destroy(GtkObject *object, gpointer user_data)
{
	detruire_arbre(arbre);
	printf("bye.\n");
	gtk_main_quit();
}

Noeud* construit_arbre()
{
	FILE* dico;
	char mot[MAX_LIGNE];
	int* chemin;
	int N;
	Noeud* racine = initialise_noeud();
	Noeud* tmp;

	fopen_s(&dico, "dictionnaire.txt", "r");
	if (dico == NULL)
	{
		printf("Failed to open dictionnary in read mode");
		exit(-2);
	}

	while (fgets(mot, MAX_LIGNE, dico) != NULL)
	{
		tmp = racine;
		N = strlen(mot);
		chemin = malloc(N * sizeof(int));

		transforme_la_chaine_en_chiffres(mot, chemin, N);
		ajoute_le_mot_au_noeud(chemin, mot, tmp, N);
	}
	free(chemin);
	fclose(dico);
	return tmp;
}

void ajoute_chiffre_bouton_au_label(int valeur_chiffre_bouton)
{
	char valeur_label[2];
	sprintf_s(valeur_label, 2, "%d", valeur_chiffre_bouton);

	GtkLabel *label2 = GTK_LABEL(gtk_builder_get_object(builder, "label2"));

	const char* existant;

	existant = gtk_label_get_text(label2);

	if (strlen(existant) == 0)
	{
		gtk_label_set_text(label2, valeur_label);
	}
	else
	{
		const int N = (strlen(existant) + 1 + 1);
		char* nouveau_label = malloc(sizeof(char)*N);

		strcpy_s(nouveau_label, N, existant);
		strcat_s(nouveau_label, N, valeur_label);

		gtk_label_set_text(label2, nouveau_label);
		free(nouveau_label);
	}
}

G_MODULE_EXPORT void on_button2_clicked(GtkObject *object, gpointer user_data)
{
	ajoute_chiffre_bouton_au_label(2);
	rafraichir_affichage();
}
G_MODULE_EXPORT void on_button3_clicked(GtkObject *object, gpointer user_data)
{
	ajoute_chiffre_bouton_au_label(3);
	rafraichir_affichage();
}
G_MODULE_EXPORT void on_button4_clicked(GtkObject *object, gpointer user_data)
{
	ajoute_chiffre_bouton_au_label(4);
	rafraichir_affichage();
}
G_MODULE_EXPORT void on_button5_clicked(GtkObject *object, gpointer user_data)
{
	ajoute_chiffre_bouton_au_label(5);
	rafraichir_affichage();
}
G_MODULE_EXPORT void on_button6_clicked(GtkObject *object, gpointer user_data)
{
	ajoute_chiffre_bouton_au_label(6);
	rafraichir_affichage();
}
G_MODULE_EXPORT void on_button7_clicked(GtkObject *object, gpointer user_data)
{
	ajoute_chiffre_bouton_au_label(7);
	rafraichir_affichage();
}
G_MODULE_EXPORT void on_button8_clicked(GtkObject *object, gpointer user_data)
{
	ajoute_chiffre_bouton_au_label(8);
	rafraichir_affichage();
}
G_MODULE_EXPORT void on_button9_clicked(GtkObject *object, gpointer user_data)
{
	ajoute_chiffre_bouton_au_label(9);
	rafraichir_affichage();
}
G_MODULE_EXPORT void on_button10_clicked(GtkObject *object, gpointer user_data)
{
	GtkLabel *label2 = GTK_LABEL(gtk_builder_get_object(builder, "label2"));

	const char* existant;

	existant = gtk_label_get_text(label2);

	const int N = (strlen(existant)+1);
	char* nouveau_label = malloc(sizeof(char)*N);

	strcpy_s(nouveau_label, N, existant);
	if (N > 1)
	{
		nouveau_label[N - 2] = '\0';
		gtk_label_set_text(label2, nouveau_label);
	}
	else
	{
		printf("Impossible d'effacer");
	}
	rafraichir_affichage();
	free(nouveau_label);
}

void rafraichir_affichage()
{
	GtkLabel *label_code = GTK_LABEL(gtk_builder_get_object(builder, "label2"));
	GtkLabel *label_mots = GTK_LABEL(gtk_builder_get_object(builder, "label4"));

	const char* code;
	code = gtk_label_get_text(label_code);
	
	int N = strlen(code)+2;
	if (N > 4)
	{
		char* code2 = malloc(sizeof(char)*N);
		strcpy_s(code2, N, code);

		t9(code2, label_mots);
		free(code2);
	}
	else
	{ 
		int i = 0;
		GtkTextIter* j = malloc(12 * sizeof(GtkTextIter));
		GtkTextBuffer* message = gtk_text_buffer_new(NULL);
		gtk_text_view_set_buffer(text_view, message);
		gtk_text_buffer_get_iter_at_offset(message, j, i);
		gtk_text_buffer_insert(message, j, "Rentrer au moins 3 chiffres", -1);
		gtk_text_view_set_buffer(text_view, message);
		free(j);
	}
}


