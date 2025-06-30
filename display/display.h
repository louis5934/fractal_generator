#ifndef DISPLAY_H
#define DISPLAY_H 1

__u_char* Display_load_image_png(const char* filename, int* width, int* height);

void Display_save_image_png(__u_char* image_rgb, int width, int height, const char* filename);

void Display_display_image(__u_char* image_rgb, int width, int height);

#endif