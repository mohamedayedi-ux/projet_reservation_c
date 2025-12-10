#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GestionSalle.h"


// ---------------------------
// Gestion des salles
// ---------------------------
//ajourer les salles dans un fichier tarif.txt
void creerFichierTarif() {
    FILE *f = fopen("Tarif.txt", "w");
    if(f == NULL) {
        printf("Erreur lors de la creation du fichier Tarif.txt\n");
        return;
    }
    for(int i=0; i<nb_salles; i++) {
        fprintf(f, "%s | Capacite: %d | Tarif: %.2f TND/h | Equipements: %s\n",salles[i].nom, salles[i].capacite, salles[i].tarif_horaire, salles[i].equipements);
    }
    fclose(f);
}
void ajouterSalle(char nom[], int capacite, float tarif, char equipements[]) {
    if(nb_salles >= MAX_SALLES) return;
    strcpy(salles[nb_salles].nom, nom);
    salles[nb_salles].capacite = capacite;
    salles[nb_salles].tarif_horaire = tarif;
    strcpy(salles[nb_salles].equipements, equipements);
    nb_salles++;
    creerFichierTarif();
}

void afficherSalles() {
    printf("\n--- Liste des salles ---\n");
    for(int i=0;i<nb_salles;i++){
        printf("%d. %s | Capacite: %d | Tarif: %.2f TND/h | Equipements: %s\n",
               i+1, salles[i].nom, salles[i].capacite, salles[i].tarif_horaire, salles[i].equipements);
    }
}

// ---------------------------
// Lecture sécurisée de la date et de l'heure
// ---------------------------
void lireDate(char date[11]) {
    char buffer[20];
    int j,m,a;
    do {
        printf("Date (JJ/MM/AAAA) : ");
        fgets(buffer,sizeof(buffer),stdin);
        if(sscanf(buffer,"%d/%d/%d",&j,&m,&a)==3 && j>=1 && j<=31 && m>=1 && m<=12 && a>=2023){
            sprintf(date,"%02d/%02d/%04d",j,m,a);
            break;
        } else {
            printf("Format invalide. Reessayez.\n");
        }
    } while(1);
}

void lireHeure(char heure[6], const char *message) {
    char buffer[20];
    int h,m;
    do {
        printf("%s (HH:MM) : ", message);
        fgets(buffer,sizeof(buffer),stdin);
        if(sscanf(buffer,"%d:%d",&h,&m)==2 && h>=0 && h<=23 && m>=0 && m<=59){
            sprintf(heure,"%02d:%02d",h,m);
            break;
        } else {
            printf("Format invalide. Reessayez.\n");
        }
    } while(1);
}


// ---------------------------
// Nettoyage des chaînes
// ---------------------------
void nettoyerChaine(char *str) {
    for(int i=0; str[i]!='\0'; i++){
        if(str[i]=='\n'){ str[i]='\0'; break; }
    }
}

// ---------------------------
// Recherche d'une salle
// ---------------------------
Salle* trouverSalle(char nom_salle[]) {
    for(int i=0; i<nb_salles; i++){
        if(strcmp(nom_salle, salles[i].nom)==0)
            return &salles[i];
    }
    return NULL;
}