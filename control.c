//standard
#include <stdio.h>
#include <stdlib.h>

//others
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

//both semaphore && shared memory
#include <sys/types.h>
#include <sys/ipc.h>

//semaphore
#include <sys/sem.h>

//shared memory
#include <sys/shm.h>

//file
#include <fcntl.h>
#include <sys/stat.h>


int main(int argc, char **argv){
  int KEY = ftok("story.txt", 24601);
  int sem = -1;
  int shm = -1;
  int fd = -1;

  union semun {
    int              val;
    struct semid_ds *buf;
    unsigned short  *array;
    struct seminfo  *__buf;
  } arg;

  /*
    If creating (command line argument: -c):
    Should make the shared memory, semaphore and file (open the file with the truncate flag).
    Set any values that are needed.
   */
  if (strcmp(argv[1], "-c") == 0){

    //create semaphore, shared memory, and file
    sem = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    shm = shmget(KEY, 1024, IPC_CREAT | IPC_EXCL | 0644);
    fd = open("story.txt", O_CREAT | O_TRUNC, 0644);
    close(fd);

    if (sem != -1 && shm != -1){
      printf("semaphore created: %d\n", sem);
      printf("shared memory created: %d\n", shm);
      printf("file created: %d\n", fd);

      arg.val = 1;
      semctl(sem, 0, SETVAL, arg);
      printf("semaphore value set: %d\n", semctl(sem, 0, GETVAL));
    }
    else if (sem == -1 && shm == -1){
      printf("both semaphore and shared memory already exist\n");
    }
    else if (sem == -1){
      printf("semaphore already exists\n");
    }
    else if (shm == -1){
      printf("shared memory already exists\n");
    }
  }

  /*
    If viewing (command line argument: -v)
    Output the contents of the story file.
    This mode does not need to interact with the semaphore
   */
  else if (strcmp(argv[1], "-v") == 0){
    fd = open("story.txt", O_RDONLY, 0644);
    struct stat sb;
    stat("story.txt", &sb);
    int size = sb.st_size;
    char * s = calloc(1, size+1);
    read(fd, s, size);
    printf("story: \n\t%s\n", s);
    close(fd);
  }

  /*
    If removing (command line argument: -r)
    Remove the shared memory and the semaphore
    Display the full contents of the story.
   */
  else if (strcmp(argv[1], "-r") == 0){
    sem = semget(KEY, 1, 0);
    shm = shmget(KEY, 1024, 0);
    if (sem != -1){
      semctl(sem, 0, IPC_RMID);
      printf("semaphore removed: %d\n", sem);

      shmctl(shm, IPC_RMID, 0);
      printf("shared memory removed: %d\n", shm);

      fd = open("story.txt", O_RDONLY, 0644);
      struct stat sb;
      stat("story.txt", &sb);
      int size = sb.st_size;
      char * s = calloc(1, size+1);
      read(fd, s, size);
      printf("final story: \n\t%s\n", s);

      remove("story.txt");
      printf("file removed: %d\n", fd);
      close(fd);
    }
    else{
      printf("semaphore doesn't exist\n");
    }
  }

  return 0;
}
