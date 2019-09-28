#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
//#include <pthread.h>


int main(){
   int pid, pidneto;
   int *status;
   sem_t mutex; 
   sem_init(&mutex, 1, 1);  //compartilhado entre processos


   if (( pid = fork()) < 0) {
     printf("erro no fork\n");
     exit(1);
   }else if (pid == 0){ //processo filho
      printf("Processo Filho\n");
      sem_wait(&mutex);
      sleep(1);

      printf("Processo Filho em regiao critica\n");
      sleep(5);
      
      printf("Processo Filho saindo de regiao critica\n");
      sem_post(&mutex);
      sleep(1);

   }else{ //processo pai
      wait(status); 
      printf("Processo Pai\n");
      sem_wait(&mutex);
      sleep(1);

      printf("Processo Pai em regiao critica\n");
      sleep(5);

      printf("Processo Pai saindo de regiao critica\n");
      sem_post(&mutex);
      sleep(5);

     return 0;
   }
}
