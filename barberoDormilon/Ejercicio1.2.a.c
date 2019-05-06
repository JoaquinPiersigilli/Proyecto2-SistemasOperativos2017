/**
    Barbero dormilon (Memoria compartida)
    Joaquin Piersigilli, Utizi Sebastian
**/
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

//Defino el numero de clientes del barbero
#define NCLIENTES 20
//Defino el numero de sillas de la sala de espera
#define NSILLAS 10

typedef struct Memoria
{
    sem_t clienteListo; //Simulo la cantidad de clientes esperando, listos para un corte
    sem_t barberoTermino; //Simulo cuando el barbero termino un corte y esta libre
    sem_t sillasLibres; //Simulo la cantidad de sillas que quedan libres en la sala
} shared_data;

int main()
{
    int i;
    int clientes [NCLIENTES];
    //Creo y abro el nuevo espacio de memoria
    shared_data *mem;
    int memDescriptor;
    memDescriptor = shm_open("Memoria compartida", O_CREAT | O_RDWR, 0666);
    if(memDescriptor == -1)
    {
        perror("Error al crear la memoria compartida.");
        exit(1);
    }
    ftruncate(memDescriptor, sizeof(struct Memoria));
    mem = mmap(0, sizeof(struct Memoria), PROT_WRITE, MAP_SHARED, memDescriptor, 0);

    //Inicializo el struct
    sem_init(&(mem->barberoTermino), 1, 0);
    sem_init(&(mem->clienteListo), 1, 0);
    sem_init(&(mem->sillasLibres), 1, NSILLAS);

//Barbero
    int pid = fork();
    if(pid < 0)
    {
        perror("Error al crear al barbero.");
        exit(1);
    }
    if(pid == 0)
    {
        //Mientras haya clientes que atender
        while (1)
        {
            printf("El barbero esta descansando esperando a un cliente\n");
            fflush(stdout);
            sem_wait(&(mem->clienteListo));
            fflush(stdout);
            //Libero la silla ocupada por el cliente
            sem_post(&(mem->sillasLibres));
            printf("El barbero le corta el pelo a un cliente\n");
            fflush(stdout);
            sleep(2);
            printf("El barbero termino de trabajar.\n");
            fflush(stdout);
            sem_post(&(mem->barberoTermino));
        }
    }

//Cliente
    for(i=0; i<NCLIENTES; i++)
    {
        clientes[i] = fork();
        if(clientes[i] < 0)
        {
            perror("Error al crear los clientes.");
            exit(1);
        }
        if(clientes[i] == 0)
        {
            printf("El cliente: %d acaba de llegar.\n", i);
            fflush(stdout);
            //Espero a que haya lugar en la sala de espera
            sem_wait(&(mem->sillasLibres));
            printf("El cliente %d ocupa una silla de la sala.\n", i);
            fflush(stdout);
            //Espero a que la silla del barbero este libre
            sem_post(&(mem->clienteListo));
            sem_wait(&(mem->barberoTermino));
            exit(0);
        }
    }

    //Espero a que terminen todos los clientes
    for(i=0; i<NCLIENTES; i++)
    {
        wait(NULL);
    }

    return 0;
}
