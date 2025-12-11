#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Reservation.h"

// ---------------------------
// Ajouter une réservation
// ---------------------------
int ajouterReservation(int id, char nom_client[], char nom_salle[], char date[11],char debut[6], char fin[6], int nb_personnes) {

    if(nb_reservations >= MAX_RES) return 0;

    Salle *salle = trouverSalle(nom_salle);
    if(salle == NULL){ printf("Salle introuvable.\n"); return 0;}
    if(nb_personnes > salle->capacite){ printf("Salle trop petite.\n"); return 0;}
    if(!salleDisponible(*salle,date,debut,fin)){ printf("Salle non disponible.\n"); return 0;}

    Reservation res;
    res.id = id;
    strcpy(res.nom_client, nom_client);
    res.salle = *salle;
    strcpy(res.date, date);
    strcpy(res.heure_debut, debut);
    strcpy(res.heure_fin, fin);
    res.nombre_personnes = nb_personnes;
    res.tarif = calculTarif(*salle,debut,fin);
    strcpy(res.statut, "confirmee");

    reservations[nb_reservations++] = res;
    genererFacture(res);
    sauvegarderReservations();
    return 1;
}
// ---------------------------
// Annulation ou modification
// ---------------------------
void annulerModifierReservation() {
    if (nb_reservations == 0) {
        printf("Aucune reservation.\n");
        return;
    }

    int id;
    char buffer[50];
    printf("Entrez l'ID de la reservation : ");
    scanf("%d", &id);
    getchar(); // consommer '\n'

    int trouve = 0;
    for (int i = 0; i < nb_reservations; i++) {
        if (reservations[i].id == id) {
            trouve = 1;

            printf("Reservation trouvee : %s dans %s le %s de %s a %s\n",
                   reservations[i].nom_client,
                   reservations[i].salle.nom,
                   reservations[i].date,
                   reservations[i].heure_debut,
                   reservations[i].heure_fin);

            printf("1) Annuler\n2) Modifier\nVotre choix : ");
            int choix;
            scanf("%d", &choix); getchar();

            if (choix == 1) {
                // Supprimer la réservation du tableau
                for (int j = i; j < nb_reservations - 1; j++) {
                    reservations[j] = reservations[j + 1];
                }
                nb_reservations--;
                printf("Reservation annulee.\n");
                sauvegarderReservations();
                //Supprimer la facture
                char nom_fichier[100];
                sprintf(nom_fichier, "Facture_%d.txt", reservations[i].id);
                if (remove(nom_fichier) == 0) {
                    printf("Facture supprimee avec succes.\n");
                } else {
                    printf("Aucune facture a supprimer.\n");
                }
            } 
            else if (choix == 2) {
                printf("Modification de la reservation.\n");

                char date[11], debut[6], fin[6], nom_salle[50];
                int nb_personnes, extra;

                // Lire nombre de personnes entier positif
                while (1) {
                    printf("Nombre de personnes : ");
                    fgets(buffer, sizeof(buffer), stdin);
                    if (sscanf(buffer, "%d %c", &nb_personnes, &extra) == 1 && nb_personnes > 0)
                        break;
                    printf("Erreur : entrez un nombre entier positif.\n");
                }

                // Lire date et heures
                lireDate(date);

                lireHeure(debut, "Heure debut");
                while (heureEnMinutes(debut) < 480 || heureEnMinutes(debut) > 1439) {
                    printf("Erreur : l'heure de debut doit etre entre 08:00 et 23:59.\n");
                    lireHeure(debut, "Heure debut");
                }

                lireHeure(fin, "Heure fin");
                while (heureEnMinutes(fin) < 480 || heureEnMinutes(fin) > 1439 || heureEnMinutes(fin) <= heureEnMinutes(debut)) {
                    printf("Erreur : l'heure de fin doit etre entre 08:00 et 23:59 et apres l'heure de debut.\n");
                    lireHeure(fin, "Heure fin");
                }
                int x;
                // Afficher les salles disponibles
                x=recommanderSalles(nb_personnes, date, debut, fin);
                //retour au menu si aucune salle disponible
                if (x == 0) {
                    continue; // Retour au menu principal
                }
                printf("Choisir la salle (nom) : ");
                fgets(nom_salle, sizeof(nom_salle), stdin);
                nettoyerChaine(nom_salle);
                Salle *salle = trouverSalle(nom_salle);
                if (!salle) {
                    printf("Salle non trouvee.\n");
                    return;
                }
                
                int minutes = heureEnMinutes(fin) - heureEnMinutes(debut);
                float tarif = (minutes / 60.0f) * salle->tarif_horaire;
                printf("Estimation : %s | Date : %s | Heure : %s-%s | Nombre : %d | Duree : %d h %d min | Cout estime : %.2f TND\n",salle->nom, date, debut, fin, nb_personnes, minutes / 60, minutes % 60, tarif);
                printf("1) Reserver\n2) Retour au menu\nVotre choix : ");
                fgets(buffer, sizeof(buffer), stdin);
                int choix2; sscanf(buffer, "%d", &choix2);
                if (choix2 == 1) {
                // Mettre à jour la réservation
                strcpy(reservations[i].date, date);
                strcpy(reservations[i].heure_debut, debut);
                strcpy(reservations[i].heure_fin, fin);
                strcpy(reservations[i].salle.nom, salle->nom);
                reservations[i].nombre_personnes = nb_personnes;
                reservations[i].tarif = tarif;
                strcpy(reservations[i].statut, "modifiee");
                printf("Reservation modifiee avec succes.\n");
                genererFacture(reservations[i]);
                sauvegarderReservations();
                    }
                else {
                    printf("Retour au menu principal.\n");
                    return;
                }
            } 
            else {
                printf("Choix invalide.\n");
            }

            break;
        }
    }

    if (!trouve) {
        printf("Reservation non trouvee.\n");
    }
}

