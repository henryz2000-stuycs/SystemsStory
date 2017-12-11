#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){

  int KEY = ftok("story.txt", 24601);

  struct sembuf s1;
  struct sembuf s2;

  s1.sem_op = -1;
  s1.sem_num = 0;
  s1.sem_flg = SEM_UNDO;
  s2.sem_op = 1;
  s2.sem_num = 0;

  int f = semget(KEY, 1, 0644);
  if(f == -1){
    printf("Could not locate semaphore.\n");
    return 1;
  }
  semop(f, &s1, 1);
  int shmid = shmget(KEY, 1024, 0644);
  if(shmid == -1){
    printf("Could not access shared memory.\n");
    return 1;
  }
  int * shmem  = (int *)shmat(shmid, 0, 0);
  int last_line_size = *shmem;
  int desc = open("story.txt", O_RDONLY | O_WRONLY, 644);
  lseek(desc, last_line_size, SEEK_END);
  char last_line[last_line_size];
  read(desc, last_line, last_line_size);
  printf("Last line added to file:\n%s\n", last_line);
  printf("Add next line:\n");
  char next_line[256];
  scanf("%s", next_line);
  int buf_size = strlen(next_line);
  write(desc, next_line, buf_size);
  close(desc);
  write(*(shmem), &buf_size, sizeof(int));
  if(shmdt(shmem) == -1){
    printf("Failed to detach shared memory segment from variable\n");
  }
  semop(f, &s2, 1);
  return 0;
}
