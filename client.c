#include "work15.h"

int main(){

  int KEY = ftok("story.txt", 24601);

  struct sembuf s1;

  s1.sem_op = -1;
  s1.sem_num = 0;
  s1.sem_flg = SEM_UNDO;

  int f = semget(KEY, 1, 0);
  if(f == -1){
    printf("Could not locate semaphore.\n");
    return 1;
  }
  semop(f, &s1, 1);

  int shmid = shmget(KEY, 1024, 0);
  if(shmid == -1){
    printf("Could not access shared memory.\n");
    return 1;
  }
  
  int * shmem  = shmat(shmid, 0, 0);
  
  char * story = (char *)calloc(1, *shmem + 1);
  int desc = open("story.txt", O_RDWR | O_APPEND);
  lseek(desc, -1 * *shmem, SEEK_END);
  read(desc, story, *shmem);
  printf("Last line added to file:\n%s\n", story);
  
  printf("Add next line:\n");
  char * next_line;
  fgets(next_line, sizeof(next_line), stdin);
  printf("Line recorded as: %s\n", next_line);
  
  *shmem = strlen(next_line);
  write(desc, next_line, *shmem);
  close(desc);
  
  if(shmdt(shmem) == -1){
    printf("Failed to detach shared memory segment from variable\n");
  }
  
  s1.sem_op = 1;
  semop(f, &s1, 1);
  
  free(story);
  
  return 0;
}
