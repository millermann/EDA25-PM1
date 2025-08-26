#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "alumno.h"

#define max_LSO_size 130

void strAMayus(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = toupper((unsigned char)str[i]);
        i++;
    }
}

typedef struct // LSO con tamaño conocido
{
    alumno vipd[max_LSO_size];
    int cur;
    int ultimoElem; // indice del ultimo elem guardado
} LSO;

void initLSO(LSO *lista)
{
    lista->cur = -1;
    lista->ultimoElem = -1;
}

int isFull(LSO lista)
{
    if (lista.ultimoElem == (max_LSO_size - 1))
        return 1;
    else
        return 0;
}

int isEmpty(LSO lista)
{
    if (lista.ultimoElem == -1)
        return 1;
    else
        return 0;
}

int isOos(LSO lista)
{
    if (lista.cur > lista.ultimoElem)
        return 1;
    else
        return 0;
}

alumno peek(LSO lista)
{
    return lista.vipd[lista.cur];
}

void forward(LSO *lista)
{
    lista->cur++;
}

void resetCur(LSO *lista)
{
    lista->cur = 0;
}

int localizar(char id[], LSO *lista) // Exito = 0
{
    int resultado;

    resetCur(lista);
    while (!isOos(*lista) && (resultado = strcmp(peek(*lista).codigo, id)) < 0)
    {
        forward(lista); // deja el cur justo en la celda del 1er elem (>=) a x que encuentra
    }

    return (resultado);
}

void alta(alumno x, LSO *lista)
{
    // antes de pedirle ingresar los datos al usuario controlar que hay espacio para un elem mas
    // cuando ingresa el codigo de registro controlar que no este en la lista y pedir correccion
    if (isEmpty(*lista) != 1)
    {
        localizar(x.codigo, lista);

        int aux = lista->ultimoElem;
        while (aux >= lista->cur)
        {
            lista->vipd[aux + 1] = lista->vipd[aux];
            aux--;
        }
        lista->vipd[lista->cur] = x;
        lista->ultimoElem = (lista->ultimoElem) + 1;
    }
    else
    {
        lista->cur = 0;
        lista->vipd[0] = x;
        lista->ultimoElem = 0;
    }
}

int baja(char codigo[], LSO *lista)
{
    int borrar = -1, check_resp = 0;

    if (localizar(codigo, lista) == 0)
    {
        mostrarDatos(peek(*lista));
        printf("\n\n - Seguro desea dar de baja al alumno (1 = Si / 0 = No)");
        printf("\n + Resp: ");
        check_resp = scanf("%d", &borrar);
        while (borrar > 1 || borrar < 0 || check_resp != 1)
        {
            printf("\n\a # Respuesta invalida...");
            printf("\n\n + Resp: ");
            fflush(stdin);
            check_resp = scanf("%d", &borrar);
        }

        if (borrar == 1)
        {
            int aux = lista->cur;
            while (aux < lista->ultimoElem)
            {
                lista->vipd[aux] = lista->vipd[aux + 1];
                aux++;
            }
            lista->ultimoElem = (lista->ultimoElem) - 1;
        }
    }
    return borrar;
}

int pertenece(char codigo[], LSO *lista)
{
    int exito = 0;
    if (!isEmpty(*lista))
    {
        if (localizar(codigo, lista) == 0)
            exito = 1;
    }
    return exito;
}

int modificar(char codigo[], LSO *lista)
{
    int exito = -1;
    if (localizar(codigo, lista) == 0)
    {
        int check_resp = 0, resp = 0;
        mostrarDatos(peek(*lista));
        alumno x;
        strcpy(x.codigo, peek(*lista).codigo);

        printf("\n\n - Ingrese el nombre completo del alumno: ");
        scanf(" %[^\n]", x.nombreCompleto);

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
        printf("\n # # # #   M O D I F I C A R   A L U M N O S   # # # #\n");
        printf("\n - Antes: ");
        mostrarDatos(peek(*lista));
        printf("\n - Modificado: ");
        mostrarDatos(x);
        printf("\n - Desea efectuar las modificaciones? (1 = Si / 0 = No)");
        printf("\n + Resp: ");
        check_resp = scanf("%d", &resp);
        while (resp < 0 || resp > 1 || check_resp != 1)
        {
            printf("\n\a # Respuesta no valida.");
            printf("\n + Resp: ");
            fflush(stdin);
            check_resp = scanf("%d", &resp);
        }
        exito = resp;
        if (resp == 1)
        {
            strcpy(lista->vipd[lista->cur].nombreCompleto, x.nombreCompleto);
            strcpy(lista->vipd[lista->cur].mail, x.mail);
            lista->vipd[lista->cur].nota = x.nota;
            strcpy(lista->vipd[lista->cur].condicion, x.condicion);
        }
    }
    return exito;
}

int memorizar(char direccionArchivo[], LSO *lista, int info[])
{
    FILE *archivo = fopen(direccionArchivo, "r");

    if (archivo == NULL)
        return 1;

    else
    {
        int n = 0, repetidos = 0;
        alumno x;
        char nombre[nomb_size], apellido[nomb_size];
        while (!feof(archivo) && !isFull(*lista))
        {
            fscanf(archivo, "%[^\n] ", x.codigo);
            strAMayus(x.codigo);
            fscanf(archivo, "%[^,],%[^\n] ", apellido, nombre);
            strcpy(x.nombreCompleto, strcat(apellido, nombre));
            fscanf(archivo, "%[^\n] ", x.mail);
            fscanf(archivo, "%d ", &x.nota);
            fscanf(archivo, "%[^\n] ", x.condicion);

            if (isEmpty(*lista) == 1)
                alta(x, lista), n++;

            else
            {
                if (localizar(x.codigo, lista) == 0)
                    repetidos++;

                else
                    alta(x, lista), n++;
            }
        }
        info[0] = n, info[1] = repetidos;
    }
    fclose(archivo);
    return 0;
}

alumno *evocar(char codigo[], LSO *lista)
{
    if (localizar(codigo, lista) == 0)
        return &lista->vipd[lista->cur];

    else
        return NULL;
}

void mostrarEstructura(LSO *lista)
{
    int aux = 0;

    resetCur(lista);
    while (isOos(*lista) != 1)
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
        mostrarDatos(peek(*lista));
        forward(lista);
    }
    printf("\n\n # No hay mas alumnos para mostrar...");
}
#endif // LSO_H_INCLUDED
