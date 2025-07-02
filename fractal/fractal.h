#include "../color/color.h"

#ifndef FRACTAL_H
#define FRACTAL_H 1

typedef struct Fractal_s Fractal ;

Fractal* Fractal_create(int width, int height, double canvasW) ;

void Fractal_set_center(Fractal* f, double x, double y) ;
void Fractal_set_rotation(Fractal* f, double rot) ;
void Fractal_set_max_iter(Fractal* f, int max_iter) ;
void Fractal_set_bound(Fractal* f, double bound) ;
void Fractal_set_gradient(Fractal* f, Gradient* gradient) ;

__u_char* Fractal_get_pixel_data(Fractal* f) ;

void Fractal_generate_mandelbrot(Fractal* f) ;
void Fractal_generate_julia(Fractal* f, double cRe, double cIm) ;

void Fractal_destroy(Fractal* f);

#endif