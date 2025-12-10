#ifndef GESTION_SALLE_H
#define GESTION_SALLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"  // Inclut les définitions de Salle et Reservation


extern Salle salles[MAX_SALLES];
extern int nb_salles;
// Déclarations des fonctions de gestion des salles
void ajouterSalle(char nom[], int capacite, float tarif, char equipements[]);
void afficherSalles();
Salle* trouverSalle(char nom_salle[]);

// Fonctions utilitaires pour la saisie et le nettoyage
void lireDate(char date[11]);
void lireHeure(char heure[6], const char *message);
void nettoyerChaine(char *str);

#endif // GESTION_SALLE_H
