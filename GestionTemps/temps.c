#include "../header/affichageSDL2.h"
#include "../header/define.h"
#include "../header/joueur.h"
#include "../header/temps.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



#include <stdbool.h>

bool decompteActif = false; // Variable pour contrôler l'état du décompte

void* decompte(void* arg) {
    int* minutes_ptr = (int*)arg;
    int minutes = *minutes_ptr;
    int secondes = 0;
    
    while (minutes > 0 || secondes > 0) {
        globalMinutes = minutes;
        globalSecondes = secondes;
        printf("%d:%02d restantes\n", minutes, secondes);
        sleep(1); // Attendre une seconde
        secondes--;
        
        if (secondes < 0) {
            minutes--;
            secondes = 59;
        }
    }
    
    printf("Décompte terminé\n");
    
    // Remettre l'état du décompte à false
    decompteActif = false;
    
    return NULL;
}

void AfficheChrono(int minutes, SDL_Renderer* renduFenetre) {
    if (decompteActif) {
        printf("Le décompte est déjà en cours\n");
        return;
    }

    decompteActif = true;

    // Allocation dynamique d'un nouvel espace mémoire pour chaque thread
    int* minutes_ptr = (int*)malloc(sizeof(int));
    *minutes_ptr = minutes;

    pthread_t thread_decompte;
    int code_retour;

    code_retour = pthread_create(&thread_decompte, NULL, decompte, minutes_ptr);
    if (code_retour != 0) {
        printf("Erreur lors de la création du thread de décompte : %d\n", code_retour);
        SDL_Quit();
        free(minutes_ptr); // Libération de la mémoire allouée dynamiquement
        return;
    }
}

