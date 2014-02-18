#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring> // strcmp
#include <iomanip> // setw
#include "imagen.h"
#include "mfset.h"

using namespace std;

Color::Color(int r, int g, int b){
    this->r=r;
    this->g=g;
    this->b=b;
}
void Color::pasar_a_gris() { 
  r=g=b=(unsigned char)(0.3*r+0.59*g+0.11*b); 
}

bool Color::operator==(const Color &der) const {
  return r==der.r && g==der.g && b==der.b;
}

bool Color::operator!=(const Color &der) const {
  return r!=der.r || g!=der.g || b!=der.b;
}

ImagenColor::ImagenColor(int ancho, int alto) {
  this->ancho = ancho;
  this->alto  = alto;
  datos       = new Color[ancho*alto];
}

ImagenColor::~ImagenColor() {
  delete[] datos;
}

ImagenColor::ImagenColor(std::istream &fich_in) {
  datos = 0;
  leer_ppm(fich_in); // si falla mala suerte
}

ImagenColor::ImagenColor(const ImagenColor &der) {
  ancho = der.ancho;
  alto = der.alto;
  int numpixels = ancho*alto;
  datos = new Color[numpixels];
  for (int i=0;i<numpixels;i++)
    datos[i] = Color(der.datos[i].r,
		     der.datos[i].g,
		     der.datos[i].b);
}


bool ImagenColor::leer_ppm(std::istream &fich_in) {
  // restriccion: este metodo de lectura no admite comentarios que,
  // sin embargo, estan contemplados en el formato pnm

  delete[] datos; // posiblemente borrar la imagen previa
  ancho = alto = 0; datos = 0;
  const int tallafirma = 100;
  char firma[tallafirma];
  fich_in >> std::setw(100) >> firma;
  if (strlen(firma)!=2 || firma[0] != 'P' ||
      firma[1]<'1' || firma[1]>'6') return false;
  int maxvalue, numpixels;
  fich_in >> ancho >> alto >> maxvalue;
  numpixels = ancho*alto;
  datos = new Color[numpixels];
  switch (firma[1]) {
  case '3': // ppm ascii
    int r,g,b;
    for (int i=0;i<numpixels;i++) {
      fich_in >> r >> g >> b;
      datos[i] = Color(r*255/maxvalue,
		       g*255/maxvalue,
		       b*255/maxvalue);
    }
    break;
  case '6': // ppm binario
    {
      fich_in.ignore();  // debe continuar la lectura. El puntero queda
      // en el carácter de nueva línea, por lo que debemos hacer una 
      // lectura en falso para que avance a la siguiente línea
      char *v = new char[numpixels*3];    // Cada pixel tiene asociados
      fich_in.read(v, numpixels*3);                       // tres bytes
      for (int i=0,n=0; i<numpixels; i++,n+=3)
	datos[i] = Color(v[n  ]*255/maxvalue,
			 v[n+1]*255/maxvalue,
			 v[n+2]*255/maxvalue);
      delete [] v;
    }
    break;
  default:
    // pnm format currently not supported
    return false;
  }
  return true;
}

void ImagenColor::escribir_ppm(std::ostream &fich_out) const {
  // TODO: permitir escribir en binario
  fich_out << "P3" << std::endl << ancho << ' ' << alto << std::endl
	   << "255" << std::endl;
  int numpixels = ancho*alto;
  for (int i=0; i<numpixels;i++)
    fich_out << (int)datos[i].r << ' '
	     << (int)datos[i].g << ' '
	     << (int)datos[i].b << std::endl;
}

Color* ImagenColor::operator[](int x) {
  return datos+ancho*x;
}

Color& ImagenColor::operator()(int x, int y) {
  return datos[ancho*x+y];
}

void ImagenColor::pasar_a_gris() {
  for (int i=ancho*alto-1;i>=0;--i) datos[i].pasar_a_gris();
}

bool ImagenColor::operator==(const ImagenColor & der) const { // Sobrecargamos
  if (ancho != der.ancho || alto != der.alto) // el operador de igualdad
    return false;              // para comparar imágenes más cómodamente
  for (int i=0; i<ancho*alto; i++)
    if (datos[i] != der.datos[i])
      return false;
  return true;
}

