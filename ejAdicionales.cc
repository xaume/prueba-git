#include <iostream>
#include <fstream>
#include "imagen.h"
#include "mfset.h"

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


// Ejercicio adicional 
ImagenColor* pintarBlancaComponenteConexa(ImagenColor &ima,
					  int fil, int col ){

  // el mfSet se crea y configura como en numCompConex
  mfSet M(ima.ancho * ima.alto);    
  for (int f=0; f<ima.alto; f++)
    for (int c=0; c<ima.ancho; c++){
      if (c < ima.ancho -1 && ima(f,c)==ima(f,c+1))
	M.merge(ima.indexPixel(f,c), ima.indexPixel(f,c+1));
      if (f < ima.alto -1 && ima(f,c) == ima(f+1,c))
	M.merge(ima.indexPixel(f,c), ima.indexPixel(f+1,c));
    }  

  // obtenemos el representante del pixel
  int rep=M.find(ima.indexPixel(fil,col));

  // definimos el color blanco
  Color blanco(255,255,255);

  // creamos una imagen copia de la original
  ImagenColor *resul = new ImagenColor(ima);

  // ponemos en blanco los pixels de la componente conexa
  for (int f=0; f<ima.alto; f++)
    for (int c=0; c<ima.ancho; c++) 
      if (M.find(ima.indexPixel(f,c)) == rep)
	(*resul)(f,c) = blanco;

  return resul;
}

// Ejercicio adicional 
ImagenColor* devuelveComponenteConexa(ImagenColor &ima,
				      int fil, int col) { 

  // el mfSet se crea y configura como en numCompConex
  mfSet M(ima.ancho * ima.alto);    
  for (int f=0; f<ima.alto; f++)
    for (int c=0; c<ima.ancho; c++){
      if (c < ima.ancho -1 && ima(f,c)==ima(f,c+1))
	M.merge(ima.indexPixel(f,c), ima.indexPixel(f,c+1));
      if (f < ima.alto -1 && ima(f,c) == ima(f+1,c))
	M.merge(ima.indexPixel(f,c), ima.indexPixel(f+1,c));
    }  

  // obtenemos el representante del pixel
  int rep=M.find(ima.indexPixel(fil,col));

  // creamos una imagen en negro del mismo tamanyo:
  ImagenColor *resul = new ImagenColor(ima.ancho,ima.alto);

  // copiamos los pixels de la componente conexa
  for (int f=0; f<ima.alto; f++)
    for (int c=0; c<ima.ancho; c++) 
      if (M.find(ima.indexPixel(f,c)) == rep)
	(*resul)(f,c) = ima(f,c);

  return resul;
}

// Ejercicio adicional 
ImagenColor* componenteConexaMayor(ImagenColor & ima) {

  // el mfSet se crea y configura como en numCompConex
  mfSet M(ima.ancho * ima.alto);    
  for (int f=0; f<ima.alto; f++)
    for (int c=0; c<ima.ancho; c++){
      if (c < ima.ancho -1 && ima(f,c)==ima(f,c+1))
	M.merge(ima.indexPixel(f,c), ima.indexPixel(f,c+1));
      if (f < ima.alto -1 && ima(f,c) == ima(f+1,c))
	M.merge(ima.indexPixel(f,c), ima.indexPixel(f+1,c));
    }  

  // averiguamos la componente conexa con mas pixels
  int numSub = M.numSubconjuntos();
  int* repr  = M.obtenRepresentantes();
  
  // vector de contadores
  int* cont  = new int[numSub];
  for (int i=0; i<numSub; i++)
    cont[i]=0;
  
  // esto se podria hacer mas eficiente
  for (int f=0; f<ima.alto; f++)
    for (int c=0; c<ima.ancho; c++) {
      int rpixel = M.find(ima.indexPixel(f,c));
      for (int r=0; r<numSub; r++)
	if (rpixel==repr[r])
	  cont[r]++;
    }  
  int max=0;
  int r_max=0;
  for (int r=0; r<numSub; r++)
    if (cont[r]>max){
      max=cont[r];
      r_max=r;
    }
  
  // creamos una imagen en negro del mismo tamanyo:
  ImagenColor *resul = new ImagenColor(ima.ancho,ima.alto);
  
  // copiamos los pixels de la componente conexa
  for (int f=0; f<ima.alto; f++)
    for (int c=0; c<ima.ancho; c++) 
      if (M.find(ima.indexPixel(f,c)) == repr[r_max])
	(*resul)(f,c) = ima(f,c);
  
  return resul;
}

int main(int argc, char **argv) {
  if (argc != 5) {
    cerr << "Usage " << argv[0]
         << " image_file_in image_file_out (without .pnm) fil col" << endl
	 << "Write result in files image_file_out_1.pnm image_file_out_2.pnm image_file_out_3.pnm" << endl;
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
 
  int f,c;
  f=atoi(argv[3]);
  c=atoi(argv[4]);
  char dest_filename[1024];
  ofstream fich_sal;
  ImagenColor * imag = 0;

  // PRIMER EJERCICIO ADICIONAL
  strcpy(dest_filename,argv[2]);
  strcat(dest_filename,"_1.pnm");
  fich_sal.open(dest_filename);
  if (!fich_sal){
    cerr << "El fichero \"" << dest_filename << "\" no se puede abrir" << endl;
    exit(-1);
  }
  imag = pintarBlancaComponenteConexa(ima, f, c);
  imag->escribir_ppm(fich_sal);
  fich_sal.close();
  delete imag; // borramos la imagen

  // SEGUNDO EJERCICIO ADICIONAL
  strcpy(dest_filename,argv[2]);
  strcat(dest_filename,"_2.pnm");
  fich_sal.open(dest_filename);
  if (!fich_sal){
    cerr << "El fichero \"" << dest_filename << "\" no se puede abrir" << endl;
    exit(-1);
  }
  imag = devuelveComponenteConexa(ima, f, c);
  imag->escribir_ppm(fich_sal);
  fich_sal.close();
  delete imag; // borramos la imagen

  // TERCER EJERCICIO ADICIONAL
  strcpy(dest_filename,argv[2]);
  strcat(dest_filename,"_3.pnm");
  fich_sal.open(dest_filename);
  if (!fich_sal){
    cerr << "El fichero \"" << dest_filename << "\" no se puede abrir" << endl;
    exit(-1);
  }
  imag = componenteConexaMayor(ima);
  imag->escribir_ppm(fich_sal);
  fich_sal.close();
  delete imag; // borramos la imagen

  return 0;
}
