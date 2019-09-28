#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>

int main()
{

    //Criação de processos
    int shm_id, n, count = 0;
    pid_t pid;

    printf("\nDigite a quatidade de operações N:");
    scanf("%d", &n);

    //compartilhamento de memoria
    shm_id = shmget(IPC_PRIVATE, 1024, IPC_CREAT | 0660);
    if (shm_id < 0)
    {
        printf("shmget error\n");
    }
    int *shrd = (int *)shmat(shm_id, NULL, 0);

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }

    //Produz um loop nos processo ate o valor digitado pelo usuário
    for (count = 0; count <= n; count++)
    {
        //Execução do processo filho
        if (pid == 0)
        {
            if (count == 0)
            {
                *shrd = 0;
            }
            else
            {
                if (count < n)
                {
                    printf("\npid do Filho: %d", getpid());
                    printf("\nProcesso filho\nNumero incrementado = %d\n", *shrd);
                    *shrd += 1;
                }
                else
                {
                    *shrd = n;
                }
            }
        }
        //Execução do Processo Pai
        else
        {
            printf("\npid do Pai: %d", getpid());
            printf("\nProcesso pai\nNumero incrementado = %d\n", *shrd);
            if (count < n)
            {
                *shrd += 1;
            }
            else
            {
                printf("\nProcessos encerrados\nNumero N = %d", *shrd);
            }
        }
    }
    exit(0);
}
