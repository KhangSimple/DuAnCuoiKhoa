#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

int loadSound(const char* filename);
int loadEffectSound(const char* filename);
#endif // SOUND_H_INCLUDED
