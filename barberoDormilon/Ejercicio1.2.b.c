/**
    Barbero dormilon (Cola de mensajes)
    Joaquin Piersigilli, Utizi Sebastian
**/

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define barberoListo 1
#define clienteListo 2
#define sillasLibres 3
#define NCLIENTES 20
#define NSILLAS 10

typedef struct my_msg   // Estrucutra del mensaje.
{
    long type;
} msg;

int main()
{
    pid_t pid;  // ID de procesos.
    int q_id;
    int msg_sz;
    msg buffer;
    int i;
    int clientes[NCLIENTES];

    q_id = msgget(IPC_PRIVATE, IPC_CREAT | 0666);  //  Se crea la cola de mensajes.
    msg_sz = sizeof(struct my_msg);

    //Inicializo las sillas libres
    buffer.type = sillasLibres;
    for (i=0; i<NSILLAS; i++)
    {
        msgsnd(q_id, &buffer, msg_sz, 0);
    }

    //Inicialmente el barbero duerme y no trabaja
    buffer.type = barberoListo;
    msgsnd(q_id, &buffer, msg_sz, 0);

    //Barbero
    pid = fork();
    if(pid==0)
    {
        while(1)
        {
            msgrcv(q_id, &buffer, msg_sz, clienteListo, 0);
            buffer.type = sillasLibres;
            msgsnd(q_id, &buffer, msg_sz, 0);

            printf("El barbero le corta el pelo a un cliente\n");
            fflush(stdout);
            buffer.type=barberoListo;
            msgsnd(q_id, &buffer, msg_sz, 0);
        }
    }

    //Clientes
    for(i=0; i<NCLIENTES; i++)
    {
        clientes[i]=fork();

        if(clientes[i]==0)  //estoy en el hijo
        {
            printf("Llego un nuevo cliente\n");
            fflush(stdout);
            //Ocupo una silla en la sala
            msgrcv(q_id, &buffer, msg_sz, sillasLibres, 0);
            printf("El cliente entro en la sala\n");
            fflush(stdout);
            msgrcv(q_id, &buffer, msg_sz, barberoListo, 0);
            //El barbero esta listo y le aviso que hay un cliente esperando
            buffer.type=clienteListo;
            msgsnd(q_id, &buffer, msg_sz, 0);

            exit(0);
        }
    }

    //Espero a que terminen todos los hijos
    for(i=0; i<NCLIENTES; i++)
    {
        wait(NULL);
    }

    msgctl(IPC_PRIVATE, IPC_RMID, NULL);  // Se elimina la cola.

    return 0;
}
