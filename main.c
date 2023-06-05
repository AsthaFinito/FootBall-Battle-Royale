#include <stdio.h>
#include <stdlib.h>
#include "header/affichageSDL2.h"
#include "header/arduinoLecture.h"
#include "header/define.h"
#include "header/temps.h"
#include "header/joueur.h"
#include<unistd.h>
#include <fcntl.h>
#include <windows.h>

int etat=0;


int main(int argc, char *argv[]) {
    //InitPort();
    
    int compteur=0;
    char compteur2[10];
    NombreEquipe1=11;
    NombreEquipe2=11;
    printf("Compilation ok \n");
    SDL_Window *fenetre=NULL;
    SDL_Renderer *renduFenetre=NULL;
    
    fenetre=SDL_CreateWindow("Battle Royale Football",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH_FENETRE,HEIGHT_FENETRE,0);
    renduFenetre=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_SOFTWARE);
    TestSeparationFichier(fenetre,renduFenetre);
    SDL_bool programmeEnCours = SDL_TRUE;
   int mouseX =0;
   int mouseY=0;
   //ChargementTexture(renduFenetre);
   int test=AffichageMenu(fenetre,renduFenetre);
    while(programmeEnCours) {
        SDL_Event evenement;
       
        while (SDL_PollEvent(&evenement)) {
            
            switch (evenement.type) {
                case SDL_QUIT:
                    programmeEnCours = SDL_FALSE;
                    break;
                case SDL_KEYDOWN:
                    switch (evenement.key.keysym.sym) {
                        case SDLK_SPACE:
                            printf("Appuie touche Space \n");
                            programmeEnCours = SDL_FALSE;
                            break;
                        case SDLK_f:
                            compteur++;
                            printf("Appuie touche F %d \n",compteur);
                            break;
                       
                        case SDLK_z:
                            if(etat==1){
                                NombreEquipe1++;
                                printf("Valeur Equipe1 : %d",NombreEquipe1);
                            }
                            break;
                        case SDLK_s:
                            if(etat==1){
                                NombreEquipe1--;
                                printf("Valeur Equipe1 : %d",NombreEquipe1);
                            }
                            break;
                             
                        case SDLK_h:
                            etat=2;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                     mouseX = evenement.motion.x;
                     mouseY = evenement.motion.y;
                     if(mouseX>  WIDTH_FENETRE/2-250 && mouseX< WIDTH_FENETRE/2-150 && mouseY>HEIGHT_FENETRE-150 && mouseY<HEIGHT_FENETRE-50){
                        printf("Boutton 1 detec \n");
                        etat=1;
                     }
                    else if(etat==1 && mouseX> WIDTH_FENETRE/2+75 && mouseX<WIDTH_FENETRE/2+175 && mouseY>HEIGHT_FENETRE-350 && mouseY<HEIGHT_FENETRE-250){
                        NombreEquipe2++;
                        printf("Augmentation equipe \n");
                    }
                     else if(etat==1 && mouseX>WIDTH_FENETRE/2-175 && mouseX<WIDTH_FENETRE/2-75 && mouseY>HEIGHT_FENETRE-350 && mouseY<HEIGHT_FENETRE-250){
                        NombreEquipe1++;
                        printf("Augmentation equipe \n");
                    }
                     else if(etat==1 && mouseX>WIDTH_FENETRE/2-175 && mouseX<WIDTH_FENETRE/2-75 && mouseY>HEIGHT_FENETRE-150 && mouseY<HEIGHT_FENETRE-50){
                        NombreEquipe1--;
                        printf("Augmentation equipe \n");
                    }
                     else if(etat==1 && mouseX> WIDTH_FENETRE/2+75 && mouseX<WIDTH_FENETRE/2+175 && mouseY>HEIGHT_FENETRE-150 && mouseY<HEIGHT_FENETRE-50){
                        NombreEquipe2--;
                        printf("Augmentation equipe \n");
                    }
                    else if(etat==1 && mouseX>WIDTH_FENETRE-175 && mouseX<WIDTH_FENETRE-75 && mouseY>HEIGHT_FENETRE-150 && mouseY<HEIGHT_FENETRE-50){
                        etat=2;
                        AfficheChrono(45,renduFenetre);
                    }
                    //printf("Coo de la souris : %d %d  = %d\n",mouseX,mouseY,etat);
                    break;
            }
        }
         compteur+=frame_rate(24,renduFenetre,compteur,etat);
        
        
    }
    return 0;
}
