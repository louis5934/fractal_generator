#include <stdlib.h>
#include <stdio.h>
#include "color.h"

Color Color_interpolate(Color c1, Color c2, float t) {

    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    __u_char r = c1.r + (c2.r - c1.r) * t;
    __u_char g = c1.g + (c2.g - c1.g) * t;
    __u_char b = c1.b + (c2.b - c1.b) * t;

    return (Color) {r, g, b};

}   

typedef struct Gradient_s {
    Color* colors;
    float* marks;
    int size;
} Gradient;

Gradient* Gradient_create(Color* colors, float* marks, int size) {

    // size has to be greater than 2
    
    Gradient* g = malloc(sizeof(Gradient));
    g->colors = malloc(size * sizeof(Color));
    g->marks = malloc((size - 2) * sizeof(float));
    g->size = size;

    for (int i = 0; i < size; i++) g->colors[i] = colors[i];
    for (int i = 0; i < size - 2; i++) g->marks[i] = marks[i];

    return g;

}

void Gradient_destroy(Gradient* g) {
    free(g->colors);
    free(g->marks);
    free(g);
}

Gradient* Gradient_create_default() {

    Color* colors = malloc(2 * sizeof(Color));
    colors[0] = (Color) {0, 0, 0};
    colors[1] = (Color) {255, 255, 255};

    return Gradient_create(colors, NULL, 2);

}

Color Gradient_get_color(Gradient* g, float t) {

    if (t <= 0.0f) return g->colors[0];
    if (t >= 1.0f) return g->colors[g->size - 1];

    for (int i = 0; i < g->size - 2; i++) {
        if (g->marks[i] < t) continue;
        float tp = (t - g->marks[i-1]) / (g->marks[i] - g->marks[i-1]);
        return Color_interpolate(g->colors[i], g->colors[i+1], tp);
    }

    float tp = (t - g->marks[g->size-3]) / (1 - g->marks[g->size-3]);
    return Color_interpolate(g->colors[g->size-2], g->colors[g->size-1], tp);

}
