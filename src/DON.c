#include "DON.h"
#include <stdio.h>
#include <string.h>


int ajouter(char *filename, Don d)
{
    FILE *f = fopen(filename, "a");
    if (f != NULL)
    {
        fprintf(f, " %d %s %s %d %d %d %d\n",  d.id_don, d.blood_type, d.center, d.quantity, d.month, d.day, d.year);
        fclose(f);
        return 1;
    }
    else
        return 0;
}

int modifier(char *filename, int id_don, Don nouv)
{
    int tr = 0;
    Don d;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    while (fscanf(f, " %d %s %s %d %d %d %d\n",  &d.id_don, d.blood_type, d.center, &d.quantity, &d.day, &d.month, &d.year) != EOF)
    {
        if (d.id_don== id_don)
        {
            fprintf(f2, " %d %s %s %d %d %d %d\n", nouv.id_don, nouv.blood_type, nouv.center, nouv.quantity, nouv.day, nouv.month, nouv.year);
            tr = 1;
        }
        else
            fprintf(f2, " %d %s %s %d %d %d %d\n", d.id_don, d.blood_type, d.center, d.quantity, d.day, d.month, d.year);
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

int supprimer(char *filename, int id_don)
{
    int tr = 0;
    Don d;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, " %d %s %s %d %d %d %d\n", &d.id_don, d.blood_type, d.center, &d.quantity, &d.day, &d.month, &d.year) != EOF) {
            if (d.id_don != id_don) {
                // Write entries that do not match the id to the new file
                fprintf(f2, " %d %s %s %d %d %d %d\n", d.id_don, d.blood_type, d.center, d.quantity, d.day, d.month, d.year);
            } else {
                // Mark that we found the item to delete
                tr = 1;
            }
        }
    }
    fclose(f);
    fclose(f2);

    // Only remove the original file if it was successfully opened
    if (tr == 1) {
        remove(filename);
        rename("nouv.txt", filename);
    } else {
        // Clean up temporary file if no deletion was performed
        remove("nouv.txt");
    }
    
    return tr;}

Don chercher(char *filename, int id_don)
{
    Don d;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL)
    {
        while (tr == 0 && fscanf(f, "%d  %s %s %d %d %d %d\n", &d.id_don, d.blood_type, d.center, &d.quantity, &d.day, &d.month, &d.year) != EOF)
        {
            if (d.id_don == id_don)
            {
                tr = 1;
            }
        }
        fclose(f);
	if(tr==0)
	 d.id_don=-1;
    }
    return d;
}


//affichage
enum{
	Eid_don,
	Eblood_type,
	Ecenter,
	Equantity,
	Eday,
	Emonth,
	Eyear,
	COLUMNS
}; 
void afficher(GtkWidget *liste){
GtkCellRenderer *renderer;
GtkTreeViewColumn *column;
GtkTreeIter iter;
GtkListStore *store;
char id_don[20];
char blood_type[20];
char center[20];
char quantity[20];
char day[20];
char month[20];
char year[20]; 
store =NULL;
FILE *f;
store=gtk_tree_view_get_model(liste);
if (store==NULL){
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("id_don",renderer,"text",Eid_don,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
renderer=gtk_cell_renderer_text_new(); 
column=gtk_tree_view_column_new_with_attributes("center",renderer,"text",Ecenter,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("blood_type",renderer,"text",Eblood_type,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
renderer= gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("quantity",renderer,"text",Equantity,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("day",renderer,"text",Eday,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("month",renderer,"text",Emonth,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
renderer=gtk_cell_renderer_text_new();
column=gtk_tree_view_column_new_with_attributes("year",renderer,"text",Eyear,NULL);
gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
}
store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
f=fopen("don.txt", "r");
if (f==NULL){
return;
}
else {f=fopen("don.txt", "a+");
while(fscanf(f," %s %s %s %s %s %s %s\n",&id_don,blood_type,center,&quantity,&day,&month,&year)!=EOF){
gtk_list_store_append(store,&iter);
gtk_list_store_set(store,&iter,Eid_don,id_don,Eblood_type,blood_type,Ecenter,center,Equantity,quantity,Eday,day,Emonth,month,Eyear,year,-1);
}
fclose(f);
gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
g_object_unref(store);
}
}



void extract_bloodtype(const char *file_name) {
    char line[100];
    FILE *file = fopen(file_name, "r");
    FILE *output_file = fopen("bloodtype.txt", "w");

    if (file == NULL || output_file == NULL) {
        printf("Error opening file(s).\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char establishment[100];
        int quantity;
        char *blood_type_start, *blood_type_end;

        // Extract establishment name and quantity
        if (sscanf(line, "%*d %s %*s %d", establishment, &quantity) != 2) {
            printf("Error parsing line: %s\n", line);
            continue;
        }

        // Find the start and end of the blood type in the line
        blood_type_start = strchr(line, ' ');
        if (blood_type_start == NULL) {
            printf("Error finding blood type in line: %s\n", line);
            continue;
        }
        blood_type_start++;
        blood_type_end = strchr(blood_type_start, ' ');
        if (blood_type_end == NULL) {
            printf("Error finding blood type in line: %s\n", line);
            continue;
        }

        // Extract the blood type
        char blood_type[100];
        strncpy(blood_type, blood_type_start, blood_type_end - blood_type_start);
        blood_type[blood_type_end - blood_type_start] = '\0';

        // Write the extracted data to the output file
        fprintf(output_file, "%s %d\n", establishment, quantity, blood_type);
    }

    fclose(file);
    fclose(output_file);
}

int calculate_blood_quantity(const char *file_name, const char *blood_type) {
    int total_quantity = 0;
    char line[100];
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    while (fgets(line, sizeof(line), file)) {
        char blood_type_in_file[100];
        int quantity;

        // Parse blood type and quantity from the line
        if (sscanf(line, "%s %d", blood_type_in_file, &quantity) != 2) {
            printf("Error parsing line: %s\n", line);
            continue;
        }

        // Compare blood type with the provided one
        if (strcmp(blood_type_in_file, blood_type) == 0) {
            total_quantity += quantity;
        }
    }

    fclose(file);
    return total_quantity;
}







void sang_rare(char nomFichier[], char sangRare[]) {
    const char *blood_types[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    int min_quantity = -1;
    char min_blood_type[100] = "";

    for (int i = 0; i < 8; i++) {
        int quantity = calculate_blood_quantity(nomFichier, blood_types[i]);
        if (quantity >= 0 && (min_quantity == -1 || quantity < min_quantity)) {
            min_quantity = quantity;
            strcpy(min_blood_type, blood_types[i]);
        }
    }

    strcpy(sangRare, min_blood_type);
}
