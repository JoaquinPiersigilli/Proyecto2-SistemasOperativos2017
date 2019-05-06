/**,
    Ejercicio 1.1.a.i
    Joaquin Piersigilli, Utizi Sebastian
**/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{

        //Declaro los pipes
        int pipeA[2]; //Este pipe se usa para escribir la letra A y habilitar la escritura de la letra B
        int pipeB[2]; //Este pipe se usa para escribir la letra B y habilitar la escritura de la letra C o la D
        int pipeCoD[2]; //Este pipe se usa para escribir la letra C o la D y habilitar la escritura de la letra E
        int pipeE[2]; //Este pipe se usa para escribir la letra E y habilitar la escritura de la letra A

        pid_t   childpid;
        char mensaje;

        //Creo los pipes
        pipe(pipeA);
        pipe(pipeB);
        pipe(pipeCoD);
        pipe(pipeE);

        //Utilizo el lado de escritura del pipeA para poder comenzar con el primer proceso hijo sin que se bloquee el read
        //y luego de una vuelta de la secuencia ABCoDE continue por ese proceso
        write(pipeA[1],"N", 1);

        // Estoy en el proceso padre y creo el
        // Proceso A
        if((childpid = fork()) == -1){  //Hay error en la creacion del proceso hijo
                perror("fork");
                exit(1);
        }

        if(childpid == 0){
            //Si el fork devolvió 0 estoy en el proceso hijo

                //close(pipeA[0]); Dejo abierto el lado de lectura del pipeA
                close(pipeA[1]);
                close(pipeB[0]);
                //close(pipeB[1]); Dejo abierto el lado de escritura
                close(pipeCoD[0]);
                close(pipeCoD[1]);
                close(pipeE[0]);
                close(pipeE[1]);

                while(1){
                    read(pipeA[0], &mensaje, sizeof(char));
                    printf("A");
                    fflush(stdout);
                    write(pipeB[1],"N", 1);
		  //  sleep(1);
                }
                exit(0);
        }

        //Estoy en el proceso padre y creo el
        //Proceso B

        if((childpid = fork()) == -1){
                perror("fork");
                exit(1);
        }

        if(childpid == 0){
                //Si el fork devolvió 0 estoy en el proceso hijo

                close(pipeA[0]);
                close(pipeA[1]);
                //close(pipeB[0]); Dejo abierto el lado de lectura del pipeB
                close(pipeB[1]);
                close(pipeCoD[0]);
               // close(pipeCoD[1]); Dejo abierto el lado de escritura del pipeCoD
                close(pipeE[0]);
                close(pipeE[1]);

                while(1){
                    read(pipeB[0], &mensaje, sizeof(char));
                    printf("B");
                    fflush(stdout);
                    write(pipeCoD[1],"N", 1);
			//sleep(1);
                }
                exit(0);
        }

        //Estoy en el proceso padre y creo el
        // Proceso C

        if((childpid = fork()) == -1){
                perror("fork");
                exit(1);
        }

        if(childpid == 0){
                //Si el fork devolvió 0 estoy en el proceso hijo

                close(pipeA[0]);
                close(pipeA[1]);
                close(pipeB[0]);
                close(pipeB[1]);
               //close(pipeCoD[0]); Dejo abierto el lado de lectura del pipeCoD
                close(pipeCoD[1]);
                close(pipeE[0]);
               //close(pipeE[1]); Dejo abierto el lado de escritura del pipeE

                while(1){
                    read(pipeCoD[0], &mensaje, sizeof(char));
                    printf("C");
                    fflush(stdout);                   
		 write(pipeE[1],"N", 1);
		//sleep(1);
                }
                exit(0);
        }

        //Estoy en el proceso padre y creo el
        // Proceso D

        if((childpid = fork()) == -1){
                perror("fork");
                exit(1);
        }

        if(childpid == 0){
                //Si el fork devolvió 0 estoy en el proceso hijo

                close(pipeA[0]);
                close(pipeA[1]);
                close(pipeB[0]);
                close(pipeB[1]);
                //close(pipeCoD[0]); Dejo abierto el lado de lectura del pipeCoD
                close(pipeCoD[1]);
                close(pipeE[0]);
                //close(pipeE[1]); Dejo abierto el lado de escritura del pipeE

                while(1){
                    read(pipeCoD[0], &mensaje, sizeof(char));
                    printf("D");
                    fflush(stdout);
                    write(pipeE[1],"N", 1);
		//	sleep(1);
                }
                exit(0);
        }


        //Estoy en el proceso padre y creo el
        // Proceso E

        if((childpid = fork()) == -1){
                perror("fork");
                exit(1);
        }

        if(childpid == 0){
                //Si el fork devolvió 0 estoy en el proceso hijo

                close(pipeA[0]);
                //close(pipeA[1]); Dejo abierto el lado de escritura del pipeA
                close(pipeB[0]);
                close(pipeB[1]);
                close(pipeCoD[0]);
                close(pipeCoD[1]);
                //close(pipeE[0]); Dejo abierto el lado de lectura del pipeE
                close(pipeE[1]);

                while(1){
                    read(pipeE[0], &mensaje, sizeof(char));
                    printf("E ");
                    fflush(stdout); 
                    write(pipeA[1],"N", 1);
			// sleep(1);

                }
                exit(0);
        }


        //Estoy en el proceso padre luego de haber creado todos los procesos hijos encargados de imprimir cada letra sincronizandose con pipes.

        int i;
        for ( i=0; i<6; i++)  //  Espera por la finalización de todos sus hijos.
            wait(NULL);

        exit (1);
}
