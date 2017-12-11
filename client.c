#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>

int main(){

  int KEY = ftok("story.txt", 24601);

  int f = semget(KEY, 1, 0644);
  if(f == -1){
    printf("Could not locate semaphore.\n");
    return 1;
  }
  int shmid = shmget(KEY, 1024, 0644);
  if(shmid == -1){
    printf("Could not access shared memory\n");
  }
  int * shmem  = (int *)shmat(shmid, 0, 0);
  int last_line_size = *shmem;
  printf("%d\n", last_line_size);
  //int desc = open("story.txt", OWR_ONLY);
  //write()
  return 0;
}
