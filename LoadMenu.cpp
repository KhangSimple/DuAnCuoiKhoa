#include "LoadMenu.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

const int MENU_WIDTH=900;
const int MENU_HEIGHT=600;
const string MENU_TITLE="SNAKE GAME";
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_TOTAL
};

//The window we'll be rendering to
SDL_Window* MenuWindow = NULL;
//The surface contained by the window
SDL_Surface* MenuScreenSurface = NULL;

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The images that correspond to a keypress
SDL_Surface* MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* MenuCurrentSurface = NULL;

bool leavegame=false;

bool loadMediaMenu()
{
	//Loading success flag
	bool success = true;
    //Load default surface
	MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = IMG_Load( "img/Menu1.jpg" );
	if( MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load left surface
	MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_UP] = IMG_Load( "img/Menu1.jpg" );
	if( MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
	{
		printf( "Failed to load left image!\n" );
		success = false;
	}

	//Load right surface
	MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = IMG_Load( "img/Menu2.jpg" );
	if( MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
	{
		printf( "Failed to load right image!\n" );
		success = false;
	}

	return success;
}
bool initMenu()
{
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		MenuWindow = SDL_CreateWindow( MENU_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MENU_WIDTH,MENU_HEIGHT , SDL_WINDOW_SHOWN );
		if( MenuWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			MenuScreenSurface = SDL_GetWindowSurface( MenuWindow );
		}
	}
	return success;
}
void closeMenu()
{
	//Deallocate surface
	SDL_FreeSurface(MenuCurrentSurface);
	MenuCurrentSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( MenuWindow );
	MenuWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
void loadmenu(bool &check_menu)
{
    //Start up SDL and create window
	if( !initMenu() ){
		printf( "Failed to initialize!\n" );
	}
	else{
		//Load media
		if( !loadMediaMenu() ){
			printf( "Failed to load media!\n" );
		}
		else{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			MenuCurrentSurface = MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

			//While application is running
			while( !quit ){
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 ){
					//User requests quit
					if( e.type == SDL_QUIT ){
						quit = true;
						leavegame=true;
					}
					//User presses a key
					else if( e.type == SDL_KEYDOWN ){
						//Select surfaces based on key press
						switch( e.key.keysym.sym ){

							case SDLK_UP:
							MenuCurrentSurface = MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
							break;

							case SDLK_DOWN:
							MenuCurrentSurface = MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN];
							break;

                            case SDLK_KP_ENTER:
                                quit=true;
                                if(MenuCurrentSurface==MenuKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]||MenuCurrentSurface==MenuKeyPressSurfaces[KEY_PRESS_SURFACE_UP]) check_menu=true;
                                break;
                            case SDLK_RETURN:
                                quit=true;
                                if(MenuCurrentSurface==MenuKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]||MenuCurrentSurface==MenuKeyPressSurfaces[KEY_PRESS_SURFACE_UP]) check_menu=true;
                                break;
							default:
							MenuCurrentSurface = MenuKeyPressSurfaces[ KEY_PRESS_SURFACE_UP];
							break;
						}
					}

				}

				//Apply the current image
				SDL_BlitSurface( MenuCurrentSurface, NULL, MenuScreenSurface, NULL );

				//Update the surface
				SDL_UpdateWindowSurface( MenuWindow );
			}
		}
	}
	closeMenu();
}
bool isLeaveGame()
{
    return leavegame;
}

