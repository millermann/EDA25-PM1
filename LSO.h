#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED

#include "alumno.h"

#define max_LSO_size 130

typedef struct{
    alumno vipd[max_LSO_size];
    int cur;
}LSO;

//void localizar(in x, out pos, out exito)
//alta
//baja
//pertenece
//evocacion
//modificacion

#endif // LSO_H_INCLUDED
