#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <fcntl.h>
#include <windows.h>
#include "../header/arduinoLecture.h"

int InitPort(){


    // Ouvrir le port série
    serial_port = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (serial_port == INVALID_HANDLE_VALUE) {
        printf("Erreur lors de l'ouverture du port série\n");
        return -1;
    }

    // Configurer les paramètres du port série
    memset(&dcbSerialParams, 0, sizeof(dcbSerialParams));
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(serial_port, &dcbSerialParams)) {
        printf("Erreur lors de la récupération des paramètres du port série\n");
        CloseHandle(serial_port);
        return -1;
    }

    dcbSerialParams.BaudRate = CBR_9600; // Vitesse de transmission (9600 bauds)
    dcbSerialParams.ByteSize = 8; // 8 bits de données
    dcbSerialParams.StopBits = ONESTOPBIT; // 1 bit d'arrêt
    dcbSerialParams.Parity = NOPARITY; // Pas de parité

    if (!SetCommState(serial_port, &dcbSerialParams)) {
        printf("Erreur lors de la configuration des paramètres du port série\n");
        CloseHandle(serial_port);
        return -1;
    }

   
    if (!SetCommTimeouts(serial_port, &timeouts)) {
        printf("Erreur lors de la configuration des délais d'attente du port série\n");
        CloseHandle(serial_port);
        return -1;
    }

    return 0;
    
}


int ReturnValeurLue(){
     if (ReadFile(serial_port, read_buf, sizeof(read_buf) - 1, &num_bytes, NULL)) {
            if (num_bytes > 0) {
                read_buf[num_bytes] = '\0'; // Ajoutez un caractère de fin de chaîne

                // Traitement de la valeur reçue depuis le port série
                int valeur = atoi(read_buf);
                printf("Valeur recue : %d\n", valeur);
                return valeur;
            }
        }
    return -1;
}
