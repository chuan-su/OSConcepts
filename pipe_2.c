#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE  25
#define READ_END  0
#define WRITE_END  1

int main() {
  void reverse_msg(char *msg);

  char write_msg[BUFFER_SIZE] = "Hello Pipe";
  char read_msg[BUFFER_SIZE];

  int fd[2], fd_r[2];

  pid_t pid;

   /* Create the pipe */
  if (pipe(fd) == -1 || pipe(fd_r) == -1) {
    fprintf(stderr, "Pip Failed");
    return 1;
  }

  pid = fork();

  if (pid < 0) {
   fprintf(stderr, "Fork Failed");
   return 1;
  }

  if (pid > 0) {
    close(fd[READ_END]);
    close(fd_r[WRITE_END]);

    write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);

    close(fd[WRITE_END]);
    read(fd_r[READ_END], read_msg, BUFFER_SIZE);

    printf("Parent read: %s\n", read_msg);

    close(fd_r[READ_END]);
  } else {
    close(fd[WRITE_END]);
    close(fd_r[READ_END]);

    read(fd[READ_END], read_msg, BUFFER_SIZE);

    printf("Child read: %s\n", read_msg);

    close(fd[READ_END]);

    /* reverse the message and write to pipe_r */
    reverse_msg(read_msg);

    write(fd_r[WRITE_END], read_msg, strlen(read_msg) + 1);
    close(fd_r[WRITE_END]);
  }

  return 0;
}

void reverse_msg(char *msg)
{
  int i = 0;
  int j = strlen(msg) - 1;

  void swap(char *a, char *b);

  for (; i < j; i++, j--)
    swap(&msg[i], &msg[j]);
}

void swap(char *a, char *b)
{
  char tmp = *a;
  *a = *b;
  *b = tmp;
}
