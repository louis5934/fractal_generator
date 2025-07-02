#include <stdio.h>
#include <stdlib.h>
#include "fractal/fractal.h"
#include "display/display.h"
#include "color/color.h"

int main() {

    int width = 640 * 2;
    int height = 480 * 2;

    Color* colors = malloc(4 * sizeof(Color));
    colors[0] = (Color) {0, 32, 182};
    colors[1] = (Color) {230, 251, 252};
    colors[2] = (Color) {233, 131, 0};
    colors[3] = (Color) {24, 24, 24};

    float* marks = malloc(2 * sizeof(float));
    marks[0] = 0.25f;
    marks[1] = 0.5f;

    
    Fractal* f = Fractal_create(width, height, 3);
    Fractal_set_max_iter(f, 100);
    Fractal_set_gradient(f, Gradient_create(colors, marks, 4));
    // Fractal_generate_julia(f, -0.4, 0.6);
    Fractal_set_center(f, -0.6, 0);
    Fractal_generate_mandelbrot(f);

    __u_char* image_rgb = Fractal_get_pixel_data(f);
    Display_save_image_png(image_rgb, width, height, "image/mandelbrot.png");
    free(image_rgb);

    Fractal_destroy(f);
    
    return 0;
}