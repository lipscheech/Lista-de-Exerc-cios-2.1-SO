#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(){
  int pid;

   if ((pid = fork()) < 0) {
      printf("erro no fork\n");
      pause();
      exit(-1);
   }

   if (pid == 0){
     pid = fork();

     if (pid == 0){
      sleep(5);
      printf("Ola processo sou o processo %d neto\n", getpid());
      exit(0);
     } else{
      wait(0);
      
      printf("Ola processo %d neto sou o processo %d filho\n",  pid, getpid());
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