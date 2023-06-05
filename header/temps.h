#include <stdio.h>
#include <stdlib.h>
#include "../header/affichageSDL2.h"
#include "../header/define.h"

#include <unistd.h>

int globalMinutes;
int globalSecondes;


void* decompte(void* arg);
void AfficheChrono();