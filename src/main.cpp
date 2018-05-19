#include <switch.h>
#include <iostream>
#include <unistd.h>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char **argv)
{
	 SDL_Init(SDL_INIT_EVERYTHING);
   
    //Switch screen size: 720p. Must set to full screen.
    SDL_Window* window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!window)
        SDL_Quit();
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer)
        SDL_Quit();

	//set default/startup screen
	SDL_SetRenderDrawColor(renderer, 20, 40, 60, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	

	while(appletMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS){
			SDL_Quit(); //shut down SDL2 thingy
			break; // break in order to return to hbmenu
		}
		
		if (kDown & KEY_A)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //white
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		
		}

		if (kDown & KEY_B)
		{
			SDL_SetRenderDrawColor(renderer, 255, 42, 0, 255); //red
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		}
		
		if (kDown & KEY_X)
		{
			SDL_SetRenderDrawColor(renderer, 46, 255, 0, 255); //green
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		}
		
		if (kDown & KEY_Y)
		{
			SDL_SetRenderDrawColor(renderer, 16, 0, 255, 255); //blue
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		}

	}

	return 0;
}

