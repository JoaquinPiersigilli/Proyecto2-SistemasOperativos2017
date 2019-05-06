/**
    Pryecto 2 - Ejercicio 2.1 - Asignacion de permisos
    Piersigilli Joaquin - Utizi Sebastian
**/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc,char *argv[3]){
    if(argc != 3){
        perror("Argumentos ingresados incorrectamente\n");
        exit(1);
    }
       mode_t permisos = strtol(argv[2], NULL, 8);
       int res = chmod(argv[1], permisos);
       if (res == -1){
            perror("El permiso no pudo ser asignado\n");
            exit(2);
        }
    printf("Permisos asignados correctamente\n");
    return 0;
}
