#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "fractal.h"

typedef double complex Cplx ;

typedef struct Fractal_s {
    int width;
    int height;
    double centerX;
    double centerY;
    double canvasW;
    double canvasH;
    double rot;
    int max_iter;
    double bound;
    int* pixel_data;
} Fractal;

Fractal* Fractal_create(int width, int height, double canvasW) {
    Fractal* f = malloc(sizeof(Fractal));
    f->width = width;
    f->height = height;
    f->centerX = 0;
    f->centerY = 0;
    f->canvasW = canvasW;
    f->canvasH = canvasW * height / width;
    f->rot = 0;
    f->max_iter = 100;
    f->bound = 2;
    f->pixel_data = malloc(f->width * f->height * sizeof(int));
    return f;
}

void Fractal_set_center(Fractal* f, double x, double y) {
    f->centerX = x;
    f->centerY = y; 
}

void Fractal_set_rotation(Fractal* f, double rot) {
    f->rot = rot;
}

void Fractal_set_max_iter(Fractal* f, int max_iter) {
    f->max_iter = max_iter;
}

void Fractal_set_bound(Fractal* f, double bound) {
    f->bound = bound;
}

__u_char* Fractal_get_pixel_data(Fractal* f) {
    
    __u_char* image_rgb = malloc(f->width * f->height * 3 * sizeof(__u_char));
    for (int i = 0; i < f->width * f->height; i++) {
        __u_char color = 255 - (f->pixel_data[i] * 255 / f->max_iter);
        image_rgb[3 * i + 0] = color;
        image_rgb[3 * i + 1] = color;
        image_rgb[3 * i + 2] = color;
    }

    return image_rgb;

}

Cplx pixel_to_complex(Fractal* f, int px, int py) {

    // Normalize pixel coordinates to [-1, 1] range
    double normalized_x = (2.0 * px / (f->width - 1)) - 1.0;
    double normalized_y = 1.0 - (2.0 * py / (f->height - 1)); // Flip y-axis

    // Scale to the complex plane dimensions
    double scaled_x = normalized_x * (f->canvasW / 2.0);
    double scaled_y = normalized_y * (f->canvasH / 2.0);

    // Apply rotation
    double cos_angle = cos(f->rot);
    double sin_angle = sin(f->rot);
    double rotated_x = scaled_x * cos_angle - scaled_y * sin_angle;
    double rotated_y = scaled_x * sin_angle + scaled_y * cos_angle;

    // Translate to the center of the complex plane
    Cplx c = f->centerX + rotated_x + (f->centerY + rotated_y) * _Complex_I;

    return c;

}

int compute_mandelbrot(Fractal* f, Cplx c) {

    Cplx zn = c;

    int i = 0;
    while (i < f->max_iter && cabs(zn) < f->bound) {
        zn = zn * zn + c;
        i++;
    }

    return i;

}

void Fractal_generate_mandelbrot(Fractal* f) {

    for (int py = 0; py < f->height; py++) {
        for (int px = 0; px < f->width; px++) {

            Cplx c = pixel_to_complex(f, px, py);
            int n = compute_mandelbrot(f, c);
            f->pixel_data[py * f->width + px] = n;

        }
    }

}

void Fractal_destroy(Fractal* f) {
    free(f->pixel_data);
    free(f);
}
