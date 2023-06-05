#include <stdio.h>
#include <stdlib.h>
#include "../src/include/SDL2/SDL.h"
#include "../src/include/SDL2/SDL_image.h"
#include "../src/include/SDL2/SDL_ttf.h"
#include "../src/include/SDL2/SDL_mixer.h"
#include "../header/affichageSDL2.h"
#include "../header/define.h"
#include "../header/joueur.h"
#include "../header/arduinoLecture.h"
#include "../header/temps.h"

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

    
  //  RecupInitLib=AffichageMenu(fenetre,renduFenetre);
    

   
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


int frame_rate(int fps,SDL_Renderer *renduFenetre,int compteur,int etat)
{
    static Uint32 prev_ticks = 0;
    int valeur=0;
    Uint32 ticks = SDL_GetTicks();
    Uint32 min_ticks = 1000 / fps;
    if (ticks - prev_ticks < min_ticks)
    {
        SDL_Delay(min_ticks - (ticks - prev_ticks));
        RefreshEcran(renduFenetre,compteur,etat);
        if(etat==2){
            valeur=ReturnValeurLue();
        }
       // 
        //printf("%d \n",valeur);
        
    }
    prev_ticks = SDL_GetTicks();
    return valeur;
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

void RefreshEcran(SDL_Renderer *renduFenetre,int compteur,int etat){
    SDL_RenderClear(renduFenetre);
    if(etat==0 || etat==2){

        SDL_Texture* textureTerrain=RenvoieTextureChargeImage("img/MenuTerrain.jpg",renduFenetre);
        int test=PlacementTextureCharge(textureTerrain,renduFenetre,0,0,WIDTH_FENETRE,HEIGHT_FENETRE);
        
   

     
   
    SDL_Color CouleurEcriture2 = {192, 192, 192};
    SDL_Texture* texturePolice=RenvoieTextureChargeTTF("ttf/MenuFont.ttf",renduFenetre,CouleurEcriture2,75,"Projet Technique");

    int textureLargeur, textureHauteur;
    SDL_QueryTexture(texturePolice, NULL, NULL, &textureLargeur, &textureHauteur);

    test=PlacementTextureCharge(texturePolice,renduFenetre,(WIDTH_FENETRE/2)-(textureLargeur/2),150,textureLargeur,textureHauteur);

    if(etat==0){
       int distanceEntreRectangles = 100; // Distance entre les rectangles en pixels
        int distanceBordGauche = 100; // Distance entre le bord gauche de la fenêtre et le premier rectangle

        // Premier rectangle
        int x1 = WIDTH_FENETRE/2-250;
        DrawGrayBoutton(renduFenetre, x1, HEIGHT_FENETRE - 150, 100, 100);

        // Deuxième rectangle
        int x2 = WIDTH_FENETRE/2-50; // Ajout de la largeur du premier rectangle et de la distance entre les rectangles
        DrawGrayBoutton(renduFenetre, x2, HEIGHT_FENETRE - 150, 100, 100);

        // Troisième rectangle
        int x3 = x2 + 100 + distanceEntreRectangles; // Ajout de la largeur du deuxième rectangle et de la distance entre les rectangles
        DrawGrayBoutton(renduFenetre, x3, HEIGHT_FENETRE - 150, 100, 100);

        SDL_Texture* Icone1=RenvoieTextureChargeImage("img/MenuTerrain.jpg",renduFenetre);
         SDL_Texture* Icone2=RenvoieTextureChargeImage("img/MenuTerrain.jpg",renduFenetre);
          SDL_Texture* Icone3=RenvoieTextureChargeImage("img/MenuTerrain.jpg",renduFenetre);
        int test2=PlacementTextureCharge(textureTerrain,renduFenetre, WIDTH_FENETRE/2-250+((100-75)/2), HEIGHT_FENETRE - 150+((100-75)/2),75,75);
        test2=PlacementTextureCharge(textureTerrain,renduFenetre, WIDTH_FENETRE/2-50+((100-75)/2), HEIGHT_FENETRE - 150+((100-75)/2),75,75);
        test2=PlacementTextureCharge(textureTerrain,renduFenetre, x2 + 100 + distanceEntreRectangles+((100-75)/2), HEIGHT_FENETRE - 150+((100-75)/2),75,75);
        SDL_DestroyTexture(Icone1);
        SDL_DestroyTexture(Icone2);
        SDL_DestroyTexture(Icone3);
    }
    if(etat==2){
        char compteur2[10];
        sprintf(compteur2, "%d", compteur);
        SDL_Color CouleurEcriture={192,192,192};
        SDL_Texture *textureTTF=RenvoieTextureChargeTTF("ttf/MenuFont.ttf",renduFenetre,CouleurEcriture,75,compteur2);
        if(textureTTF==NULL){
            printf("Erreur ttf \n");
         }
        test=PlacementTextureCharge(textureTTF,renduFenetre,WIDTH_FENETRE/2-175,HEIGHT_FENETRE-250,100,100);
        sprintf(compteur2,"%d",globalSecondes);
        SDL_Texture *textureTTF2=RenvoieTextureChargeTTF("ttf/MenuFont.ttf",renduFenetre,CouleurEcriture,75,compteur2);
         test=PlacementTextureCharge(textureTTF2,renduFenetre,WIDTH_FENETRE/2+50,HEIGHT_FENETRE/2-50,100,100);

          sprintf(compteur2, "%d", globalMinutes);
        SDL_Texture *textureTTF3=RenvoieTextureChargeTTF("ttf/MenuFont.ttf",renduFenetre,CouleurEcriture,75,compteur2);
         test=PlacementTextureCharge(textureTTF3,renduFenetre,WIDTH_FENETRE/2-100,HEIGHT_FENETRE/2-50,100,100);
        SDL_DestroyTexture(textureTTF2);
        SDL_DestroyTexture(textureTTF);
        SDL_DestroyTexture(textureTTF3);
              
    }
    SDL_DestroyTexture(textureTerrain);
    SDL_DestroyTexture(texturePolice);
    

    //SDL_Texture* textureMode1=RenvoieTextureChargeImage("img/mode1.jpg",renduFenetre);
    //test=PlacementTextureCharge(textureMode1,renduFenetre,(WIDTH_FENETRE/2)-(textureLargeur/2),HEIGHT_FENETRE-100,100,100);

    }
    else if(etat==1){
        SDL_Texture* textureTerrain=RenvoieTextureChargeImage("img/MenuTerrain.jpg",renduFenetre);
        int test=PlacementTextureCharge(textureTerrain,renduFenetre,0,0,WIDTH_FENETRE,HEIGHT_FENETRE);
        SDL_Color CouleurEcriture2 = {192, 192, 192};
        SDL_Texture* texturePolice=RenvoieTextureChargeTTF("ttf/MenuFont.ttf",renduFenetre,CouleurEcriture2,75,"Choix des equipes");

        int textureLargeur, textureHauteur;
        SDL_QueryTexture(texturePolice, NULL, NULL, &textureLargeur, &textureHauteur);

        test=PlacementTextureCharge(texturePolice,renduFenetre,(WIDTH_FENETRE/2)-(textureLargeur/2),150,textureLargeur,textureHauteur);

         char compteur2[10];
        sprintf(compteur2, "%d", NombreEquipe1);
        SDL_Color CouleurEcriture={192,192,192};
        SDL_Texture *textureTTF=RenvoieTextureChargeTTF("ttf/MenuFont.ttf",renduFenetre,CouleurEcriture,75,compteur2);
        if(textureTTF==NULL){
            printf("Erreur ttf \n");
         }
        test=PlacementTextureCharge(textureTTF,renduFenetre,WIDTH_FENETRE/2-175,HEIGHT_FENETRE-250,100,100);      
        sprintf(compteur2, "%d", NombreEquipe2);
       
        SDL_Texture *textureTTF2=RenvoieTextureChargeTTF("ttf/MenuFont.ttf",renduFenetre,CouleurEcriture,75,compteur2);
        if(textureTTF==NULL){
            printf("Erreur ttf \n");
         }
        test=PlacementTextureCharge(textureTTF2,renduFenetre,WIDTH_FENETRE/2+75,HEIGHT_FENETRE-250,100,100);

         SDL_Texture* Icone1=RenvoieTextureChargeImage("img/flecheUP.jpg",renduFenetre);
         test=PlacementTextureCharge(Icone1,renduFenetre,WIDTH_FENETRE/2+75,HEIGHT_FENETRE-350,100,100);
         test=PlacementTextureCharge(Icone1,renduFenetre,WIDTH_FENETRE/2-175,HEIGHT_FENETRE-350,100,100);
         SDL_Texture* Icone2=RenvoieTextureChargeImage("img/flecheDOWN.png",renduFenetre);
          test=PlacementTextureCharge(Icone2,renduFenetre,WIDTH_FENETRE/2+75,HEIGHT_FENETRE-150,100,100);
         test=PlacementTextureCharge(Icone2,renduFenetre,WIDTH_FENETRE/2-175,HEIGHT_FENETRE-150,100,100);
          SDL_Texture* Icone3=RenvoieTextureChargeImage("img/bouttonNext.png",renduFenetre);
          test=PlacementTextureCharge(Icone3,renduFenetre,WIDTH_FENETRE-175,HEIGHT_FENETRE-150,100,100);
         SDL_DestroyTexture(textureTerrain);
        SDL_DestroyTexture(texturePolice);
        SDL_DestroyTexture(textureTTF);
        SDL_DestroyTexture(textureTTF2);
        SDL_DestroyTexture(Icone1);
        SDL_DestroyTexture(Icone2);
        SDL_DestroyTexture(Icone3);

    }
   
    
    SDL_RenderPresent(renduFenetre);
}


void ChargementTexture(SDL_Renderer *renduFenetre){

    //Chargement du terrain
     SDL_Texture* textureTerrain=RenvoieTextureChargeImage("../img/MenuTerrain.jpg",renduFenetre);
    printf("Chargement MenuTerrain?");

    //Chargement ecriture projetTechnique
    SDL_Color CouleurEcriture2 = {192, 192, 192};
    SDL_Texture* texturePolice=RenvoieTextureChargeTTF("ttf/MenuFont.ttf",renduFenetre,CouleurEcriture2,75,"Projet Technique");
    printf("Fin chargement texture \n");


    }


void DrawGrayBoutton(SDL_Renderer* renderer, int x, int y, int width, int height) {
    // Création d'une surface SDL pour représenter le rectangle
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    
    // Remplissage de la surface avec une couleur grise (RGB : 128, 128, 128)
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 128, 128, 128));
    
    // Conversion de la surface en une texture SDL
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    // Dessin de la texture sur le rendu
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
    // Libération de la mémoire
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}