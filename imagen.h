#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>

struct Color {
  unsigned char r,g,b;
  Color(int r=0, int g=0, int b=0);
  void pasar_a_gris();
  bool operator==(const Color &der) const;
  bool operator!=(const Color &der) const;
  // línea nueva
  int a=0;

};


class ImagenColor {
public:
  int ancho,alto;
  Color *datos;

  ImagenColor(int ancho, int alto);
  ImagenColor(std::istream &fich_in);
  ImagenColor(const ImagenColor &der);
  ~ImagenColor();

  int indexPixel(int f, int c) const {
    return f*ancho + c;
  }

  Color* operator[](int x);
  Color& operator()(int x, int y);

  bool leer_ppm(std::istream &fich_in);
  void escribir_ppm(std::ostream &fich_out) const;

  void pasar_a_gris();

  bool operator==(const ImagenColor & der) const ;

  int numCompConex();    // ejercicio 2

  ImagenColor * pintarBlancaComponenteConexa(int f, int c);  // ej. adicional
  ImagenColor * devuelveComponenteConexa(int f, int c);      // ej. adicional
  ImagenColor * componenteConexaMayor();                     // ej. adicional
};

#endif // IMAGE_H
