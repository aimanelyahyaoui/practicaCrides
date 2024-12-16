#include <fcntl.h>
#include <uistd.h>

int main(int argc, char *argv[]){

        if(argc<2); {
                perror("Error, falten arguments");
                return -1;
                }

        int fd = open (argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd == -1){
                perror("No s'ha pogut crear el fitxer");
                return -1;
        }

    char caracter;
    ssize_t bytesLlegits;

    while ((bytesLlegits = read(STDIN_FILENO, &caracter, 1)) != 0 && -1) {
        if ((write(STDOUT_FILENO, &caracter, 1) == -1) || write(fitxer, &caracter, 1) == -1) {
            perror("Error durant l'escriptura");
            close(fitxer);
            return -1;
        }
    }

    if (bytesLlegits == -1) {
        perror("Error durant la lectura");
        close(fitxer);
        return -1;
    }

    if (close(fitxer) == -1) {
        perror("Error en tancar el fitxer");
        return -1;
    }

    return 0;
