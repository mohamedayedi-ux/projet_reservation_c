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
// Recherche d'une salle
// ---------------------------
Salle* trouverSalle(char nom_salle[]) {
    for(int i=0; i<nb_salles; i++){
        if(strcmp(nom_salle, salles[i].nom)==0)
            return &salles[i];
    }
    return NULL;
}

// ---------------------------
// Recommandation de salle
// ---------------------------
int recommanderSalles(int nb_personnes, char date[11], char debut[6], char fin[6]) {

    printf("\n--- Salles disponibles pour %d personnes le %s de %s a %s ---\n",
           nb_personnes, date, debut, fin);

    int trouve = 0;

    for (int i = 0; i < nb_salles; i++) {

        if (salles[i].capacite >= nb_personnes &&
            salleDisponible(salles[i], date, debut, fin)) {

            printf("%d. %s | Capacite: %d | Tarif: %.2f TND/h | Equipements: %s\n",
                   i + 1,
                   salles[i].nom,
                   salles[i].capacite,
                   salles[i].tarif_horaire,
                   salles[i].equipements);

            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucune salle disponible pour ce creneau.\n");
    }

    return trouve;
}