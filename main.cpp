#include <stdio.h>
#include <SDL.h>

// Initializes SDL and creates a window.
bool init();

// Loads media to window
bool loadMedia();

// Frees media and closes SDL, releasing all associated memory
void close();

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* imageToLoad = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


bool init() {
  bool success = true;
  if (SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf("SDL could not initialize, SDL_ERROR: %s\n", SDL_GetError());
  }
  else {
    window = SDL_CreateWindow( "Starfall", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
      printf("Window could not be created, SDL_ERROR: %s\n", SDL_GetError());
    }
    else {
      screenSurface = SDL_GetWindowSurface(window);
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  imageToLoad = SDL_LoadBMP( "assets/test.bmp" );
  if (imageToLoad == NULL) {
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(imageToLoad);
  imageToLoad = NULL;

  SDL_DestroyWindow(window);
  window = NULL;

  SDL_Quit();
}


int main(int argc, char* args[]) {
  if (!init()) {
    printf("Failure to initialize window\n");
  }
  else {
    if (!loadMedia()) {
      printf("Failure to load media\n");
    }
    else {
      SDL_BlitSurface(imageToLoad, NULL, screenSurface, NULL);
      SDL_UpdateWindowSurface(window);
      SDL_Event e;
      bool quit = false;
      while (quit == false) {
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }
      }
      close();
      return 0;
    }
  }
}
