#include <iostream>
#include<stdio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <SDL.h>
#include <SDL_image.h>

#include "painter.h"
#include "PlayGround.h"
#include "Gallery.h"
#include "Text.h"
#include "LoadMenu.h"
#include "Snake.h"
#include "HighScore.h"
#include "Sound.h"
using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Snake Game";
const string GAMEOVER_TITLE = "Snake Game";

const int GROUND_WIDTH = 30;
const int GROUND_HEIGHT = 20;
const int CELL_SIZE = 30;

const int GAMEOVER_WIDTH=800;
const int GAMEOVER_HEIGHT=600;

const double STEP_DELAY = 0.15;

#define CLOCK_NOW chrono::system_clock::now
typedef chrono::duration<double> ElapsedTime;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

void renderSplashScreen();
void renderGamePlay(Painter&, const PlayGround& playGround);
void renderGameOver(bool &check);
UserInput interpretEvent(SDL_Event e);
void updateRankingTable(const PlayGround& playGround);
void loadBkGround();
void render_MenuGame();
void close();
bool loadMedia();
bool init();

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

Gallery* gallery = nullptr; // global picture manager

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

SDL_Surface* gBkGround = NULL;

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;



int main(int argc, char* argv[])
{
    //Game Loop

    do{
        // check_menu use to check player choose "Play" or "HighScore"
        bool check_menu=false;
        loadmenu(check_menu);
        if(isLeaveGame()) return 0;
        if(!check_menu){
            LoadHighScore();
            continue;
        }
        //  Variable re_play is used to check if the player wants to play again?
        bool re_play;
        do{
            //int m = loadMusic("sound/BkMusic.mp3");
            re_play=false;
            // Reset score after play again
            resetScore();
            srand(time(0));
            SDL_Window* window;
            SDL_Renderer* renderer;
            initSDL(window, renderer);
            Painter painter(window, renderer);
            gallery = new Gallery(painter);
            //renderSplashScreen(); // Wait key
            PlayGround playGround(GROUND_WIDTH, GROUND_HEIGHT);
            SDL_Event e;
            auto start = CLOCK_NOW();
            renderGamePlay(painter, playGround);
            Mix_ResumeMusic();
            loadSound((char*)"sound/BkMusic.mp3");
            while (playGround.isGameRunning()){
                // Load BackGround Music
                while (SDL_PollEvent(&e)) {
                    UserInput input = interpretEvent(e);
                    playGround.processUserInput(input);
                }
                auto end = CLOCK_NOW();
                ElapsedTime elapsed = end-start;
                if (elapsed.count() > STEP_DELAY) {
                    playGround.nextStep();
                    renderGamePlay(painter, playGround);
                    start = end;
                }
                SDL_Delay(1);
            }
            // Pause music
            Mix_HaltMusic();
            // Load Game Over Sound
            loadEffectSound("sound/gameover.wav");
            SDL_Delay(1000);
            //shut window game
            quitSDL(window, renderer);
            // Show score
            LoadMask();
            // Game over window
            renderGameOver(re_play);
            close();
        }while(re_play);
    }while(!isLeaveGame());
    // release picture
    delete gallery;
    //quitSDL(window, renderer);
    return 0;
}
bool loadMedia()
{
	//Loading success flag
	bool success = true;
    //Load default surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = IMG_Load( "img/gameover1.jpg" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load left surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = IMG_Load( "img/gameover1.jpg" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
	{
		printf( "Failed to load left image!\n" );
		success = false;
	}

	//Load right surface
	gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = IMG_Load( "img/gameover2.jpg" );
	if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
	{
		printf( "Failed to load right image!\n" );
		success = false;
	}

	return success;
}
bool init()
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
		gWindow = SDL_CreateWindow( GAMEOVER_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAMEOVER_WIDTH,GAMEOVER_HEIGHT , SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}
	return success;
}
void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    //SDL_Delay(1000);
    //Update the surface
    SDL_UpdateWindowSurface( gWindow );
    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void close()
{
	//Deallocate surface
	SDL_FreeSurface(gCurrentSurface);
	gCurrentSurface = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(1);
    }
}

