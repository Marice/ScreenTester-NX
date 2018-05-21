#include <switch.h>
#include <iostream>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <math.h>

using namespace std;

int main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
   
    //Setup window
    SDL_Window* window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window) { SDL_Quit(); }
	
	//Setup renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) { SDL_Quit(); }

	//Make an image-surface and create texture
	SDL_Surface * image = SDL_LoadBMP("menubg.bmp");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
		
	//set default menuscreen
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL); //load image to screen
	SDL_RenderPresent(renderer);
	
	while(appletMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();
		u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS){
			SDL_Quit();
			break; // break in order to return to hbmenu
		}
		
		if (kDown & KEY_A)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		}

		if (kDown & KEY_B) //red
		{
			SDL_SetRenderDrawColor(renderer, 255, 42, 0, 255); SDL_RenderClear(renderer); SDL_RenderPresent(renderer); 
		}
		
		if (kDown & KEY_X) //green
		{
			SDL_SetRenderDrawColor(renderer, 46, 255, 0, 255); SDL_RenderClear(renderer); SDL_RenderPresent(renderer);
		}
		
		if (kDown & KEY_Y) //blue
		{
			SDL_SetRenderDrawColor(renderer, 16, 0, 255, 255); SDL_RenderClear(renderer); SDL_RenderPresent(renderer);
		}
		
		if (kDown & KEY_UP) //black
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); SDL_RenderClear(renderer); SDL_RenderPresent(renderer);
		}
		
		if (kDown & KEY_DOWN)
		{
			while (1) 
			{	
				hidScanInput();
				u32 kDownAbb = hidKeysDown(CONTROLLER_P1_AUTO);
				if (kDownAbb & KEY_DOWN){ break; } //abort the 'rapid random color cycle' mode
				if (kDownAbb & KEY_PLUS){ break; }
				if (kDownAbb & KEY_MINUS){ break; }
				
				int r = rand() % 255;
				int g = rand() % 255;
				int b = rand() % 255;
				
				SDL_SetRenderDrawColor(renderer, r, g, b, 255); //black
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);
			}
		}
		
		if (kDown & KEY_LEFT)
		{
			while (1) 
			{	
				hidScanInput();
				u32 kDownAbb = hidKeysDown(CONTROLLER_P1_AUTO);
				if (kDownAbb & KEY_LEFT){ break; } //abort the 'Rapid rgb' mode
				if (kDownAbb & KEY_PLUS){ break; }
				if (kDownAbb & KEY_MINUS){ break; }
				
				//flash rgb
				SDL_SetRenderDrawColor(renderer, 255, 42, 0, 255); SDL_RenderClear(renderer); SDL_RenderPresent(renderer);
				SDL_SetRenderDrawColor(renderer, 46, 255, 0, 255); SDL_RenderClear(renderer); SDL_RenderPresent(renderer);
				SDL_SetRenderDrawColor(renderer, 16, 0, 255, 255); SDL_RenderClear(renderer); SDL_RenderPresent(renderer);
			}
		}
				
		if (kDown & KEY_MINUS) //load menu image
		{
			SDL_RenderClear(renderer); SDL_RenderCopy(renderer, texture, NULL, NULL); SDL_RenderPresent(renderer);
		}

	}
	
	SDL_Quit();
	return 0;
}