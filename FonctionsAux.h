#ifndef FONCTIONS_AUX_H
#define FONCTIONS_AUX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"  // <-- indispensable !

// Déclarer les variables définies dans main.c
extern Salle salles[MAX_SALLES];
extern int nb_salles;
extern Reservation reservations[MAX_RES];
extern int nb_reservations;

// ---------------------------
// Déclarations des fonctions
// ---------------------------

// Convertit une heure "HH:MM" en minutes totales
int heureEnMinutes(char heure[6]);

// Vérifie si deux créneaux horaires se chevauchent
int chevauche(char debut1[6], char fin1[6], char debut2[6], char fin2[6]);

// Calcule le tarif d'une réservation
float calculTarif(Salle salle, char debut[6], char fin[6]);

// Vérifie si une salle est disponible pour une date et un créneau
int salleDisponible(Salle salle, char date[11], char debut[6], char fin[6]);

#endif // FONCTIONS_AUX_H
