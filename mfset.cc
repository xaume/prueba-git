#include <iostream>
#include "mfset.h"

//////////////////////////////////////////////////
// con fusion por rango y compresion de caminos //
//////////////////////////////////////////////////

mfSet::mfSet(int talla) {
  n = talla;
  nSubconjuntos = talla;
  mfs = new int[n];
  for (int i=0; i<n; i++)
    mfs[i] = -1;              // la altura del nodo i es -(mfs[i]+1).
}

mfSet::~mfSet() {
  delete[] mfs;
}

int mfSet::find(int x) { 
  int rx=x;
  while (mfs[rx] >= 0) // buscamos representante
      rx = mfs[rx];
  while (mfs[x] > 0) { // volvemos a recorrer el camino
      int tmp = x; x = mfs[x]; mfs[tmp] = rx;
  }
  return rx;
}

void mfSet::merge(int x, int y) {
  int rx,ry;
  rx = find(x);
  ry = find(y);
  if (rx != ry) {
    nSubconjuntos--;        
    if (mfs[rx] == mfs[ry]) {  
      mfs[ry] = rx;               // ponemos y como hijo de x
      mfs[rx]--;                  // incrementamos la altura de                
    }                               // uno de los arboles es mas alto
    else if (mfs[rx] < mfs[ry]) // altura(x) > altura(y)
      mfs[ry] = rx;               // ponemos y como hijo de x
    else
      mfs[rx] = ry;               // ponemos x como hijo de y
  }
}
int mfSet::numSubconjuntos() {
  return nSubconjuntos;
}

int *  mfSet::obtenRepresentantes() {
    int * representantes = new int [nSubconjuntos];
    int p = 0;
    for (int i=0; i<n; i++)
        if (mfs[i] < 0) {
            representantes[p] = i;
            p++;
        }
    return representantes;
}

int  mfSet::obtenRepresentanteCompMayor(){
     int * cont = new int[n];
     for (int i=0; i<n; i++)
	 cont[i]=0;

     for (int i=0; i<n; i++){
	 int r=find(i);
	 cont[r]++;
     }

     int max=cont[0];
     int c_max=0;
     for (int i=1; i<n; i++)
	 if (cont[i] > max){
	     max=cont[i];
	     c_max=i;
	 }

     return c_max;
     
}
