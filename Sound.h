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
	static bool load();
	static void pause();
	static bool playing();
	static void free();
	static void play(SFX sound);
	static void music(Music music);
	~Sound();

private:
	static Uint32 timer;
	static Mix_Chunk* sfx[25];
	static Mix_Music* bgm[10];
};


#endif
