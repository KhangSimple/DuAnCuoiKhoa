#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>

int loadSound(Mix_Music* music,int loops);
int loadEffectSound(Mix_Chunk* chunk);

#endif // SOUND_H_INCLUDED
