#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
  const int SIZE = 4096;
  const char *name = "OS";
  const char * message_0 = "Hello";
  const char * message_1 = "Process!";

  pid_t pid;

  int shm_fd;
  void *ptr;

  shm_fd = shm_open(name, O_CREAT | O_RDONLY, 0666);
  ftruncate(shm_fd, SIZE);
  ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork Failed\n");
    return 1;
  } else if (pid == 0) {
    shm_fd = shm_open(name, O_RDWR, 0666);
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    sprintf(ptr, "%s", message_0);
    ptr += strlen(message_0);
    sprintf(ptr, "%s", message_1);
    ptr += strlen(message_1);
  } else {
    wait(NULL);
    printf("%s\n", (char *) ptr);
    shm_unlink(name);
  }

  return 0;
}
