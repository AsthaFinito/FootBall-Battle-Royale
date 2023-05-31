#include <stdio.h>
#include <stdlib.h>
#include "../src/include/SDL2/SDL.h"
#include "../src/include/SDL2/SDL_image.h"
#include "../src/include/SDL2/SDL_ttf.h"
#include "../src/include/SDL2/SDL_mixer.h"
#include "../header/affichageSDL2.h"
#include "../header/define.h"

int TestSeparationFichier(SDL_Window *fenetre,SDL_Renderer *renduFenetre){
    printf("test \n");


    int RecupInitLib=InitialisationLibrairie();
    if(RecupInitLib!=0){
        printf("Erreur dans l'initialisation de la SDL2");
        return -1;
    }
    else{
        printf("Initialisation de la SDL2 ok \n");
    }

    
    RecupInitLib=AffichageMenu(fenetre,renduFenetre);
    

   
    return 0;
}

int InitialisationLibrairie(){
     if(TTF_Init()!=0){
        SDL_Log("Erreur: Initialisation TTF_Init > %s\n ",TTF_GetError());
        return EXIT_FAILURE;
    };
   

    if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
        SDL_Log("Erreur: Initialisation SDL_INIT_AUDIO > %s\n ",SDL_GetError());
        return EXIT_FAILURE;
    };
    
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)!=0){
        SDL_Log("Erreur: Initialisation audio mix_init > %s\n ",Mix_GetError());
        return EXIT_FAILURE;
    }

    
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        SDL_Log("Erreur: Initialisation SDL > %s\n ",SDL_GetError());
        return EXIT_FAILURE;
    };
    return 0;
}


void frame_rate(int fps,SDL_Renderer *renduFenetre)
{
    static Uint32 prev_ticks = 0;
    Uint32 ticks = SDL_GetTicks();
    Uint32 min_ticks = 1000 / fps;
    if (ticks - prev_ticks < min_ticks)
    {
        SDL_Delay(min_ticks - (ticks - prev_ticks));
        SDL_RenderPresent(renduFenetre);
    }
    prev_ticks = SDL_GetTicks();
}

int AffichageMenu(SDL_Window* fenetre,SDL_Renderer *renduFenetre){
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
    Mix_Music *MusiqueEntree;
    MusiqueEntree=Mix_LoadMUS("music/Menu.mp3");
     Mix_VolumeMusic(MIX_MAX_VOLUME / 8);
    if (!MusiqueEntree) {
        printf("Erreur lors du chargement de la musique: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }
    Mix_PlayMusic(MusiqueEntree,-1);


    SDL_Texture* textureTerrain=RenvoieTextureChargeImage("img/MenuTerrain.jpg",renduFenetre);
    int test=PlacementTextureCharge(textureTerrain,renduFenetre,0,0,WIDTH_FENETRE,HEIGHT_FENETRE);


   
    SDL_Color CouleurEcriture = {192, 192, 192};
    SDL_Texture* texturePolice=RenvoieTextureChargeTTF("ttf/MenuFont.ttf",renduFenetre,CouleurEcriture,75,"Projet Technique");

    int textureLargeur, textureHauteur;
    SDL_QueryTexture(texturePolice, NULL, NULL, &textureLargeur, &textureHauteur);

    test=PlacementTextureCharge(texturePolice,renduFenetre,(WIDTH_FENETRE/2)-(textureLargeur/2),150,textureLargeur,textureHauteur);
    SDL_RenderPresent(renduFenetre); //TODO remplacer les SDL_RenderPresent par la fonction frame_rate
     
    return 0;

}

SDL_Texture* RenvoieTextureChargeImage(char cheminAcces[50],SDL_Renderer *renduFenetre){
    SDL_Surface * ChargementImageSurface=IMG_Load(cheminAcces);
    if (ChargementImageSurface == NULL)
    {
       
        TTF_Quit();
        SDL_Quit();
        SDL_Log("Erreur: Création Image > %s\n ", SDL_GetError());
        return NULL;
    }
     SDL_Texture *textureImage=SDL_CreateTextureFromSurface(renduFenetre, ChargementImageSurface);
     return textureImage;
}

SDL_Texture* RenvoieTextureChargeTTF(char cheminAcces[50],SDL_Renderer *renduFenetre,SDL_Color CouleurEcriture,int tailleEcriture,char TexteAAfficher[100]){
    TTF_Font *TestNouvellePartie = TTF_OpenFont(cheminAcces, tailleEcriture);
    SDL_Surface *EcritureNouvellePartie = TTF_RenderText_Solid(TestNouvellePartie, TexteAAfficher, CouleurEcriture);
    if (EcritureNouvellePartie == NULL)
    {
       
        TTF_Quit();
        SDL_Quit();
        SDL_Log("Erreur: Création Image > %s\n ", SDL_GetError());
        return NULL;
    }
     SDL_Texture *textureTTF=SDL_CreateTextureFromSurface(renduFenetre, EcritureNouvellePartie);
     return textureTTF;
}

int PlacementTextureCharge(SDL_Texture* texture,SDL_Renderer *renduFenetre,int x, int y, int w,int h){
    SDL_Rect vecteurPosition;
    vecteurPosition.w=w;
    vecteurPosition.h=h;
    vecteurPosition.x=x;
    vecteurPosition.y=y;
    SDL_RenderCopy(renduFenetre, texture, NULL, &vecteurPosition);
    return 0;
   
}