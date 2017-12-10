#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  int f = semget(ftok("story.txt", 24601), 1);
  void * shmem  = shmat(shmget(f, 256), 0);
  int desc = open("story.txt", OWR_ONLY);
  write()
  
}
