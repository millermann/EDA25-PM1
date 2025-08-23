#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED

#define cod_alumno_size 7
#define nomb_size 80
#define mail_size 23
#define cond_size 10

typedef struct
{
    char codigo[cod_alumno_size];
    char nombreCompleto[nomb_size];
    char mail[mail_size];
    int nota;
    char condicion[cond_size];
} alumno;

void mostrarDatos(alumno x)
{
    printf("\n    ###################################");
    printf("\n     + Codigo: %s", x.codigo);
    printf("\n       + Alumno: %s", x.nombreCompleto);
    printf("\n       + Mail: %s", x.mail);
    printf("\n       + Nota: %d", x.nota);
    printf("\n       + Condicion: %s", x.condicion);
}
#endif // ALUMNO_H_INCLUDED
