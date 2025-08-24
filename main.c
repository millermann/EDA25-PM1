#include <stdio.h>
#include <stdlib.h>
#include "LSO.h"
#include "alumno.h"

int main()
{
    int opcion = -1, check_resp = 0, resultado = 0, resp = 0;
    LSO listaUsada;
    initLSO(&listaUsada);

    while (opcion != 0)
    {
        system("cls");
        printf("\n # # # # # # #   M E N U   # # # # # # #");
        printf("\n - - - - - - - - - - - - - - - - - - - - ");
        printf("\n  [1]   Ingresar de nuevos alumnos.");
        printf("\n  [2]   Eliminar alumnos existentes.");
        printf("\n  [3]   Modificar datos de un alumno.");
        printf("\n  [4]   Consultar la info del alumno.");
        printf("\n  [5]   Memorizacion previa.");
        printf("\n  [6]   Mostrar estructura.");
        printf("\n - - - - - - - - - - - - - - - - - - - - ");
        printf("\n  [0]  Salir.");
        printf("\n\n + Resp.: ");

        fflush(stdin);
        check_resp = scanf("%d", &opcion);
        while (opcion > 6 || opcion < 0 || check_resp != 1)
        {
            printf("\n\a # Respuesta invalida...");
            printf("\n\n + Resp: ");
            fflush(stdin);
            check_resp = scanf("%d", &opcion);
        }

        switch (opcion)
        {
        case 1:
        {
            system("cls");
            printf("\n # # # #   C A R G A R   A L U M N O   # # # #\n");

            if (isFull(listaUsada))
            {
                printf("\n\a # No hay suficiente memoria para cargar alumnos...");
            }
            else
            {
                alumno x;

                printf("\n - Ingrese el codigo del alumno: ");
                scanf("%s", x.codigo);

                // pasar a mayus el codigo

                while (pertenece(x.codigo, &listaUsada) && !isEmpty(listaUsada))
                {
                    printf("\n\a # El codigo de alumno ingresado ya existe en la base, por favor ingrese otro...");
                    printf("\n - Ingrese el codigo del alumno: ");
                    scanf("%s", x.codigo);
                }

                printf("\n - Ingrese el nombre completo del alumno: ");
                scanf("%s", x.nombreCompleto);

                printf("\n - Ingrese el correo del alumno: ");
                scanf("%s", x.mail);

                printf("\n - Ingrese la nota del alumno: ");
                check_resp = scanf("%d", &x.nota);
                while (x.nota < 0 || x.nota > 10 || check_resp != 1)
                {
                    printf("\n\a # La nota ingresada no es valida (0 <= nota <= 10), por favor vuelva a intentar...");
                    printf("\n - Ingrese el codigo del alumno: ");
                    fflush(stdin);
                    check_resp = scanf("%d", &x.nota);
                }

                printf("\n - Seleccione la condicion del alumno: ");
                printf("\n (1) Promociona, (2) Regular, (3) Libre, (4) Ausente");
                printf("\n + Resp: ");
                check_resp = scanf("%d", &resp);
                while (resp < 1 || resp > 4 || check_resp != 1)
                {
                    printf("\n\a # Respuesta no valida, por favor vuelva a intentar...");
                    printf("\n - Seleccione la condicion del alumno: ");
                    printf("\n (1) Promociona, (2) Regular, (3) Libre, (4) Ausente");
                    printf("\n + Resp: ");
                    fflush(stdin);
                    check_resp = scanf("%d", &resp);
                }
                switch (resp)
                {
                case 1:
                    strcpy(x.condicion, "Promociona");
                    break;
                case 2:
                    strcpy(x.condicion, "Regular");
                    break;
                case 3:
                    strcpy(x.condicion, "Libre");
                    break;
                case 4:
                    strcpy(x.condicion, "Ausente");
                }

                system("cls");
                printf("\n # # # #   C A R G A R   A L U M N O   # # # #\n");
                mostrarDatos(x);
                printf("\n\n - Confirmar alta (1 = Si / 0 = No) ");
                printf("\n + Resp: ");
                check_resp = scanf("%d", &resp);
                while (resp < 0 || resp > 1 || check_resp != 1)
                {
                    printf("\n\a # Respuesta no valida.");
                    printf("\n + Resp: ");
                    fflush(stdin);
                    check_resp = scanf("%d", &resp);
                }

                if (resp == 1)
                {
                    alta(x, &listaUsada);
                    printf("\n # Alumno cargado en la base...");
                }
                else
                    printf("\n # Alta cancelada...");
            }

            printf("\n\n - Pulse para volver al menu...");
            fflush(stdin);
            getchar();
            break;
        }

        case 2:
        {
            system("cls");
            printf("\n # # # #   B O R R A R   A L U M N O   # # # #\n");

            if (isEmpty(listaUsada))
                printf("\n\a # No hay alumnos cargados en la base...");
            else
            {
                char codigo[cod_alumno_size];

                printf("\n - Ingrese el codigo del alumno a eliminar: ");
                scanf("%s", codigo);
                resultado = baja(codigo, &listaUsada);

                switch (resultado)
                {
                case -1:
                    printf("\n\a # No se encontro el alumno en la base...\n");
                    break;
                case 0:
                    printf("\n # Baja cancelada...\n");
                    break;
                case 1:
                    printf("\n # Se ha dado baja al alumno...\n");
                    break;
                }
            }

            printf("\n - Pulse para volver al menu...");
            fflush(stdin);
            getchar();

            break;
        }
        case 3:
        {
            system("cls");
            printf("\n # # # #   M O D I F I C A R   A L U M N O S   # # # #\n");

            if (isEmpty(listaUsada))
                printf("\n\a # No hay alumnos cargados en la base...");
            else
            {
                char codigo[cod_alumno_size];
                printf("\n - Ingrese el codigo del alumno: ");
                scanf("%s", codigo);
                
            }
            break;
        }
        case 5:
        {
            int info[2];
            system("cls");
            printf("\n # # # #   M E M O R I Z A R   # # # #\n");

            if (isFull(listaUsada))
                printf("\n\a # No hay suficiente memoria para cargar alumnos...");
            else
            {
                if (memorizar("Alumnos.txt", &listaUsada, info) == 1)
                    printf("\n\a # Ocurrio un error al importar el archivo \"alumnos.txt\"...");
                else
                {
                    printf("\n # Se ha importado correctamente los datos del archivo \"alumnos.txt\"...");
                    printf("\n\t + Alumnos cargados: %d", info[0]);
                    printf("\n\t + Omitidos (Codigo no valido): %d", info[1]);
                }
            }

            printf("\n\n - Pulse para volver al menu...");
            fflush(stdin);
            getchar();
            break;
        }

        case 6:
        {
            system("cls");
            printf("\n # # # #   M O S T R A R   A L U M N O S   # # # #\n");
            if (isEmpty(listaUsada))
            {
                printf("\n\a # No hay alumnos cargados en la base...");
            }
            else
            {
                int aux = 0;

                resetCur(&listaUsada);
                while (isOos(listaUsada) != 1)
                {
                    if (aux > 3)
                    {
                        printf("\n\n - Pulse para continuar...");
                        fflush(stdin);
                        getchar();
                        system("cls");
                        printf("\n # # # #   M O S T R A R   A L U M N O S   # # # #\n");
                        aux = 0;
                    }
                    aux++;
                    mostrarDatos(peek(listaUsada));
                    forward(&listaUsada);
                }
                printf("\n\n # No hay mas alumnos para mostrar...");
            }
            printf("\n\n - Pulse para volver al menu...");
            fflush(stdin);
            getchar();
        }
        }
    }

    return 0;
}
