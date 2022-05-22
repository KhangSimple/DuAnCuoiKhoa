#include "Sound.h"
vector<Mix_Music*> music;
vector<Mix_Chunk*> chunk;

int loadSound(const char* filename){
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
		return -1;
	}
	music.push_back(Mix_LoadMUS(filename));
	if (music[music.size()-1] == NULL)
	{
		printf("%s", Mix_GetError());
	}
	//music.push_back(music_);
    if (!Mix_PlayingMusic())
        Mix_PlayMusic(music[music.size()-1], 0);
}
int loadEffectSound(const char* filename){
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
		return -1;
	}
	//Mix_Chunk* chunk = NULL;
    chunk.push_back(Mix_LoadWAV(filename));
	if (chunk[chunk.size()-1] == NULL)
	{
		printf("%s", Mix_GetError());
	}
	//if (!Mix_Playing(-1))
    Mix_PlayChannel(-1, chunk[chunk.size()-1], 0);
}
