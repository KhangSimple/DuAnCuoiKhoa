#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
#include "Text.h"
#include "Snake.h"
#undef main
using namespace std;
int x=130;
int y=100;
int sizeOfText=40;

int LoadMask()
{
    std::string Text="YOUR SCORE:";
    std::stringstream ss;
    ss<<getScore();
    std::string s;
    ss>>s;
    Text+=s;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool isRunning = true;
	SDL_Event mainEvent;
	TTF_Font* font = NULL;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	//initializes  the subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING)<0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		//return -1;
	}

	//Initialize the truetype font API.
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
		//return -1;
	}

	//Create window
	window = SDL_CreateWindow("SCORE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600,300, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		//return -1;
	}

	//create a renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Could not create render %s", SDL_GetError());
		//return -1;
	}
	Painter painter(window, renderer);
    painter.clearWithBgColor(MEDIUMPURPLE3_COLOR);
	font = TTF_OpenFont("mono0755.ttf", sizeOfText);

	SDL_Color fg = { 255, 255, 0 };

	std::string text = Text;
	surface = TTF_RenderText_Solid(font, text.c_str(), fg);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect srcRest;
	SDL_Rect desRect;
	TTF_SizeText(font, text.c_str(), &srcRest.w, &srcRest.h);

	srcRest.x = 0;
	srcRest.y =  0;

	desRect.x = x;
	desRect.y = y;

	desRect.w = srcRest.w;
	desRect.h = srcRest.h;

	//set background color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//main loop
	while (isRunning)
	{
		//main event
		while (SDL_PollEvent(&mainEvent))
		{
			switch (mainEvent.type)
			{
				//User - requested quit
				case SDL_QUIT:
				{
					isRunning = false;
					break;
				}
				default:
				{
					break;
				}
			}
		}
		// clear the window to black
		//SDL_RenderClear(renderer);
		//Copy a portion of the texture to the current rendering target.
		SDL_RenderCopy(renderer, texture, &srcRest, &desRect);
		//draw to screen
		SDL_RenderPresent(renderer);
		SDL_Delay(2000);
		isRunning = false;
	}
	//Destroy a window.
	SDL_DestroyWindow(window);
	//Destroy a renderer
	SDL_DestroyRenderer(renderer);
	//Shutdown and cleanup the truetype font API.
	TTF_Quit();
	//cleans up all initialized subsystems
	SDL_Quit();
	//return 0;
}
