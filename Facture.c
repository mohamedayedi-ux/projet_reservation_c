#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "Facture.h"


void genererFacture(Reservation res) {
    char nom_fichier[100];
    sprintf(nom_fichier, "Facture_%d.txt", res.id);   // unique grâce à l'id
    FILE *fp = fopen(nom_fichier, "w"); // "w" = nouveau fichier
    if(fp){
        int duree = heureEnMinutes(res.heure_fin) - heureEnMinutes(res.heure_debut);

        fprintf(fp,
            "===== FACTURE =====\n"
            "Client : %s\n"
            "Salle : %s\n"
            "Date : %s\n"
            "Heure : %s-%s\n"
            "Duree : %d h %d min\n"
            "Montant : %.2f TND\n",
            res.nom_client,
            res.salle.nom,
            res.date,
            res.heure_debut,
            res.heure_fin,
            duree/60,
            duree%60,
            res.tarif
        );

        fclose(fp);
    }
}
