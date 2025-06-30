#ifndef FRACTAL_H
#define FRACTAL_H 1

typedef struct Fractal_s Fractal ;

Fractal* Fractal_create(int width, int height, double canvasW) ;

void Fractal_set_center(Fractal* f, double x, double y) ;
void Fractal_set_rotation(Fractal* f, double rot) ;
void Fractal_set_max_iter(Fractal* f, int max_iter) ;
void Fractal_set_bound(Fractal* f, double bound) ;

__u_char* Fractal_get_pixel_data(Fractal* f) ;

void Fractal_generate_mandelbrot(Fractal* f);

void Fractal_destroy(Fractal* f);

#endif