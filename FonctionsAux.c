#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FonctionsAux.h"

// ---------------------------
// Fonctions auxiliaires
// ---------------------------

// Convertit une heure "HH:MM" en minutes totales
int heureEnMinutes(char heure[6]) {
    int h, m;
    sscanf(heure, "%d:%d", &h, &m);
    return h*60 + m;
}

// Vérifie si deux créneaux horaires se chevauchent
int chevauche(char debut1[6], char fin1[6], char debut2[6], char fin2[6]) {
    int d1 = heureEnMinutes(debut1);
    int f1 = heureEnMinutes(fin1);
    int d2 = heureEnMinutes(debut2);
    int f2 = heureEnMinutes(fin2);
    return (d1 < f2) && (d2 < f1);
}

// Calcule le tarif d'une réservation
float calculTarif(Salle salle, char debut[6], char fin[6]) {
    int minutes = heureEnMinutes(fin) - heureEnMinutes(debut);
    return (minutes / 60.0f) * salle.tarif_horaire;
}

// Vérifie si une salle est disponible pour une date et un créneau
int salleDisponible(Salle salle, char date[11], char debut[6], char fin[6]) {
    for(int i=0; i<nb_reservations; i++) {
        if(strcmp(reservations[i].salle.nom, salle.nom)==0 &&
           strcmp(reservations[i].date, date)==0 &&
           (strcmp(reservations[i].statut, "confirmee")==0 ||
           strcmp(reservations[i].statut, "modifiee")==0) &&
           chevauche(reservations[i].heure_debut, reservations[i].heure_fin, debut, fin)) {
            return 0;
        }
    }
    return 1;
}