float generateRandomNumber()
{
    return (float) rand() / RAND_MAX;
}

void renderSplashScreen()
{
    waitUntilKeyPressed();
}

void drawCherry(Painter& painter, int left, int top)
{
    SDL_Rect dst = { left+5, top+5, CELL_SIZE-10, CELL_SIZE-10 };
    painter.createImage(gallery->getImage(PIC_CHERRY), NULL, &dst);
}

void drawSnake(Painter& painter, int left, int top, vector<Position> pos)
{
    for (size_t i = 0; i < pos.size(); i++) {
        SDL_Rect dst = { left+pos[i].x*CELL_SIZE+1, top+pos[i].y*CELL_SIZE+1, CELL_SIZE-2, CELL_SIZE-2 };
        SDL_Texture* texture = NULL;
        if (i > 0) {
            if (pos[i].y == pos[i-1].y)
                texture = gallery->getImage(PIC_SNAKE_HORIZONTAL);
            else
                texture = gallery->getImage(PIC_SNAKE_VERTICAL);
        } else { // snake's head
            texture = gallery->getImage(PIC_SNAKE_HEAD);
        }
        painter.createImage(texture, NULL, &dst);
    }
}

void drawVerticalLine(Painter& painter, int left, int top, int cells)
{
    painter.setColor(YELLOW_COLOR);
    painter.setAngle(-90);
    painter.setPosition(left, top);
    painter.moveForward(cells * CELL_SIZE);
}

void drawHorizontalLine(Painter& painter, int left, int top, int cells)
{
    painter.setColor(YELLOW_COLOR);
    painter.setAngle(0);
    painter.setPosition(left, top);
    painter.moveForward(cells * CELL_SIZE);
}

void renderGamePlay(Painter& painter, const PlayGround& playGround)
{
    int top = 0, left = 0;
    int width = playGround.getWidth();
    int height = playGround.getHeight();
    painter.clearWithBgColor(LIME_COLOR);
    //Update the surface
    SDL_UpdateWindowSurface( gWindow );

    for (int i = 0; i <= width; i++)
        drawVerticalLine(painter, left+i*CELL_SIZE, top+0, height);

    for (int i = 0; i <= height; i++)
        drawHorizontalLine(painter, left+0, top+i * CELL_SIZE, width);

    const vector<vector<CellType> >& squares = playGround.getSquares();
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (squares[i][j] == CELL_CHERRY)
                drawCherry(painter, left+j*CELL_SIZE, top+i*CELL_SIZE);

    vector<Position> snakePositions = playGround.getSnakePositions();
    drawSnake(painter, left, top, snakePositions);

    SDL_RenderPresent(painter.getRenderer());
}

void renderGameOver(bool &check)
{
    //Start up SDL and create window
	if( !init() ){
		printf( "Failed to initialize!\n" );
	}
	else{
		//Load media
		if( !loadMedia() ){
			printf( "Failed to load media!\n" );
		}
		else{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Set default current surface
			gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

			//While application is running
			while( !quit ){
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 ){
					//User requests quit
					if( e.type == SDL_QUIT ){
						quit = true;
					}
					//User presses a key
					else if( e.type == SDL_KEYDOWN ){
						//Select surfaces based on key press
						switch( e.key.keysym.sym ){

							case SDLK_LEFT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
							break;

							case SDLK_RIGHT:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
							break;

                            case SDLK_KP_ENTER:
                                quit=true;
                                if(gCurrentSurface==gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]||gCurrentSurface==gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT]) check=true;
                                break;
                            case SDLK_RETURN:
                                quit=true;
                                if(gCurrentSurface==gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT]||gCurrentSurface==gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT]) check=true;
                                break;
							default:
							gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT];
							break;
						}
					}

				}

				//Apply the current image
				SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );

				//Update the surface
				SDL_UpdateWindowSurface( gWindow );
			}
		}
	}
}

UserInput interpretEvent(SDL_Event e)
{
    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_UP: return KEY_UP;
        case SDLK_DOWN: return KEY_DOWN;
        case SDLK_LEFT: return KEY_LEFT;
        case SDLK_RIGHT: return KEY_RIGHT;
        }
    }
    return NO_INPUT;
}

