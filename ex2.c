#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h> 
#include <stdlib.h>

int main(void) {
  int fd[2], pid;
  char buf[20];
  ssize_t bytesWrite, bytesRead, bytes = 20;
  
  pid = fork();

  if(pid == -1) {
    perror("Erro no processo filho");
    exit(errno);
  }
  if(pid == 0){
    printf("Digite até 20 caracteres:\n");
    gets(buf);

    fd[0] = open("arquivo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0755);

    bytesWrite = write(fd[0], &buf, strlen(&buf));

    printf("Foram gravados %d bytes no arquivo 'arquivo.txt'\n", bytesWrite);
    close(fd[0]);
    exit(0);

  } else {
    wait();
    fd[1]= open("arquivo.txt", O_RDONLY);

    printf ("Arquivo aberto com sucesso\n");
    sleep(2);

    printf("Tentando ler %d bytes do arquivo\n", bytes);
    sleep(2);

    bytesRead = read(fd[1], &buf, bytes);

    printf("Foram lidos %d bytes do arquivo\n", bytesRead);
    sleep(2);

    printf("Conteudo do arquivo: '%s'", buf);
    sleep(2);
    close(fd[1]);
    exit(0);
  }
}