/**
 * Zadanie 2.
 * Zapoznaj się z programem simpleredirect.c
 * Program ten jest równoważny wykonaniu polecenia: ls -l | sort –n –k5.
 * a) Czy ma znaczenie, w którym procesie będzie wykonywane polecenie ls?
 * b) Co będzie się działo, jeśli deskryptory fd[0] i fd[1] nie będą zamknięte przed wywołaniem execl?
 * c) Rozbuduj program simpleredirect.c tak, aby polecenia do wykonania były pobierane
 * z wiersza wywołania programu.
 */
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

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

int main(int argc, char * argv[]) {
   pid_t childpid;
   int fd[2];
   char * command;
   char * first;
   char * second;
   char * search = "|";

   if (argc != 2) {
       fprintf(stderr, "Brak drugiego parametru\n");
       exit(1);
   }

   /* bierzemy pod uwagę parametr */
   command = argv[1];

   /* ls -l */
   first = strtok(command, search);
   /* sort -n -k5 */
   second = strtok(NULL, search);

   if ((pipe(fd) == -1) || ((childpid = fork()) == -1)) {
      perror("Failed to setup pipeline");
      return 1;
   }

   if (childpid == 0) {
      /* ls is the child */
      if (dup2(fd[1], STDOUT_FILENO) == -1) {
         perror("Failed to redirect stdout of ls");
      } else if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
         perror("Failed to close extra pipe descriptors on ls");
      } else {
         /* execl("/bin/ls", "ls", "-l", NULL); */
         printf("Pierwsze polecenie: %s\n", first);
         shellcmd(first);
         /* perror("Failed to exec ls"); */
      }
      return 1;
   }
   if (dup2(fd[0], STDIN_FILENO) == -1) {
       /* sort is the parent */
       perror("Failed to redirect stdin of sort");
   } else if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
       perror("Failed to close extra pipe file descriptors on sort"); 
   } else {
       /* execl("/usr/bin/sort", "sort", "-n", "-k5", NULL); */
       printf("Drugie polecenie: %s\n", second);
       shellcmd(second);
       waitpid(childpid, NULL, 0);
       /* perror("Failed to exec sort"); */
   }
   return 1;
}
