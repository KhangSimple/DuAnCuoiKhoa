#include <Sound.h>

int loadSound(Mix_Music* music,int loops){
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
		return -1;
	}
	if (music == NULL)
	{
		printf("%s", Mix_GetError());
	}
    if (!Mix_PlayingMusic())
        Mix_PlayMusic(music, loops);
}
int loadEffectSound(Mix_Chunk* chunk){
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
		return -1;
	}
	if (chunk == NULL)
	{
		printf("%s", Mix_GetError());
	}
	if (!Mix_Playing(-1))
        Mix_PlayChannel(-1, chunk, 0);
}
