/**,
    Ejercicio 1.1.a.ii
    Joaquin Piersigilli, Utizi Sebastian
**/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

//ABCDEAABCDBBCDEABCDE...

//ABCDE AABCD BBCDE 

int main()
{

        //Declaro los pipes
        int pipeA[2]; 
	int pipeAA[2];

        int pipeB1[2];
	int pipeB2[2];  
	int pipeBB[2];

        int pipeC1[2];
	int pipeC2[2]; 
	int pipeC3[2]; 

	int pipeD1[2]; 
	int pipeD2[2];
	int pipeD3[2]; 

        int pipeE1[2];
	int pipeE2[2];

        pid_t   childpid;
        char mensaje;

        //Creo los pipes
        pipe(pipeA);
	pipe(pipeAA);
        pipe(pipeB1);
        pipe(pipeB2);
	pipe(pipeBB);
        pipe(pipeC1);
	pipe(pipeC2);
	pipe(pipeC3);
	pipe(pipeD1);
	pipe(pipeD2);
	pipe(pipeD3);
	pipe(pipeE1);
	pipe(pipeE2);

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

                //close(pipeA[0]);
		close(pipeA[1]);
		//close(pipeAA[0]);
		close(pipeAA[1]);

		close(pipeB1[0]);
		//close(pipeB1[1]);
		close(pipeB2[0]);
		//close(pipeB2[1]);
		close(pipeBB[0]);
		close(pipeBB[1]);

		close(pipeC1[0]);
		close(pipeC1[1]);
		close(pipeC2[0]);
		close(pipeC2[1]);
		close(pipeC3[0]);
		close(pipeC3[1]);


		close(pipeD1[0]);
		close(pipeD1[1]);
		close(pipeD2[0]);
		close(pipeD2[1]);
		close(pipeD3[0]);
		close(pipeD3[1]);


		close(pipeE1[0]);
		close(pipeE1[1]);
		close(pipeE2[0]);
		close(pipeE2[1]);
			

                while(1){
                    read(pipeA[0], &mensaje, sizeof(char));
                    printf("A");
                    fflush(stdout);
                    write(pipeB1[1],"N", 1);

		    read(pipeAA[0], &mensaje, sizeof(char));
		    printf("AA");
		    fflush(stdout);
		    write(pipeB2[1],"N", 1);
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
		close(pipeAA[0]);
		close(pipeAA[1]);

		//close(pipeB1[0]);
		close(pipeB1[1]);
		//close(pipeB2[0]);
		close(pipeB2[1]);
		//close(pipeBB[0]);
		close(pipeBB[1]);

		close(pipeC1[0]);
		//close(pipeC1[1]);
		close(pipeC2[0]);
		//close(pipeC2[1]);
		close(pipeC3[0]);
		//close(pipeC3[1]);


		close(pipeD1[0]);
		close(pipeD1[1]);
		close(pipeD2[0]);
		close(pipeD2[1]);
		close(pipeD3[0]);
		close(pipeD3[1]);


		close(pipeE1[0]);
		close(pipeE1[1]);
		close(pipeE2[0]);
		close(pipeE2[1]);

                while(1){
                    read(pipeB1[0], &mensaje, sizeof(char));
                    printf("B");
                    fflush(stdout);
                    write(pipeC1[1],"N", 1);

		    read(pipeB2[0], &mensaje, sizeof(char));
		    printf("B");
		    fflush(stdout);
		    write(pipeC2[1],"N", 1);

		    read(pipeBB[0], &mensaje, sizeof(char));
                    printf("BB");
                    fflush(stdout);                   
		    write(pipeC3[1],"N", 1);
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
		close(pipeAA[0]);
		close(pipeAA[1]);

		close(pipeB1[0]);
		close(pipeB1[1]);
		close(pipeB2[0]);
		close(pipeB2[1]);
		close(pipeBB[0]);
		close(pipeBB[1]);

		//close(pipeC1[0]);
		close(pipeC1[1]);
		//close(pipeC2[0]);
		close(pipeC2[1]);
		//close(pipeC3[0]);
		close(pipeC3[1]);


		close(pipeD1[0]);
		//close(pipeD1[1]);
		close(pipeD2[0]);
		//close(pipeD2[1]);
		close(pipeD3[0]);
		//close(pipeD3[1]);


		close(pipeE1[0]);
		close(pipeE1[1]);
		close(pipeE2[0]);
		close(pipeE2[1]);

                while(1){
                    read(pipeC1[0], &mensaje, sizeof(char));
                    printf("C");
                    fflush(stdout);                   
		    write(pipeD1[1],"N", 1);

		    read(pipeC2[0], &mensaje, sizeof(char));
                    printf("C");
                    fflush(stdout);                   
		    write(pipeD2[1],"N", 1);

		    read(pipeC3[0], &mensaje, sizeof(char));
                    printf("C");
                    fflush(stdout);                   
		    write(pipeD3[1],"N", 1);
		
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
		close(pipeAA[0]);
		close(pipeAA[1]);

		close(pipeB1[0]);
		close(pipeB1[1]);
		close(pipeB2[0]);
		close(pipeB2[1]);
		close(pipeBB[0]);
		//close(pipeBB[1]);

		close(pipeC1[0]);
		close(pipeC1[1]);
		close(pipeC2[0]);
		close(pipeC2[1]);
		close(pipeC3[0]);
		close(pipeC3[1]);


		//close(pipeD1[0]);
		close(pipeD1[1]);
		//close(pipeD2[0]);
		close(pipeD2[1]);
		//close(pipeD3[0]);
		close(pipeD3[1]);


		close(pipeE1[0]);
		//close(pipeE1[1]);
		close(pipeE2[0]);
		//close(pipeE2[1]);

                while(1){
                    read(pipeD1[0], &mensaje, sizeof(char));
                    printf("D");
                    fflush(stdout);
                    write(pipeE1[1],"N", 1);

		    read(pipeD2[0], &mensaje, sizeof(char));
                    printf("D ");
                    fflush(stdout);                   
		    write(pipeBB[1],"N", 1);

		    read(pipeD3[0], &mensaje, sizeof(char));
                    printf("D");
                    fflush(stdout);                   
		    write(pipeE2[1],"N", 1);
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
		//close(pipeA[1]);
		close(pipeAA[0]);
		//close(pipeAA[1]);

		close(pipeB1[0]);
		close(pipeB1[1]);
		close(pipeB2[0]);
		close(pipeB2[1]);
		close(pipeBB[0]);
		close(pipeBB[1]);

		close(pipeC1[0]);
		close(pipeC1[1]);
		close(pipeC2[0]);
		close(pipeC2[1]);
		close(pipeC3[0]);
		close(pipeC3[1]);


		close(pipeD1[0]);
		close(pipeD1[1]);
		close(pipeD2[0]);
		close(pipeD2[1]);
		close(pipeD3[0]);
		close(pipeD3[1]);


		//close(pipeE1[0]);
		close(pipeE1[1]);
		//close(pipeE2[0]);
		close(pipeE2[1]);

                while(1){
                    read(pipeE1[0], &mensaje, sizeof(char));
                    printf("E ");
                    fflush(stdout); 
                    write(pipeAA[1],"N", 1);

		    read(pipeE2[0], &mensaje, sizeof(char));
                    printf("E ");
                    fflush(stdout); 
                    write(pipeA[1],"N", 1);
                }
                exit(0);
        }


        //Estoy en el proceso padre luego de haber creado todos los procesos hijos encargados de imprimir cada letra sincronizandose con pipes.

        int i;
        for ( i=0; i<6; i++)  //  Espera por la finalización de todos sus hijos.
            wait(NULL);

        exit (1);
}
