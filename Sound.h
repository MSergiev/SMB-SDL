#ifndef SOUND_H
#define SOUND_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
using std::cerr;
using std::endl;

enum SFX
{
	SJUMPFX, LJUMPFX, BUMPFX, ONEUPFX,
   	COINFX, BREAKFX, FIREBALLFX, FALLFX,
   	FLAGPOLEFX, GAMEOVERFX, FIREFX, KICKFX,
   	DEATHFX, PAUSEFX, PIPEFX, POWERUPFX,
   	UPFX, DOWNFX, STOMPFX, STAGECLEARFX,
   	WORLDCLEARFX 
};

enum Music
{
	OVERWORLD, UNDERWORLD, WATER, CASTLE
};

class Sound
{
public:
	Sound();
	bool load();
	void free();
	void play(SFX sound);
	void music(Music music);
	~Sound();

private:
	Uint32 timer;
	Mix_Chunk* sfx[25];
	Mix_Music* bgm[10];
};


#endif