// Sauvegarder toutes les réservations dans un fichier Reservations.txt
void sauvegarderReservations() {
    FILE *f = fopen("Reservations.txt", "w");
    if(f == NULL) {
        printf("Erreur lors de la sauvegarde des reservations.\n");
        return;
    }
    for(int i=0; i<nb_reservations; i++) {
       fprintf(f,
        "ID: %d | Client: %s | Salle: %s | Date: %s | Début: %s | Fin: %s | Personnes: %d | Tarif: %.2f TND | Statut: %s\n",
        reservations[i].id,
        reservations[i].nom_client,
        reservations[i].salle.nom,
        reservations[i].date,
        reservations[i].heure_debut,
        reservations[i].heure_fin,
        reservations[i].nombre_personnes,
        reservations[i].tarif,
        reservations[i].statut
);
    }
    fclose(f);
}


// Charger les réservations depuis le fichier Reservations.txt
void chargerReservations() {
    FILE *f = fopen("Reservations.txt", "r");
    if(f == NULL) {
        printf("Aucune reservation a charger.\n");
        return;
    }

    nb_reservations = 0;

    while(nb_reservations < MAX_RES) {

        Reservation res;

        int lus = fscanf(f,
            "ID: %d | Client: %49[^|] | Salle: %49[^|] | Date: %10[^|] | Début: %5[^|] | Fin: %5[^|] | Personnes: %d | Tarif: %f TND | Statut: %19[^\n]\n",
            &res.id,
            res.nom_client,
            res.salle.nom,
            res.date,
            res.heure_debut,
            res.heure_fin,
            &res.nombre_personnes,
            &res.tarif,
            res.statut
        );

        if(lus != 9)
            break;

        //  Nettoyage nom salle : enlever espaces début/fin
        char *n = res.salle.nom;

        // retirer espaces au début
        while (*n == ' ') n++;

        // copier la chaîne nettoyée
        strcpy(res.salle.nom, n);

        // retirer espaces à la fin
        int len = strlen(res.salle.nom);
        while (len > 0 && res.salle.nom[len - 1] == ' ') {
            res.salle.nom[--len] = '\0';
        }

        // Ajouter la réservation dans le tableau
        reservations[nb_reservations++] = res;
    }

    fclose(f);
}

