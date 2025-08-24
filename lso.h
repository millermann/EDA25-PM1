#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include "alumno.h"

#define max_LSO_size 130

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
    // control aca isEmpty????

    resetCur(lista);
    while (!isOos(*lista) && (resultado = strcmp(lista->vipd[lista->cur].codigo, id)) < 0)
    {
        // deja el cur justo en la celda del 1er elem (>=) a x que encuentra
        forward(lista);
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
    int opcion = -1, check_resp = 0;

    if (localizar(codigo, lista) == 0)
    {
        mostrarDatos(lista->vipd[lista->cur]);
        printf("\n\n - Seguro desea dar de baja al alumno (1 = Si / 0 = No)");
        printf("\n + Resp: ");
        check_resp = scanf("%d", &opcion);
        while (opcion > 1 || opcion < 0 || check_resp != 1)
        {
            printf("\n\a # Respuesta invalida...");
            printf("\n\n + Resp: ");
            fflush(stdin);
            check_resp = scanf("%d", &opcion);
        }

        if (opcion == 1)
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
    return opcion;

}

int pertenece(char codigo[], LSO *lista) // mas al pedo que concha de monja
{
    // control para listas vacias aca?
    if (localizar(codigo, lista) == 0)
        return 1;
    else
        return 0;
}

int modificar(char codigo[], LSO *lista){
    
    if (localizar(codigo, lista)!=0)
    {
        return 0;
    }
    else{
        
    }
    
    
    return 0;
}

int memorizar(char direccionArchivo[], LSO *lista, int info[]) // INC
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
            // PASAR A MAYUS EL CODIGO
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

// evocacion

/*void memorizar
    controlar e informar:
        * alumnos repetidos
        * archivo no encontrado
*/

// Operaciones que ordenan
// alta
// baja

#endif // LSO_H_INCLUDED
