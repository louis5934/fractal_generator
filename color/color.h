#ifndef COLOR_H
#define COLOR_H 1

typedef struct Color_s {
    __u_char r;
    __u_char g;
    __u_char b;
} Color;

Color Color_create(__u_char r, __u_char g, __u_char b);
void Color_destroy(Color* c);

Color Color_interpolate(Color c1, Color c2, float t);

typedef struct Gradient_s Gradient;

Gradient* Gradient_create(Color* colors, float* marks, int size);
void Gradient_destroy(Gradient* g);

Gradient* Gradient_create_default();

Color Gradient_get_color(Gradient* g, float t);


#endif