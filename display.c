#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "display.h"

__u_char* Display_load_image_png(const char* filename, int* width, int* height) {
            
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Error SDL2_image Initialization");
        exit(EXIT_FAILURE);
    }

    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        fprintf(stderr, "IMG_Load Error: %s\n", IMG_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    __u_char* image_rgb = malloc(surface->w * surface->h * 3);
    if (!image_rgb) {
        fprintf(stderr, "Memory allocation error\n");
        SDL_FreeSurface(surface);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (surface->format->BytesPerPixel == 4) {
        for (int i = 0; i < surface->w * surface->h; i++) {
            image_rgb[i * 3] = ((__u_char*)surface->pixels)[i * 4];
            image_rgb[i * 3 + 1] = ((__u_char*)surface->pixels)[i * 4 + 1];
            image_rgb[i * 3 + 2] = ((__u_char*)surface->pixels)[i * 4 + 2];
        }
    } else {
        memcpy(image_rgb, surface->pixels, surface->w * surface->h * 3);
    }

    *width = surface->w;
    *height = surface->h;

    SDL_FreeSurface(surface);
    IMG_Quit();
    SDL_Quit();

    return image_rgb;
}

void Display_save_image_png(__u_char* image_rgb, int width, int height, const char* filename) {
    
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(image_rgb, width, height, 24, width * 3, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
    if (!surface) {
        fprintf(stderr, "SDL_CreateRGBSurfaceFrom Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (IMG_SavePNG(surface, filename) != 0) {
        fprintf(stderr, "IMG_SavePNG Error: %s\n", IMG_GetError());
        SDL_FreeSurface(surface);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(surface);
    SDL_Quit();

}

void Display_display_image(__u_char* image_rgb, int width, int height) {
        
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Error SDL2_image Initialization");
        exit(EXIT_FAILURE);
    }

    SDL_Window* window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Error window creation");
        exit(EXIT_FAILURE);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error renderer creation");
        exit(EXIT_FAILURE);
    }

    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(image_rgb, width, height, 24, width * 3, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);
    if (!surface) {
        fprintf(stderr, "SDL_CreateRGBSurfaceFrom Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Error creating texture");
        exit(EXIT_FAILURE);
    }

    while (1) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    IMG_Quit();
    SDL_Quit();

}
