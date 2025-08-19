#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED

#define nombSize 80
#define codAlumnoSize 7
#define mailSize 23

typedef struct{
    char codigo[codAlumnoSize];
    char nombreCompleto[nombSize];
    char mail[nombSize];
    int nota;
    char condicion[nombSize];
} Alumno;

#endif // ALUMNO_H_INCLUDED
