/**
 * Zadanie 3.
 * Napisz program, składający się z procesu macierzystego i potomnego, w którym:
 * - proces macierzysty generuje komunikat,
 * - proces potomny odbiera komunikat za pomocą potoku, zamienia go na pisany wielkimi literami i przesyła z
 * powrotem za pomocą potoku do procesu macierzystego
 * - proces macierzysty drukuje otrzymany komunikat.
 * Uwaga: należy utworzyć dwa potoki łączące proces macierzysty i potomny.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> /* PIPE_BUF */
#include <ctype.h>

void toUpper(char *text, char *nText){
    for(int i = 0; i <= strlen(text); i++){
        if ((text[i] > 96 ) && (text[i] < 123) ) {
            nText[i] = text[i] - 'a' + 'A';
        } else {
            nText[i] = text[i];
        }
    }
}

int main(int argc, char * argv[]) {
    pid_t childpid = fork();
    int potok[2];
    char readed[PIPE_BUF];
    char modify[PIPE_BUF];
    char sended[PIPE_BUF];
    char received[PIPE_BUF];

    if (pipe(potok) == EOF) {
        perror("potok: pipe()");
        exit(1);
    }

    if (childpid == (pid_t) 0) {
        /* potomny */
        printf("[*] zamykamy potok[1]\n");
        close(potok[1]);

        printf("[*] czytamy z potok[0]\n");
        read(potok[0], readed, sizeof(readed));

        // toUpper(readed, modify);

        printf(" --- odczytany: %s\n", readed);
        printf(" --- zmodyfikowany: %s\n", modify);

        printf("[*] piszemy do potok[1]\n");
        write(potok[1], modify, sizeof(modify));

        printf("[*] zamykamy potok[1]\n");
        close(potok[1]);
    } else if (childpid > 0) {
        /* macierzysty */
        sprintf(sended, "jestem boski");
        printf(" >>> wysylamy: %s\n", sended);

        printf("[#] zamykamy potok[0]\n");
        close(potok[0]);

        printf("[#] piszemy do potok[1]\n");
        write(potok[1], sended, sizeof(sended));

        waitpid(childpid, NULL, 0);

        printf("[#] czytam z potok[0]\n");
        read(potok[0], received, sizeof(received));

        printf("[#] zamykamy potok[0]\n");
        close(potok[0]);

        printf(" <<< dostajemy: %s\n", received);
    } else {
        fprintf(stderr, "nie mozna utworzyć procesu potomnego");
        exit(1);
    }

    return 0;
}
