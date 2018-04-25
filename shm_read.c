#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
  const int SIZE = 4096;
  const char *name = "OS";

  /* shared memory file descriptor */
  int shm_fd;
  /* pointer to shared memory object */
  void *ptr;

  /* open the shared memory object */
  shm_fd = shm_open(name, O_RDONLY, 0666);

  /* memory map the shared memory object */
  ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

  /* read form the shared memory object */
  printf("%s", (char *)ptr);

  /* remove the shared memory object */
  shm_unlink(name);

  return 0;
}
