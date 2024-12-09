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
                }
        }
