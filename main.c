#include <stdio.h>
#include <stdlib.h>
#include "header/affichageSDL2.h"
#include "header/define.h"



int main(int argc, char *argv[]) {
    printf("Compilation ok \n");
    SDL_Window *fenetre=NULL;
    SDL_Renderer *renduFenetre=NULL;
    fenetre=SDL_CreateWindow("Battle Royale Football",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH_FENETRE,HEIGHT_FENETRE,0);
    renduFenetre=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_SOFTWARE);
    TestSeparationFichier(fenetre,renduFenetre);
    SDL_bool programmeEnCours = SDL_TRUE;
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
                    }
                    break;
            }
        }
    }
    return 0;
}
