#include <iostream>
#include <fstream>
#include "mfset.h"
#include "imagen.h"

using namespace std;

int numCompConex(ImagenColor &ima) {

  mfSet M(ima.ancho * ima.alto);    

  for (int f=0; f<ima.alto; f++)
    for (int c=0; c<ima.ancho; c++){
      if (c < ima.ancho -1 && ima(f,c)==ima(f,c+1))
	M.merge(ima.indexPixel(f,c), ima.indexPixel(f,c+1));
      if (f < ima.alto -1 && ima(f,c) == ima(f+1,c))
	M.merge(ima.indexPixel(f,c), ima.indexPixel(f+1,c));
    }  

  return M.numSubconjuntos();
}

int main(int argc, char **argv) {
  if (argc != 2) {
    cerr << "Usage " << argv[0]
         << " image_file_in" << endl;
    return 0;
  }
  
  ifstream fich_ent(argv[1]); // modo lectura
  if (!fich_ent){
    cerr << "El fichero \"" << argv[1] << "\" no se puede abrir" << endl;
    exit(-1);
  }
  cerr << "Leyendo la imagen ..."<< endl;
  ImagenColor ima(fich_ent);
  fich_ent.close();
  
  cout << "Numero de comp. conexas = " << numCompConex(ima) << endl;
  
  return 0;
  
}
