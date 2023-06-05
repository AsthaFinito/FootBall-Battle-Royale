#include <stdio.h>
#include <stdlib.h>
#include "../header/affichageSDL2.h"
#include "../header/define.h"
#include "../header/joueur.h"
#include <unistd.h>


void initialiserJoueur(struct Joueur* joueur, int numero, int carton) {
    joueur->numero_joueur = numero;
    joueur->carton = carton;
}

void initialiserEquipe(struct Joueur equipe[], int taille) {
    for (int i = 0; i < taille; i++) {
        equipe[i].numero_joueur = i + 1;
        equipe[i].carton = 0;
    }
}


void ajouterCarton(struct Joueur equipe[], int taille, int numero_joueur, int valeur_carton) {
    for (int i = 0; i < taille; i++) {
        if (equipe[i].numero_joueur == numero_joueur) {
            equipe[i].carton += valeur_carton;
            if(equipe[i].carton==2){
                printf("Joueur X , tu sors car carton rouge \n"); //TODO , afficher cela en SDL
            }
            break;
        }
    }
}