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

const int READ = 0;
const int WRITE = 1;

#define MESSAGE "klawiatura"

void toUpper(char *text, char *nText){
    for (int i = 0; i <= strlen(text); i++){
        nText[i] = toupper(text[i]);
    }
}

int main(int argc, char * argv[]) {
    pid_t childpid;
    int potok[2];

    /* tworzenie potoku */
    if (pipe(potok) == EOF) {
        perror("potok: pipe()");
        exit(1);
    }

    /* tworzenie procesu potomnego */
    childpid = fork();

    if (childpid == (pid_t) 0) {
        /* potomny */
        char readed[PIPE_BUF];
        printf("[*] czytamy z potok[READ]\n");
        if (read(potok[READ], readed, sizeof(readed)) == EOF) {
            perror("Problem with read() #1");
        }

        char modify[PIPE_BUF];
        toUpper(readed, modify);

        printf(" --- odczytany: %s\n", readed);
        printf(" --- zmodyfikowany: %s\n", modify);

        printf("[*] zamykamy potok[READ]\n");
        close(potok[READ]);

        printf("[*] piszemy do potok[WRITE]\n");
        if (write(potok[WRITE], modify, sizeof(modify)) == EOF) {
            perror("Problem with write() #1");
        }
    } else if (childpid > 0) {
        /* macierzysty */
        char sended[PIPE_BUF];
        sprintf(sended, MESSAGE);
        printf(" >>> wysylamy: %s\n", sended);

        printf("[#] piszemy do potok[WRITE]\n");
        if (write(potok[WRITE], sended, sizeof(sended)) == EOF) {
            perror("Problem with write() #2");
        }

        /* czekamy na proces potomny */
        waitpid(childpid, NULL, 0);

        printf("[#] zamykamy potok[WRITE]\n");
        close(potok[WRITE]);

        char received[PIPE_BUF];
        printf("[#] czytam z potok[READ]\n");
        if (read(potok[READ], received, sizeof(received)) == EOF) {
            perror("Problem with read() #2");
        }

        printf(" <<< dostajemy: %s\n", received);
    } else {
        fprintf(stderr, "nie mozna utworzyć procesu potomnego");
        exit(1);
    }

    return 0;
}
