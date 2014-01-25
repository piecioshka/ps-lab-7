/**
 * Zadanie 4.
 * Program czyta z dwóch plików, do których napływają dane. Napisz
 * program, który będzie czytał te pliki, do momentu, kiedy zostaną
 * zakończone i wyświetlał sumę przeczytanych bajtów z obydwu plików.
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> /* PIPE_BUF */

const int READ = 0;
const int WRITE = 1;

void zapisywanie(const char * komunikat, int licznik, FILE * strumien) {
    for (; licznik > 0; --licznik) {
        fprintf (strumien, "%s\n", komunikat);
        fflush (strumien);
        printf("..zapisujemy: %s\n", komunikat);
    }
}

void odczytywanie (FILE * strumien) {
    char bufor[1024];
    while (!feof (strumien) && !ferror (strumien) && fgets (bufor, sizeof (bufor), strumien) != NULL) {
        printf(" ... odczytujemy: %s\n", bufor);
        fputs (bufor, stdout);
    }
}

int main(int argc, char * argv[]) {
    int potok[2];

    /* tworzenie potoku */
    if (pipe(potok) == EOF) {
        perror("potok: pipe()");
        exit(1);
    }

    FILE * stream = fdopen(potok[1], "w");
    zapisywanie("Witam!", 2, stream);
    zapisywanie("Cie!", 2, stream);
    odczytywanie(stream);
    fclose(stream);

    return 0;
}
