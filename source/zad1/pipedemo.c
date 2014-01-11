#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main ()
{
  int fd[2];
  pid_t pid;
  pipe(fd);
  pid = fork ();
  if (pid == (pid_t) 0) {
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    execlp("sort", "sort", 0);
  }
  else {
    FILE* strumien;
    close (fd[0]);
    strumien = fdopen(fd[1], "w");
    fprintf(strumien, "Witam.\n");
    fprintf(strumien, "Welcome.\n");
    fprintf(strumien, "Bienvenue.\n");
    fprintf(strumien, "Willkommen.\n");
    fflush(strumien);
    close(fd[1]);
    waitpid(pid, NULL, 0);
  }

  return 0;
}

