#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>


int main(){
  int pid;
  int *status;

  int shm_id = shmget(IPC_PRIVATE, 1024, IPC_CREAT |  0660);
   if (shm_id < 0) {
      printf("shmget error\n");
   }

  int *pidneto = (int*)shmat(shm_id, NULL, 0);

   if ((pid = fork()) < 0) {
      printf("erro no fork\n");
      pause();
      return(-1); 
   }

   if (pid == 0){
     pid = fork();

     if (pid == 0){
      sleep(5);
      printf("Ola processo sou o processo %d neto\n", *pidneto = getpid());
      exit(0);
     }
    else{
      wait(0);
      
      printf("Ola processo %d neto sou o processo %d filho\n",  *pidneto, getpid());
      sleep(5);
      exit(0); 
   
    }
   }
   else{
      wait(0);
      wait(0); //espera o processo filho encerrar
      printf("Sou o processo %d pai, sejam bem vindos\n", getpid());
      exit(0);
   }

   return 0;
}