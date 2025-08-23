#include <stdio.h>
#include <stdlib.h>
#include "alumno.h"

int main()
{
    int opcion = -1, check_resp=0;
    while (opcion != 0)
    {
        system("cls");
        printf("\n  []   ingreso de nuevos alumnos.");
        printf("\n  []   eliminar alumnos existentes.");
        printf("\n  []   modificar datos de un alumno.");
        printf("\n  []   consultar la informacion completa asociada al alumno.");
        printf("\n  []   memorizacion previa.");
        printf("\n  []   mostrar estructura.");
        printf("\n  [0]  Salir.");
        printf("\n\n + Resp.: ");
        
        fflush(stdin);
        check_resp = scanf("%d", &opcion);
        while(opcion>20 || opcion<0 || check_resp!=1){
            printf("\n\a # Respuesta invalida...");
            printf("\n\n + Resp: ");
            fflush(stdin);
            check_resp = scanf("%d", &opcion);
        }
    }

    return 0;
}
