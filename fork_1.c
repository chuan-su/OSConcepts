#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {

  pid_t pid;

  /* fork a child process */
  pid = fork();

  /* Both processes (the parent and the child) continues execution at the instruction after fork() */
  if (pid < 0) { /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  else if (pid == 0) { /* child process */
    execlp("/bin/ls", "ls", NULL);
    printf("Line J");
    /* by invocking exec, child process overlayed its address space copied from parent by a new program*/
  }
  else { /* parent process */
    /* parent will wait fot the child to complete */
    wait(NULL);
    printf("Child Complete\n");
  }

  return 0;
}
