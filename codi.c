#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        perror("Error, falten arguments");
        return -1;
    }

    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("No s'ha pogut crear el fitxer");
        return -1;
    }

    char caracter;
    ssize_t bytesLlegits;

    while ((bytesLlegits = read(STDIN_FILENO, &caracter, 1)) != 0) {
        if (bytesLlegits == -1 || write(STDOUT_FILENO, &caracter, 1) == -1 || write(fd, &caracter, 1) == -1) {
            perror("Error durant l'escriptura");
            close(fd);
            return -1;
        }
    }

    if (bytesLlegits == -1) {
        perror("Error durant la lectura");
        close(fd);
        return -1;
    }

    if (close(fd) == -1) {
        perror("Error en tancar el fitxer");
        return -1;
    }

    return 0;
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
