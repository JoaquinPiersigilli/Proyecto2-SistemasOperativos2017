/**,
    Ejercicio 2.2 Manejo de direcciones
    Joaquin Piersigilli, Utizi Sebastian
**/


#include <stdio.h>
#include <stdlib.h>

#define PAG 4096 //Defino el tamanio de la pagina
                 //4KB = 4096B

int main()
{
    char direccionString [20];
    int direccion;
    int desplazamiento;
    int pagina;

    printf("Ingrese una direccion en decimal:");
    scanf("%s", &direccionString);
    direccion = atoi(direccionString);

    pagina = direccion / PAG;
    desplazamiento = direccion % PAG;

    printf("Pagina: %i, desplazamiento: %i\n", pagina, desplazamiento);

    return 0;
}