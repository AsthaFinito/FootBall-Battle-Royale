#include <stdio.h>
#include <stdlib.h>
#include "../src/include/SDL2/SDL.h"
#include "../src/include/SDL2/SDL_image.h"
#include "../src/include/SDL2/SDL_ttf.h"
#include "../src/include/SDL2/SDL_mixer.h"

SDL_Texture* textureTerrain;
SDL_Texture* texturePolice;


int TestSeparationFichier(SDL_Window *fenetre,SDL_Renderer *renduFenetre);
int InitialisationLibrairie();
int AffichageMenu(SDL_Window* fenetre,SDL_Renderer *renduFenetre);
int frame_rate(int fps,SDL_Renderer *renduFenetre,int compteur,int etat);
SDL_Texture* RenvoieTextureChargeImage(char cheminAcces[50],SDL_Renderer *renduFenetre);
SDL_Texture* RenvoieTextureChargeTTF(char cheminAcces[50],SDL_Renderer *renduFenetre,SDL_Color CouleurEcriture,int tailleEcriture,char TexteAAfficher[100]);
int PlacementTextureCharge(SDL_Texture* texture,SDL_Renderer *renduFenetre,int x, int y, int w,int h);
void RefreshEcran(SDL_Renderer *renduFenetre,int compteur,int etat);

void ChargementTexture(SDL_Renderer *renduFenetre);
void DrawGrayBoutton(SDL_Renderer* renderer, int x, int y, int width, int height);