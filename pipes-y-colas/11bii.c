/**,
    Ejercicio 1.1.b.ii
    Joaquin Piersigilli, Utizi Sebastian
**/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>


#define A 1
#define AA 2
#define B1 3
#define B2 4
#define BB 5
#define C1 6
#define C2 7
#define C3 8
#define D1 9
#define D2 10
#define D3 11
#define E1 12
#define E2 13


typedef struct my_msg{  // Estrucutra del mensaje.
	long type;
}msg;


//ABCDE 

//AABCD 

//BBCDE
int main()
{

	pid_t childpid;  // ID de procesos.
	int q_id;
	int msg_sz;
	msg buffer;

	q_id = msgget(IPC_PRIVATE, IPC_CREAT | 0666);  //  Se crea la cola de mensajes.
	msg_sz = sizeof(struct my_msg);


	buffer.type=A;
  	msgsnd(q_id, &buffer, msg_sz, 0);


	// Estoy en el proceso padre y creo el
        // Proceso A
        if((childpid = fork()) == -1){  //Hay error en la creacion del proceso hijo
                perror("fork");
                exit(1);
        }

        if(childpid == 0){
            //Si el fork devolvió 0 estoy en el proceso hijo

		while(1){

         		msgrcv(q_id, &buffer, msg_sz, A, 0);
        		printf("A");
        		fflush(stdout);
        		buffer.type=B1;
        		msgsnd(q_id, &buffer, msg_sz, 0);
		
			msgrcv(q_id, &buffer, msg_sz, AA, 0);
        		printf("AA");
        		fflush(stdout);
        		buffer.type=B2;
        		msgsnd(q_id, &buffer, msg_sz, 0);
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

		while(1){

			msgrcv(q_id, &buffer, msg_sz, B1, 0);
        		printf("B");
        		fflush(stdout);
        		buffer.type=C1;
        		msgsnd(q_id, &buffer, msg_sz, 0);

			msgrcv(q_id, &buffer, msg_sz, B2, 0);
        		printf("B");
        		fflush(stdout);
        		buffer.type=C2;
        		msgsnd(q_id, &buffer, msg_sz, 0);

			msgrcv(q_id, &buffer, msg_sz, BB, 0);
        		printf("BB");
        		fflush(stdout);
        		buffer.type=C3;
        		msgsnd(q_id, &buffer, msg_sz, 0);
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

		while(1){

			msgrcv(q_id, &buffer, msg_sz, C1, 0);
        		printf("C");
        		fflush(stdout);
        		buffer.type=D1;
        		msgsnd(q_id, &buffer, msg_sz, 0);

			msgrcv(q_id, &buffer, msg_sz, C2, 0);
        		printf("C");
        		fflush(stdout);
        		buffer.type=D2;
        		msgsnd(q_id, &buffer, msg_sz, 0);

			msgrcv(q_id, &buffer, msg_sz, C3, 0);
        		printf("C");
        		fflush(stdout);
        		buffer.type=D3;
        		msgsnd(q_id, &buffer, msg_sz, 0);		
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

		while(1){

			msgrcv(q_id, &buffer, msg_sz, D1, 0);
        		printf("D");
        		fflush(stdout);
        		buffer.type=E1;
        		msgsnd(q_id, &buffer, msg_sz, 0);

			msgrcv(q_id, &buffer, msg_sz, D2, 0);
        		printf("D ");
        		fflush(stdout);
        		buffer.type=BB;
        		msgsnd(q_id, &buffer, msg_sz, 0);

			msgrcv(q_id, &buffer, msg_sz, D3, 0);
        		printf("D");
        		fflush(stdout);
        		buffer.type=E2;
        		msgsnd(q_id, &buffer, msg_sz, 0);	

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

		while(1){

			msgrcv(q_id, &buffer, msg_sz, E1, 0);
        		printf("E ");
        		fflush(stdout);
        		buffer.type=AA;
        		msgsnd(q_id, &buffer, msg_sz, 0);

			msgrcv(q_id, &buffer, msg_sz, E2, 0);
        		printf("E ");
        		fflush(stdout);
        		buffer.type=A;
        		msgsnd(q_id, &buffer, msg_sz, 0);

		}
		exit(0);
	}


	int i;
   	for(i=0; i<5;i++){
       	   wait(NULL);
   	}

   	msgctl(IPC_PRIVATE, IPC_RMID, NULL);  // Se elimina la cola.

    	exit(0);
}	




























