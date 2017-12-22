#include "pngpixel_200.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define RANGO 200 // rango de los pixceles fila y columna
#define MAX_SECCION_FILA 51
#define MAX_SECCION_COLUMNA 51
int main(int argc, const char **argv) {
  char *nombre="laberinto.png";
  char fila[3];
  char columna[3];
  int seccion_fila;
  int seccion_columna;
  char nombre_2[10];
  long  rango_columna , rango_fila;
  int i,j;
  #pragma omp parallel for private(j,nombre_2,seccion_fila,rango_fila,seccion_columna,rango_columna)
  for (int i = 1; i < (MAX_SECCION_FILA+1); i++) {
    seccion_fila=i;
    rango_fila=(seccion_fila-1)*RANGO;
    for (int j = 1; j < (MAX_SECCION_COLUMNA+1); j++) {
      seccion_columna=j;
      rango_columna=(seccion_columna-1)*RANGO;
      sprintf(nombre_2, "datos/%d-%d", i, j);
      funcion_main(4,rango_fila,rango_columna,nombre, seccion_fila,seccion_columna,nombre_2);
    }
  }
  printf("termino\n");
  return 0;
}
