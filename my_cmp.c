// Segon programa:

#include <fcntl.h> // Inclou la llibreria necessària per a les operacions amb fitxers.
#include <unistd.h> // Inclou la llibreria necessària per a les operacions de lectura i escriptura.
#include <stdio.h> // Inclou funcions per mostrar missatges d'error i altres operacions d'E/S.
#include <stdlib.h> // Inclou funcions d'allocació de memòria i control del programa.

#define BUFFER_MIDA 1024 // Defineix la mida del buffer utilitzat per a la lectura.

int main(int argc, char *argv[]) {
    int fd, fd2; // Descriptors de fitxer per als dos fitxers a comparar.

    if (argc < 3) { // Comprova que l'usuari ha passat els noms dels dos fitxers com a arguments.
        perror("No hi ha prous arxius"); // Mostra un missatge d'error si falten arguments.
        return -1; // Finalitza el programa amb un codi d'error.
    }

    fd = open(argv[1], O_RDONLY); // Obre el primer fitxer en mode lectura.
    if (fd == -1) { // Comprova si hi ha hagut un error en obrir el primer fitxer.
        perror("Error intentant obrir el primer arxiu"); // Mostra un missatge d'error si no es pot obrir.
        return -1; // Finalitza el programa amb un codi d'error.
    }

    fd2 = open(argv[2], O_RDONLY); // Obre el segon fitxer en mode lectura.
    if (fd2 == -1) { // Comprova si hi ha hagut un error en obrir el segon fitxer.
        perror("Error intentant obrir el segon arxiu"); // Mostra un missatge d'error si no es pot obrir.
        close(fd); // Tanca el primer fitxer abans de finalitzar per evitar fuites de recursos.
        return -1; // Finalitza el programa amb un codi d'error.
    }

    int comptador_bytes = 1; // Comptador per al nombre de bytes processats.
    int comptador_linies = 1; // Comptador per al nombre de línies processades.
    ssize_t bytes_llegits1, bytes_llegits2; // Variables per emmagatzemar els bytes llegits de cada fitxer.
    char buf1[BUFFER_MIDA], buf2[BUFFER_MIDA]; // Buffers per emmagatzemar dades llegides de cada fitxer.

    while (1) { // Bucle infinit fins que es determini si els fitxers són iguals o diferents.
        bytes_llegits1 = read(fd, buf1, 1); // Llegeix un byte del primer fitxer.
        bytes_llegits2 = read(fd2, buf2, 1); // Llegeix un byte del segon fitxer.

        if (bytes_llegits1 == -1 || bytes_llegits2 == -1) { // Comprova si hi ha hagut un error durant la lectura.
            perror("Error llegint els fitxers"); // Mostra un missatge d'error si hi ha problemes en la lectura.
            close(fd); // Tanca el primer fitxer abans de finalitzar.
            close(fd2); // Tanca el segon fitxer abans de finalitzar.
            return -1; // Finalitza el programa amb un codi d'error.
        }

        if (bytes_llegits1 == 0 && bytes_llegits2 == 0) { // Comprova si s'ha arribat al final dels dos fitxers.
            printf("Els arxius són iguals\n"); // Mostra un missatge indicant que els fitxers són idèntics.
            close(fd); // Tanca el primer fitxer.
            close(fd2); // Tanca el segon fitxer.
            return 0; // Finalitza el programa correctament.
        }

        if (bytes_llegits1 != bytes_llegits2 || buf1[0] != buf2[0]) { // Comprova si hi ha una discrepància entre els fitxers.
            printf("Els arxius es diferèncien al byte %d de la línia %d\n",
                   comptador_bytes, comptador_linies); // Mostra la posició on els fitxers difereixen.
            close(fd); // Tanca el primer fitxer.
            close(fd2); // Tanca el segon fitxer.
            return 0; // Finalitza el programa correctament.
        }

        if (buf1[0] == '\n') { // Comprova si el byte actual és un salt de línia.
            comptador_linies++; // Incrementa el comptador de línies.
        }

        comptador_bytes++; // Incrementa el comptador de bytes.
    }

    close(fd); // Tanca el primer fitxer.
    close(fd2); // Tanca el segon fitxer.
    return 0; // Finalitza el programa correctament.
}
