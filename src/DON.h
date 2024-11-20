#ifndef DON_H_INCLUDED
#define DON_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>


typedef struct 
{
    char  blood_type[20],center[20];
    int   id_don,quantity,month,day,year;
}Don ;
int ajouter(char*,Don);
int modifier(char*,int,Don);
int supprimer(char *,int);
Don chercher(char* ,int);
void afficher(GtkWidget *liste);
int calculate_blood_quantity(const char *file_name, const char *blood_type);
void extract_bloodtype(const char *file_name);
void sang_rare(char nomFichier[], char sangRare[]);
#endif // DON_H_INCLUDED
 
