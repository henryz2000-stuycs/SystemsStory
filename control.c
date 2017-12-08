#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

int main(int argc, char **argv){
  int KEY = 24601;
  int S = -1;
  if (strcmp(argv[1], "-c") == 0){
    S = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0644);
    if (S != -1){
      semctl(S, 0, SETVAL, atoi(argv[2]));
      printf("semaphore created: %d\n", S);
      printf("value set: %d\n", semctl(S, 0, GETVAL));
    }
    else{
      printf("semaphore already exists\n");
    }
  }
  else if (strcmp(argv[1], "-v") == 0){
    S = semget(KEY, 1, 0);
    if (S != -1){
      printf("semaphore value: %d\n", semctl(S, 0, GETVAL));
    }
    else{
      printf("semaphore doesn't exist\n");
    }
  }
  else if (strcmp(argv[1], "-r") == 0){
    S = semget(KEY, 1, 0);
    if (S != -1){
      semctl(S, 0, IPC_RMID);
      printf("semaphore removed: %d\n", S);
    }
    else{
      printf("semaphore doesn't exist\n");
    }
  }
  return 0;
}
