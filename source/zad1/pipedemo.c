/**
 * Zadanie 1.
 * Zapoznaj się z programem pipedemo.c.
 * Napisz program, który będzie wysyłał list automatycznie generowany przez program.
 * Do wysyłania listu użyj polecenia mail.
 * $ sudo launchctl start org.postfix.master // uruchomienie serwera mailowego
 * Użyteczna funkcja: do utworzenia składowych polecenia można użyć instrukcji:
 * sprintf(arg,"-s 'Wiadomosc od procesu PID %d'", getpid());
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#define EMAIL "piecioshka@gmail.com"

int shellcmd(char *command) {
    int status;
    pid_t pid;
    extern int errno;

    if ((pid = fork()) < 0) {
        status = -1;
    }

    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", command, NULL);
        _exit(127);
    }

    while (waitpid(pid, &status, 0) < 0) {
        if (errno != EINTR) {
            status = -1;
            break;
        }
    }

    return status;
}

void sendmail() {
    char command[255];
    sprintf(command, "echo '' | mail -v -s 'Wiadomosc od procesu PID %d' %s", getpid(), EMAIL);
    printf("%s\n", command);
    shellcmd(command);
}

int main () {
    int fd[2];
    pid_t pid;
    pipe(fd);
    pid = fork();

    if (pid == (pid_t) 0) {
        /* macieszysty */
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execlp("sort", "sort", 0);
    } else if (pid > 0) {
        /* potomek */
        sendmail();
        FILE * strumien;
        close(fd[0]);
        strumien = fdopen(fd[1], "w");
        fprintf(strumien, "Witam.\n");
        fprintf(strumien, "Welcome.\n");
        fprintf(strumien, "Bienvenue.\n");
        fprintf(strumien, "Willkommen.\n");
        fflush(strumien);
        close(fd[1]);
        waitpid(pid, NULL, 0);
    } else {
        fprintf(stderr, "nie mozna utworzyc procesu potomnego\n");
    }

    return 0;
}
