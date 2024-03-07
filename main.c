#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

//void wait(int milliseconds){
//	clock_t start_time = clock();
//	while(clock() < start_time + milliseconds){
//		printf("Waiting\n");
//	}
//	return;
//}

struct Color{
	int r;
	int g;
	int b;
	int a;
};

struct Rect{
	int x;
	int y;
	int w;
	int h;
};

int main(int argc, char *argv[]) {
	// Initialize SDL
  	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    	printf("SDL_Init failed\n");
		return 1;
  	}

	int screen_width = 640;
	int screen_height = 480;

  	// Create a window
  	SDL_Window *window = SDL_CreateWindow("SDL Testing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
  	if (window == NULL) {
		printf("Creating SDL window failed\n");
    	return 1;
  	}	

  	// Create a renderer
  	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  	if (renderer == NULL) {
		printf("Creating SDL_Renderer failed\n");
    	return 1;
  	}

  	// Set the renderer's draw color to red
  	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  	// Clear the screen
  	SDL_RenderClear(renderer);

  	// Display the window
  	SDL_RenderPresent(renderer);

	struct Color bc = { 0, 0, 0, 255 };

	struct Color rc = { 255, 0, 0, 255 };

	struct Rect r = { 0, 0, 50, 50 };

	int x_vel = 1;
	int y_vel = 1;

  	// Wait for a key press
	// This exits 
  	SDL_Event event;
  	while (1) {
		if(SDL_PollEvent(&event)){
	    	if (event.type == SDL_QUIT) {
    	  		break;
    		}
		}

		//logic
		r.x += x_vel;
		r.y += y_vel;

		if(r.x <= 0 || r.x + r.w >= screen_width){
			x_vel *= -1;
		}

		if(r.y <= 0 || r.y + r.h >= screen_height){
			y_vel *= -1;
		}		
		
		//drawing
		SDL_SetRenderDrawColor(renderer, bc.r, bc.g, bc.b, bc.a);
		SDL_RenderClear(renderer);
		
		SDL_SetRenderDrawColor(renderer, rc.r, rc.g, rc.b, rc.a ); 
		SDL_Rect rect = { r.x, r.y, r.w, r.h };
		SDL_RenderFillRect(renderer, &rect);	

		SDL_RenderPresent(renderer);

		sleep(1);
  	}

  	// Destroy the window and renderer
  	SDL_DestroyWindow(window);
  	SDL_DestroyRenderer(renderer);

  	// Quit SDL
  	SDL_Quit();

  	return 0;
}
