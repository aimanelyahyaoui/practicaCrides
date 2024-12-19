#include <fcntl.h> // Inclou la llibreria necessària per a les operacions amb fitxers, com ara obrir i crear fitxers.
#include <unistd.h> // Inclou la llibreria necessària per a les operacions de lectura i escriptura en fitxers o dispositius.
#include <stdio.h> // Inclou funcions per mostrar missatges d'error i altres operacions d'E/S.

int main(int argc, char *argv[]) {

    if (argc < 2) { // Comprova si l'usuari ha passat almenys un argument (el nom del fitxer).
        perror("Error, falten arguments"); // Mostra un missatge d'error si no hi ha prou arguments.
        return -1; // Finalitza el programa amb un codi d'error.
    }

    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644); // Obre el fitxer en mode escriptura, creant-lo si no existeix i truncant-lo si ja existeix.
    if (fd == -1) { // Comprova si hi ha hagut un error en obrir o crear el fitxer.
        perror("No s'ha pogut crear el fitxer"); // Mostra un missatge d'error si no es pot obrir el fitxer.
        return -1; // Finalitza el programa amb un codi d'error.
    }

    char caracter; // Variable per emmagatzemar cada caràcter llegit.
    ssize_t bytesLlegits; // Variable per emmagatzemar el nombre de bytes llegits.

    while ((bytesLlegits = read(STDIN_FILENO, &caracter, 1)) != 0) { // Llegeix caràcter per caràcter des de l'entrada estàndard fins que no hi hagi més dades.
        if (bytesLlegits == -1 || write(STDOUT_FILENO, &caracter, 1) == -1 || write(fd, &caracter, 1) == -1) { // Gestiona errors durant la lectura o escriptura.
            perror("Error durant l'escriptura"); // Mostra un missatge d'error si hi ha problemes en l'escriptura.
            close(fd); // Tanca el fitxer.
            return -1; // Finalitza el programa amb un codi d'error.
        }
    }

    if (bytesLlegits == -1) { // Comprova si hi ha hagut un error durant la lectura.
        perror("Error durant la lectura"); // Mostra un missatge d'error en cas de problemes en la lectura.
        close(fd); // Tanca el fitxer abans de finalitzar per evitar pèrdua de recursos.
        return -1; // Finalitza el programa amb un codi d'error.
    }

    if (close(fd) == -1) { // Tanca el fitxer i comprova si hi ha hagut errors durant aquesta operació.
        perror("Error en tancar el fitxer"); // Mostra un missatge d'error si el fitxer no es pot tancar correctament.
        return -1; // Finalitza el programa amb un codi d'error.
    }

    return 0; // Finalitza el programa correctament.
}


#Segon programa:


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_MIDA 1024

int main(int argc, char *argv[]) {
    int fd, fd2;

    if (argc < 3) {
        perror("No hi ha prous arxius");
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error intentant obrir el primer arxiu");
        return -1;
    }

    fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1) {
        perror("Error intentant obrir el segon arxiu");
        close(fd);
        return -1;
    }

    int comptador_bytes = 1;
    int comptador_linies = 1;
    ssize_t bytes_llegits1, bytes_llegits2;
    char buf1[BUFFER_MIDA], buf2[BUFFER_MIDA];

    while (1) {
        bytes_llegits1 = read(fd, buf1, 1);
        bytes_llegits2 = read(fd2, buf2, 1);

        if (bytes_llegits1 == -1 || bytes_llegits2 == -1) {
            perror("Error llegint els fitxers");
            close(fd);
            close(fd2);
            return -1;
        }

        if (bytes_llegits1 == 0 && bytes_llegits2 == 0) {
            printf("Els arxius són iguals\n");
            close(fd);
            close(fd2);
            return 0;
        }

        if (bytes_llegits1 != bytes_llegits2 || buf1[0] != buf2[0]) {
            printf("Els arxius es diferèncien al byte %d de la línia %d\n",
                   comptador_bytes, comptador_linies);
            close(fd);
            close(fd2);
            return 0;
        }

        if (buf1[0] == '\n') {
            comptador_linies++;
        }

        comptador_bytes++;
    }

    close(fd);
    close(fd2);
    return 0;
}
