/**
 * Zadanie 6.
 * Napisz program, który prosi o podanie hasła i kończy działanie, jeśli
 * użytkownik nie wprowadzi hasła w określonym czasie. Wprowadzane hasło
 * ma być maskowane.
 */
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define TIME 10
#define PASSWORD "kanapka"

void sigalrm_handler() {
    printf("\nERR: Czas uplynal...\n");
    exit(1);
}

int main(int argc, char * argv[]) {
    /* hasło użytkownika */
    char password;

    printf("Wpisz haslo (masz na to %d sek.): ", TIME);

    /* dodajemy obsługę sygnału SIGALRM */
    signal(SIGALRM, sigalrm_handler);

    /* wysyłamy sygnał SIGALRM za określoną liczbę sekund */
    alarm(TIME);

    /* czyścimy bufor */
    fflush(stdout);

    /* pobieramy hasło od użytkownika */
    scanf("%s", &password);

    /* sprawdzamy, czy hasło jest poprawne */
    if (strcmp(&password, PASSWORD) == 0) {
        printf("Haslo poprawne!\n");
        exit(0);
    } else {
        printf("ERR: Haslo niepoprawne\n");
        exit(2);
    }

    /* czekamy na syngał */
    pause();

    return 0;
}
