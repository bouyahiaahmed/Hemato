#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"donneur.h"
#include <gtk/gtk.h>

enum
{ 
EFULLNAME,
EIDNUMBER,
EDAY,
EMONTH,
EYEAR,
ETYPE,
EGENDER,
EETS,
COLUMNS,
}; 
enum 
{
ENAME,
EID,
EBIRTHDAY,
EBIRTHMONTH,
EBIRTHYEAR,
EBLOODTYPE,
EGENDERR,
EETSS,
COLUMNSS,

};



//Ajouter fiche donneur
int ajouter_fiche_donneur(donneur D,char *filename){
FILE * f;
int c=0;
f=fopen(filename,"a");
if (f!=NULL){
  fprintf(f,"%s %s %d %s %d %s %s %s \n",D.fullname,D.idnumber,D.birthday,D.birthmonth,D.birthyear,D.type,D.gender,D.ets);
  c=1;
  fclose(f);
}
return c;
}


//Afficher fiche donneur
void afficher_fiche_donneur(GtkWidget *liste){
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	
	char nom[30];
	char cin[10];
	char jour[10];
	char mois[30];
	char annee[30];
	char type[30];
	char sexe[30];
	char ets[30];
	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model(liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Full_Name", renderer, "text",ENAME,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("ID_Number", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Birth_Day", renderer, "text",EBIRTHDAY,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Birth_Month", renderer, "text",EBIRTHMONTH,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Birth_year", renderer, "text",EBIRTHYEAR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",EBLOODTYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Gender", renderer, "text",EGENDERR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Establishment", renderer, "text",EETSS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);}
	
	
	store=gtk_list_store_new(COLUMNSS,G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING);

	f= fopen("donneur.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		while(fscanf(f,"%s %s %s %s %s %s %s %s \n",nom,cin,jour,mois,annee,type,sexe,ets)!=EOF)
		{

			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, ENAME, nom, EID, cin, EBIRTHDAY, jour, EBIRTHMONTH, mois ,EBIRTHYEAR,annee,  EBLOODTYPE, type, EGENDERR,sexe, EETSS, ets,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}

        
//supprimer fiche donneur

void supprimer_fiche_donneur(char id[],char *filename)
{
donneur D;     
FILE * f=fopen(filename,"r");
FILE * f2=fopen("donsupp.txt","w");

while (fscanf(f,"%s %s  %d %s %d %s %s %s\n  ",D.fullname,D.idnumber,&D.birthday,D.birthmonth,&D.birthyear,D.type,D.gender,D.ets)!=EOF)
{

if(strcmp(D.idnumber,id)!=0)

  fprintf(f2,"%s %s %d %s %d %s %s %s  ",D.fullname,D.idnumber,D.birthday,D.birthmonth,D.birthyear,D.type,D.gender,D.ets);
}
  fclose(f);

  fclose(f2);

remove(filename);
rename("donsupp.txt",filename);
 
}


        
//Modifier fiche doneur
void modifier_fiche_donneur(char cin[],donneur D1,char *filename)
{
donneur D;
  FILE* f=fopen(filename, "r");
  FILE* f2=fopen("donmod.txt", "w");
  
  if((f!=NULL) ||( f2!=NULL))
 {
while(fscanf(f,"%s %s %d %s %d %s %s %s \n",D.fullname,D.idnumber,&D.birthday,D.birthmonth,&D.birthyear,D.type,D.gender,D.ets)!=EOF)
{
if(strcmp(D.idnumber,cin)==0)
  fprintf(f2,"%s %s %d %s %d %s %s %s \n ",D1.fullname,D.idnumber,D1.birthday,D1.birthmonth,D1.birthyear,D1.type,D1.gender,D1.ets);
else
 fprintf(f2,"%s %s %d %s %d %s %s %s \n ",D.fullname,D.idnumber,D.birthday,D.birthmonth,D.birthyear,D.type,D.gender,D.ets);
}
   fclose(f);
   fclose(f2);
remove(filename);
rename("donmod.txt",filename);
 }
}

//Remplissage tableau 
int remplir_tableau_Rech (donneur tab[],int nb)
{
    char nom[20];
    int jour;
    int  annee;
    char cin[20];
    char mois[20];
    char type[30];
    char sexe[30];
    char ets[30];
  
    FILE* fichier ;
    int i;

    fichier = fopen("donneur.txt", "a+");

        while (fscanf(fichier,"%s %s %d %s %d %s %s %s \n",nom,cin,&jour,mois,&annee,type,sexe,ets)!=EOF)
        {
            strcpy(tab[i].fullname,nom);
	    tab[i].birthday=jour;
            strcpy(tab[i].birthmonth,mois);
	    tab[i].birthyear=annee;
	    strcpy(tab[i].idnumber,cin);
	    strcpy(tab[i].type,type);
	    strcpy(tab[i].gender,sexe);
	    strcpy(tab[i].ets,ets);	
            nb++;
	    i++;    
        }
        fclose(fichier);
	return(nb);
}

//rechercher fiche donneur

int rechercher_fiche_donneur(char id[])
{
donneur tab[100];
int nb;
int ce,i;
FILE*f;
ce=0;
nb=remplir_tableau_Rech (tab,nb);
for (i=0;i<nb;i++)
	{if (strcmp(id,tab[i].idnumber)==0)
		{
		ce=1;
		f=fopen("rechdon.txt", "w+");
		if("f!=NULL")			
	{fprintf(f,"%s %s %d %s %d %s %s %s \n",tab[i].fullname,tab[i].idnumber,tab[i].birthday,tab[i].birthmonth,tab[i].birthyear,tab[i].type,tab[i].gender,tab[i].ets);}
		fclose(f);		
		}
	
	}
return(ce);		
}

//Affichage recherche donneur
void afficher_rechercher_don(GtkWidget *liste)
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	
	GtkTreeIter iter;
	GtkListStore *store;
	char nom[30];
	char cin[10];
	char jour[10];
	char mois[30];
	char annee[30];
	char type[30];
	char sexe[30];
	char ets[30];
	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{
	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Full_Name", renderer, "text",EFULLNAME,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("ID_Number", renderer, "text",EIDNUMBER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Birth_Day", renderer, "text",EDAY,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Birth_Month", renderer, "text",EMONTH,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Birth_Year", renderer, "text",EYEAR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text",ETYPE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Gender", renderer, "text",EGENDER,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("Establishment", renderer, "text",EETS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("rechdon.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("rechdon.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s %s \n",nom,cin,jour,mois,annee,type,sexe,ets)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EFULLNAME, nom, EIDNUMBER, cin, EDAY, jour, EMONTH,  mois,EYEAR ,annee,  ETYPE,type , EGENDER, sexe, EETS, ets,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
	
}



//liste rdv 
int listeRDV(char nomFichier[], char ETS[], int jour, char mois[], int annee) {
    FILE *f2 = fopen(nomFichier, "r");
    if (f2 != NULL) {
        struct rdv1 r;
        char *appointments = malloc(500 * sizeof(char));  // Initial buffer size

        if (appointments == NULL) {
            fclose(f2);
            return NULL;  // Memory allocation failure
        }

        strcpy(appointments, "");  // Initialize the string

        while (fscanf(f2, "%s %d %s %d %s ",r.establishment, &r.date_rdv.day, r.date_rdv.month, &r.date_rdv.year, r.time) != EOF) {
            if (strcmp(r.establishment, ETS) == 0 && r.date_rdv.day == jour && r.date_rdv.year == annee && strcmp(r.date_rdv.month, mois) == 0) {
                // Concatenate the appointment information into the string
                sprintf(appointments + strlen(appointments), "-le rendez-vous est le %d, %s , %d a %s , a %s \n", r.date_rdv.day, r.date_rdv.month, r.date_rdv.year, r.time, r.establishment);
            }
        }

        fclose(f2);

        return appointments;
    }

    return NULL;  // File not opened
}


int nbETS(char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", file_name);
        return -1; // Return -1 to indicate an error
    }

    int count = 0;
    char c;
    int is_line = 0;

    // Read each character in the file
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            count++;
            is_line = 0;
        } else {
            is_line = 1;
        }
    }

    // If the last line doesn't end with a newline, count it
    if (is_line) {
        count++;
    }

    fclose(file);

    return count;
}

int getMonthNumber(char* month) {
    if (strcmp(month, "January") == 0) return 1;
    if (strcmp(month, "February") == 0) return 2;
    if (strcmp(month, "March") == 0) return 3;
    if (strcmp(month, "April") == 0) return 4;
    if (strcmp(month, "May") == 0) return 5;
    if (strcmp(month, "June") == 0) return 6;
    if (strcmp(month, "July") == 0) return 7;
    if (strcmp(month, "August") == 0) return 8;
    if (strcmp(month, "September") == 0) return 9;
    if (strcmp(month, "October") == 0) return 10;
    if (strcmp(month, "November") == 0) return 11;
    if (strcmp(month, "December") == 0) return 12;
    return -1;
}

// Function to calculate the average appointments on a given date
float moyRDV_ETS(char* file_name, int day, const char* month, int year) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", file_name);
        return 0;
    }

    char line[256];
    int count = 0;
    int total_appointments = 0;
    int month_number = getMonthNumber(month);

    while (fgets(line, sizeof(line), file)) {
        int app_day, app_year;
        char app_month[20];

        if (sscanf(line, "%*s %*s %d %s %d %*s %*s %*s", &app_day, app_month, &app_year) == 3) {
            if (app_day == day && app_year == year && getMonthNumber(app_month) == month_number) {
                total_appointments++;
            }
        }
    }

    fclose(file);

    return (total_appointments > 0) ? (float)total_appointments : 0;
}

