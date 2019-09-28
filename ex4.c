#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY 123

struct mesg_buffer { 
    long m_type; 
    char m_text[100]; 
} msg;

int main()
{
  int msgid, *status;  /* ID da fila de mensagens */
  key_t key;
  char *path = "nome_de_arquivo_existente";
  int pid, i = 0;
  int lg ;            /* tamanho da mensagem recebida */
  long type = 1 ;     /* tipo de mensagem buscado */
  int size_msg = 31 ; /* tamanho maximo do texto a ser recuperado */
  struct msqid_ds buf ;

  key = ftok(path, 65); 
  msgid = msgget(key, 0666 | IPC_CREAT); 
  msg.m_type = 1;

  if((pid = fork()) < 0){
      printf("Erro no fork\n");
      pause();
      return(-1);
  }

  if(pid == 0){
      pid = fork();
      if(pid == 0){
          printf("\nneto %d entrou\n", getpid());
          printf("fila %d\n", msgid);
          msg.m_type = 1;
          while (i <= 30)
          {
              sprintf(msg.m_text, "mensagem de numero %d de tipo %ld", i, msg.m_type);
              msgsnd(msgid,&msg,strlen(msg.m_text),IPC_NOWAIT);
              printf("-->Texto da mensagem: %s\n", msg.m_text);
              i++;
              sleep(1);
          }
          
      }else{
          wait(status);
          int j = 1;
          for(i = 0; i < 3; i++){

              while(j == 11){
                  
                lg=msgrcv(msgid,&msg,size_msg,type,IPC_NOWAIT|MSG_NOERROR);
                printf("Texto da mensagem (tamanho %d) recebido: %s\n", lg, msg.m_text);
                sleep(1);
                j++;
                if(j == 10)
                    break;
              }
              sleep(5);
              j = 0;
          }
          perror("Nao ha mais mensagens\n");
          exit(0);
      }
  }else{
      wait(status);
      msgid = msgget(key,0);
      msgctl(msgid,IPC_RMID,&buf);
      printf("Fila de mensagem destruída com sucesso\n");
      exit(0);
      exit(0);

  }
  return 0;
}