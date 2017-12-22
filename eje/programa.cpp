#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <time.h>
#include <vector>
#include "algoritmo_temporal.cpp"
#include <pqxx/pqxx>
#include <omp.h>
using namespace std;
using namespace pqxx;
//################################################### CONEXION ################################################
   string dbname= "docker";
   string user= "docker";
   string password= "docker";
   string hostaddr= "http://146.83.181.4";
   string port= "8082";
   string conexion= "dbname ="+dbname+" user = "+user+" password = "+password+" hostaddr = "+hostaddr+" port = "+port;
//###########################################cabesera##################################################################
//##########################################Definir variable#################################################
#define MAX_CARRACTERES 128
#define BLANCO "255 255 255"
#define BLANCO_VALOR 0
#define NEGRO "0 0 0"
#define NEGRO_VALOR 1
#define DATOS 10240
#define DATOS_F 1280

std::vector< std::vector<int> > cargar_datos(char *nombre);
void invertir_color(std::vector< std::vector<int> > datos);
int buscar_comienzo(char *nombre);
void pintar_camino(string camino, std::vector< std::vector<int> > datos);

int main(int argc, char const *argv[]) {
  clock_t start, end;
  start = clock();
  printf("1\n");
  std::vector< std::vector<int> > datos;
  printf("2\n");
  char *nombre_2=(char*)"final";
  printf("3\n");
  datos = cargar_datos(nombre_2);
  printf("4\n");
  char resultado_camino[8000];
  printf("5\n");
  int valor=2048;
  bool ok=true;
  int xw=1;
  printf("5.1\n");
  while(xw<5){
    printf("%d\n",xw );
    printf("%d\n",(valor*xw));
    if(datos[(valor*xw)][(valor*xw)]==0){valor --;}
    xw++;
    if(xw == 5){
      for (int i = 1; i < 5; i++) {
        if(datos[valor*i][valor*i]==0){ xw =0; break;}
        }
      }
    }
  printf("%d\n",valor );
  #pragma omp parallel for
 for(int x=1; x < 5; x++){
    if(datos[valor*x][valor*x]==0){valor --;}
    if(x==1){funcion_main(datos,41,1,(valor*x),(valor*x),resultado_camino);}
    if(x==4){funcion_main(datos,(valor*x),(valor*x),10239,10238,resultado_camino);}
    if(x>1 && x<4){funcion_main(datos,(valor*x),(valor*x),(valor*(x+1)),(valor*(x+1)),resultado_camino);}
    pintar_camino(resultado_camino,datos);
  }
  invertir_color(datos);
  printf("6\n");
  end = clock();
  printf("termnio #_#\n");
  return 0;
}
//####################################################funciones######################################

std::vector< std::vector<int> > cargar_datos(char *nombre){
  char cadena[MAX_CARRACTERES];
  long fila=0;
  long columna=0;
  long contador=0;
  bool temporal=true;

  // Creamos un vector auxiliar para juntar la informacion de cada fila (junta las columnas de una fila en un solo vector)
  vector<int> vectorAux;
  // Creamos el vector que va a contener el otro vector, de esta forma hacemos una matriz
  // Quedaria algo como esto: matrizAux = [vectorAux, vectorAux, ..., vectorAux]
  vector<vector<int> > matrizAux;

  ifstream fe(nombre);
  while(!fe.eof()) {
    fe.getline(cadena, MAX_CARRACTERES);
    contador++;
    if (contador<5 ) {
      continue;
    }
    if(columna==10240){
      // Adjunta el vector a la matriz (ver imagen de referencia)
      matrizAux.push_back(vectorAux);
      vectorAux.clear(); // limpia vector auxiliar para cargar nuevos datos sin que esten los anteriores
      columna=0;
      fila++;
    }
    if (fila==10240) {
      break;
    }
    if (strcmp(BLANCO,cadena)==0) {
        //printf("Blanco (%ld , %ld)\n",fila,columna);
        vectorAux.push_back(BLANCO_VALOR); // llena vector
      }
      else{
         if (strcmp(NEGRO,cadena)==0) {
           //printf("Negro (%ld , %ld)\n",fila,columna);
           vectorAux.push_back(NEGRO_VALOR); // llena vector
         }
         else{
             printf("Error %s (%ld,%ld)\n",cadena,fila,columna);
         }
      }
    columna++;
  }
  fe.close();
  return matrizAux;
}
void invertir_color(std::vector< std::vector<int> > datos){
  printf("entro\n");
  FILE *fp;
  fp = fopen ( "temporal", "a" );
  fprintf(fp, "P3\n10240\n10240\n255\n");
  for (long i =0; i < 10240; i++) {
    for (long z = 0; z < 10240; z++) {
      if (datos[i][z]==1) {
        fprintf(fp,"255 255 255\n");
      } else if(datos[i][z]==0) {
        fprintf(fp,"0 0 0\n");
      }else{fprintf(fp,"255 0 0\n");}
    }
  }
  fclose(fp);
  printf("salio\n");
}
int buscar_comienzo(char *nombre){
  char cadena[MAX_CARRACTERES];
  int valor = -5;
  ifstream fe(nombre);
  while(!fe.eof()) {
    valor++;
     fe.getline(cadena, MAX_CARRACTERES);
     if (strcmp(BLANCO,cadena)==0) {
       return valor/DATOS;
     }
  }
  fe.close();
}
void pintar_camino(string camino, std::vector< std::vector<int> > datos){
  printf("entro en pintar_camino\n");
  if (strcmp(camino.c_str(),"Error")!=0) {
    string sentencia= camino;
    std::stringstream sstm;
    string temporal;
    int fila;
    int columna;
    int largo;
    char separador = '-'; //aqui vas a introducir el separador -en mi caso es un espacio-
    size_t tam= camino.length();
    camino.erase(tam-1); //con la funcion erase(), borramos los caracteres
    //desde la posicion que le damos como argumento hasta el final
    //ahora la palabra tendra 1 caracter menos
    //std::cout << camino << '\n';
    for(size_t p=0, q=0; p!=sentencia.npos; p=q){
      std::stringstream sstm;
      sstm << sentencia.substr(p+(p!=0),(q=sentencia.find(separador, p+1))-p-(p!=0))<<"\n";
        fila=atoi(sstm.str().substr(1,sstm.str().find(",")-1).c_str());
        largo= sstm.str().find(")") - sstm.str().find(",");
        columna=atoi(sstm.str().substr((sstm.str().find(",")+1),largo-1).c_str());
          datos[fila][columna]=2;
    }
    printf("salio en pintar_camino\n");
  }
  else{printf("Error pintar_camino \n");}
}
