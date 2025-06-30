#include <stdio.h>
#include <stdlib.h>
#include "fractal/fractal.h"
#include "display/display.h"

int main() {

    int width = 640 * 2;
    int height = 480 * 2;

    Fractal* f = Fractal_create(width, height, 3);
    Fractal_set_center(f, -0.6, 0);
    Fractal_set_max_iter(f, 100);
    Fractal_generate_mandelbrot(f);

    __u_char* image_rgb = Fractal_get_pixel_data(f);
    Display_save_image_png(image_rgb, width, height, "image/mandelbrot.png");
    free(image_rgb);

    Fractal_destroy(f);
    
    return 0;
}