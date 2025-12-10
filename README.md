# 🏢 Gestion des Salles & Réservations – Projet en C

![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey)

Ce projet consiste à développer une application en C permettant de gérer des salles, leurs réservations, les conflits horaires, l’**estimation des coûts**, et la persistance des données via des fichiers.

---

## 📑 Sommaire
1. [Fonctionnalités](#-fonctionnalités)
2. [Structure du Projet](#-structure-du-projet)
3. [Compilation](#️-compilation)
4. [Exécution](#-exécution)
5. [Détails Techniques](#-détails-techniques)
6. [Auteurs](#-auteurs)
---

## 🚀 Fonctionnalités

### 🏢 Gestion des salles
- Ajouter une salle (nom, capacité, tarif horaire, équipements)
- Modifier ou supprimer une salle
- Lister toutes les salles
- Recommandation automatique selon la capacité

### 📅 Gestion des réservations
- Ajouter une réservation avec :
  - nom du client
  - nombre de personnes
  - date  
  - heure début
  - heure fin 
  - salle choisie  
    
- Détection des conflits de créneaux
- Modification et suppression de réservation
- Estimation automatique du coût de réservation

### 🔄 Sauvegarde des données
- Sauvegarde et lecture depuis fichiers texte/binaire :
  - Reservations.txt
  - Tarif.txt
  - Facture_(id_facture).txt

---

## 📂 Structure du Projet



Projet/
│── Main.c
│── Menu.c
│── Menu.h
│── GestionSalle.c
│── GestionSalle.h
│── Reservation.c
│── Reservation.h
│── FonctionsAux.c
│── FonctionsAux.h
│── Facture.c
│── Facture.h
│── Structures.c
│── Structures.h
│── Stats.c
│── Stats.h
│── data/
│ ├── Tarif.txt
│ ├── Reservations.txt
│ ├── Facture_(nom facture).txt
│── README.md

---

## 🖥️⚙️ Compilation

 Pour la compilation.txt
 ---
 gcc main.c Menu.c Facture.c FonctionsAux.c GestionSalle.c Reservation.c Stats.c -o Systeme_de_Gestion_de_Reservations.exe
 Systeme_de_Gestion_de_Reservations.exe
 ---

## ▶️ Exécution

 Systeme_de_Gestion_de_Reservations.exe

 ---

## 🔍 Détails techniques

🧱 1. Modèle de Données (Structures C)

Les structures principales sont définies dans Structures.h :

Structure Salle :

typedef struct {
    char nom[50];
    int capacite;
    float tarif_horaire;
    char equipements[200];
} Salle;

Structure Reservation : 

typedef struct {
    int id;
    char nom_client[50];
    Salle salle;
    char date[11];
    char heure_debut[6];
    char heure_fin[6];
    int nombre_personnes;
    float tarif;
    char statut[20];
} Reservation;


Les salles et réservations sont stockées dans des tableaux globaux définis dans main.c, limités par :
MAX_SALLES et MAX_RES.

🏢 2. Gestion des Salles & Persistance
✔ Ajout de salle

void ajouterSalle(char nom[], int capacite, float tarif, char equipements[]);

✔ Affichage

void afficherSalles();

✔ Recherche

Salle* trouverSalle(char nom_salle[]);

✔ Sauvegarde des tarifs

Un fichier Tarif.txt est géré par creerFichierTarif() pour conserver les tarifs des salles.

⏱️ 3. Gestion des Horaires & Détection des Chevauchements
a) Conversion des heures

int heureEnMinutes(char heure[6]);
Convertit "HH:MM" → minutes depuis minuit.

b) Vérification du chevauchement

int chevauche(char debut1[6], char fin1[6], char debut2[6], char fin2[6]);

Retourne 1 si les créneaux s’intersectent :

(d1 < f2) && (d2 < f1)

c) Vérification de la disponibilité de la salle

int salleDisponible(Salle salle, char date[11], char debut[6], char fin[6]);

Une salle est considérée disponible si aucune réservation confirmée/modifiée ne chevauche le créneau demandé.

💰 4. Calcul Automatique du Tarif

Tarif calculé par :
float calculTarif(Salle salle, char debut[6], char fin[6]);

Formule :
Tarif_Total = ((heure_fin - heure_debut) / 60) × tarif_horaire

Contraintes horaires :

Début ≥ 08:00

Fin ≤ 23:59

Fin > début

📝 5. Système de Réservation
Fonction principale :

int ajouterReservation(int id, char nom_client[], char nom_salle[], char date[11], char debut[6], char fin[6], int nb_personnes);

Vérifications effectuées :

Salle existante

Capacité suffisante

Absence de chevauchement

Horaire valide

Tarif calculé automatiquement

Enregistrement dans les tableaux

Gestion complémentaire :

annulerModifierReservation();

supprimerReservation(int id);

trouverReservation(int id);

afficherReservations();

📄 6. Génération de Facture

void genererFacture(Reservation res);

La facture contient :

Client

Salle

Date

Heures

Durée

Tarif total

Statut

Chaque facture peut être sauvegardée dans un fichier dédié.

📊 7. Module Statistiques

Géré principalement par Stats.c :

statistiquesCompletes();

compterReservationsParMois(int mois, int annee);

afficherSallesPopulaires(int mois, int annee);

Les statistiques incluent :

Chiffre d’affaires par salle

Nombre de réservations par mois

Classement des salles les plus réservées

💾 8. Persistance des Données

Fonctions :

void sauvegarderReservations();
void chargerReservations();


Le fichier Reservations.txt contient toutes les réservations.
Le chargement est effectué au démarrage, et la sauvegarde après chaque modification.

📌 9. Tâches du Projet (Exigences Respectées)

✔ Tâche 1 : Modèle de données

Structures Salle et Reservation complètes

Champs obligatoires respectés

✔ Tâche 2 : Système de réservation

Vérification disponibilité

Capacité de salle

Chevauchement empêché

Tarif automatique

Statut (confirmée, modifiée, annulée)

✔ Tâche 3 : Gestion des tarifs

Tarif par salle

Calcul automatique

Persistance dans Tarif.txt

✔ Tâche 4 : Factures

Générées avec genererFacture()

Format standard

Contenu : client, salle, date, durée, montant

✔ Tâche 5 : Statistiques

Chiffre d’affaires

Réservation par mois

Salles les plus populaires

✔ Tâche 6 : Persistance

Sauvegarde des réservations

Chargement automatique

Mise à jour après chaque modification

⭐ 10. Tâches Supplémentaires Réalisées (en plus du cahier des charges)

Voici ce que ton projet fait au-delà des exigences initiales :
✅ Estimation automatique du coût de réservation

→ Estime automatiquement le cout.

✅ Recommandation intelligente des salles

recommanderSalles(nb_personnes, date, debut, fin);
→ Propose automatiquement les salles disponibles et adaptées.

✅ Nettoyage et validation de la saisie

nettoyerChaine()

lireHeure()

lireDate()

→ Évite les erreurs de saisie utilisateur.

✅ Menu interactif complet

menu()
→ Interface claire et structurée.

✅ Gestion des statuts avancés

Réservation confirmée

Réservation modifiée

Réservation annulée

✅ Chargement automatique au démarrage

→ Améliore la persistance et l'expérience utilisateur.

✅ Sauvegarde automatique après chaque opération

→ Sécurise les données utilisateur.

 ---


## 💡 Auteurs

- Yasmine TRIKI
- Mohamed AYEDI
- Mohamed Louai DARGUECH
