#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stats.h"


// ---------------------------ju
// Affichage des statistiques
// ---------------------------
void statistiquesCompletes() {
    int choix;
    do {
        printf("\n=== MODULE STATISTIQUES ===\n");
        printf("1. Le chiffre d'affaires par salle\n");
        printf("2. Le nombre de reservations par mois\n");
        printf("3. La(s) salle(s) la(es) plus populaire(s)\n");
        printf("0. Retour au menu principal\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar(); // pour consommer le '\n' restant

        switch(choix) {
            case 1: { // Chiffre d'affaires par salle
                    printf("\n--- Chiffre d'affaires par salle ---\n");

                    for (int i = 0; i < nb_salles; i++) {

                    float chiffreAffaires = 0.0f;

                    for (int j = 0; j < nb_reservations; j++) {

                    // Vérifie si la réservation appartient à la salle i
                    if (strcmp(reservations[j].salle.nom, salles[i].nom) == 0) {
                        chiffreAffaires += reservations[j].tarif;
                    }
                    }

                    printf("Salle %s : %.2f TND\n", salles[i].nom, chiffreAffaires);
                    }

                    break;
                    }


            case 2: { // Nombre de réservations par mois
                int mois, annee;
                printf("Entrez le mois (1-12) : ");
                scanf("%d", &mois);
                printf("Entrez l'annee : ");
                scanf("%d", &annee);
                getchar();
                int nb = compterReservationsParMois(mois, annee);
                printf("Nombre de reservations confirmees pour %02d/%04d : %d\n", mois, annee, nb);
                break;
            }

            case 3: { // Salles les plus populaires
                int mois, annee;
                printf("Entrez le mois (1-12) : ");
                scanf("%d", &mois);
                printf("Entrez l'annee : ");
                scanf("%d", &annee);
                getchar();
                afficherSallesPopulaires(mois, annee);
                break;
            }

            case 0:
                printf("Retour au menu principal...\n");
                break;

            default:
                printf("Choix invalide !\n");
        }

    } while (choix != 0);
}


//Compter le nombre de réservations par mois
int compterReservationsParMois(int mois, int annee){
    int compteur=0;
    for(int i=0;i<nb_reservations;i++){
        int j,m,a;
        if(sscanf(reservations[i].date,"%d/%d/%d",&j,&m,&a)==3){
            if(m==mois && a==annee){
                compteur++;
            }
        }
    }
    return compteur;
}


//Afficher les salles les plus populaires
void afficherSallesPopulaires(int mois, int annee){
    printf("\n--- Salles les plus populaires pour %02d/%04d ---\n",mois,annee);
    int maxReservations=0;
    for(int i=0;i<nb_salles;i++){
        int compteur=0;
        for(int j=0;j<nb_reservations;j++){
            int j_date,m_date,a_date;
            if(sscanf(reservations[j].date,"%d/%d/%d",&j_date,&m_date,&a_date)==3){
                if(m_date==mois && a_date==annee && strcmp(reservations[j].salle.nom,salles[i].nom)==0){
                    compteur++;
                }
            }
        }
        if(compteur>maxReservations){
            maxReservations=compteur;
        }
    }
    if(maxReservations==0){
        printf("Aucune reservation pour ce mois.\n");
        return;
    }
    for(int i=0;i<nb_salles;i++){
        int compteur=0;
        for(int j=0;j<nb_reservations;j++){
            int j_date,m_date,a_date;
            if(sscanf(reservations[j].date,"%d/%d/%d",&j_date,&m_date,&a_date)==3){
                if(m_date==mois && a_date==annee && strcmp(reservations[j].salle.nom,salles[i].nom)==0){
                    compteur++;
                }
            }
        }
        if(compteur==maxReservations){
            printf("%s avec %d reservations\n",salles[i].nom,compteur);
        }
    }
}





