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
    if (lista.ultimoElem = max_LSO_size - 1)
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

int localizar(char id[], LSO *lista) // Exito = 0
{
    int resultado;
    while (lista->cur <= lista->ultimoElem && (resultado = strcmp(lista->vipd[lista->cur].codigo, id)) < 0)
    {
        // deja el cur justo en la celda del 1er elem (>=) a x que encuentra
        lista->cur = (lista->cur) + 1;
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
        while (aux > lista->cur)
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

void baja(alumno x, LSO *lista) // INC
{ 
    int resp;

    if (localizar(x.codigo, lista) == 0)
    {
        mostrarDatos(lista->vipd[lista->cur]);
        ("\n Seguro desea dar de baja al alumno...");
    }
}

int pertenece(char codigo[], LSO *lista) // mas al pedo que concha de monja
{
    // control para listas vacias aca?
    if (localizar(codigo, lista) == 0)
        return 1;
    else
        return 0;
}

int memorizar(char direccionArchivo, LSO *lista) // INC
{
    FILE *archivo_combos = fopen(direccionArchivo, "r");
}

// evocacion
// modificacion
/*void memorizar
    controlar e informar:
        * alumnos repetidos
        * archivo no encontrado
*/

// Operaciones que ordenan
// alta
// baja

#endif // LSO_H_INCLUDED
