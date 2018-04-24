#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {

  int value = 5; // what will the value become?

  pid_t pid;

  /* fork a child process */
  pid = fork();

  /* Both processes (the parent and the child) continues execution at the instruction after fork() */
  if (pid < 0) { /* error occurred */
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  else if (pid == 0) { /* child process */
    /* Child process consists of a copy of the address space of the original/parent process. */
    value = value + 5;
    return 0;
  }
  else { /* parent process */
    /* parent will wait fot the child to complete */
    wait(NULL);
    /* The result is still 5 as the child updates its copy of value. When control */
    /* returns to the parent, its value remains at 5 */
    printf("PARENT: Value = %d\n", value);
    return 0;
  }
}
