#include "Sound.h"

Sound::Sound() 
{
	if(!load())
		cerr << "Sound loading failed" << endl;
}

void Sound::free() 
{
	for (int i = 0; i < 25; i++) {
		Mix_FreeChunk(sfx[i]);
		sfx[i] = NULL;
	}

	for (int i = 0; i < 10; i++) {
		Mix_FreeMusic(bgm[i]);
		bgm[i] = NULL;
	}
	
	Mix_Quit();	
}

void Sound::play(SFX sound) 
{
	switch(sound){
		case BUMPFX:
			Mix_PlayChannel(-1, sfx[0], 0);
			break;
		case SJUMPFX:
			Mix_PlayChannel(-1, sfx[1], 0);
			break;
		case LJUMPFX:
			Mix_PlayChannel(-1, sfx[2], 0);
			break;
		case ONEUPFX:
			Mix_PlayChannel(-1, sfx[3], 0);
			break;
		case COINFX:
			Mix_PlayChannel(-1, sfx[4], 0);
			break;
		case BREAKFX:
			Mix_PlayChannel(-1, sfx[5], 0);
			break;
		case FIREBALLFX:
			Mix_PlayChannel(-1, sfx[6], 0);
			break;
		case FALLFX:
			Mix_PlayChannel(-1, sfx[7], 0);
			break;
		case FLAGPOLEFX:
			Mix_PlayChannel(-1, sfx[8], 0);
			break;
		case GAMEOVERFX:
			Mix_PlayChannel(-1, sfx[9], 0);
			break;
		case FIREFX:
			Mix_PlayChannel(-1, sfx[10], 0);
			break;
		case KICKFX:
			Mix_PlayChannel(-1, sfx[11], 0);
			break;
		case DEATHFX:
			Mix_PlayChannel(-1, sfx[12], 0);
			break;
		case PAUSEFX:
			Mix_PlayChannel(-1, sfx[13], 0);
			break;
		case PIPEFX:
			Mix_PlayChannel(-1, sfx[14], 0);
			break;
		case POWERUPFX:
			Mix_PlayChannel(-1, sfx[15], 0);
			break;
		case UPFX:
			Mix_PlayChannel(-1, sfx[16], 0);
			break;
		case DOWNFX:
			Mix_PlayChannel(-1, sfx[17], 0);
			break;
		case STOMPFX:
			Mix_PlayChannel(-1, sfx[18], 0);
			break;
		case STAGECLEARFX:
			Mix_PlayChannel(-1, sfx[19], 0);
			break;
		case WORLDCLEARFX:
			Mix_PlayChannel(-1, sfx[20], 0);
			break;
	}
}

void Sound::music(Music music){
	switch(music){
		case OVERWORLD:
			Mix_PlayMusic(bgm[0], -1);
			break;
		case UNDERWORLD:
			Mix_PlayMusic(bgm[1], -1);
			break;
		case WATER:
			Mix_PlayMusic(bgm[2], -1);
			break;
		case CASTLE:
			Mix_PlayMusic(bgm[3], -1);
			break;
	}
}

Sound::~Sound() 
{
	free();
}

bool Sound::load() 
{
	bool success = true;
	if(SDL_Init(SDL_INIT_AUDIO)<0){
		cerr << "SDL Audio error: " << SDL_GetError() << endl;
		success = false;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0){
		cerr << "Audio error: " << Mix_GetError() << endl;
		success = false;
	}

	sfx[0] = Mix_LoadWAV("SFX/smb_bump.wav");
	sfx[1] = Mix_LoadWAV("SFX/smb_jump-small.wav");
	sfx[2] = Mix_LoadWAV("SFX/smb_jump-super.wav");
	sfx[3] = Mix_LoadWAV("SFX/smb_1-up.wav");
	sfx[4] = Mix_LoadWAV("SFX/smb_coin.wav");
	sfx[5] = Mix_LoadWAV("SFX/smb_breakblock.wav");
	sfx[6] = Mix_LoadWAV("SFX/smb_fireball.wav");
	sfx[7] = Mix_LoadWAV("SFX/smb_bowserfalls.wav");
	sfx[8] = Mix_LoadWAV("SFX/smb_flagpole.wav");
	sfx[9] = Mix_LoadWAV("SFX/smb_gameover.wav");
	sfx[10] = Mix_LoadWAV("SFX/smb_bowserfire.wav");
	sfx[11] = Mix_LoadWAV("SFX/smb_kick.wav");
	sfx[12] = Mix_LoadWAV("SFX/smb_mariodie.wav");
	sfx[13] = Mix_LoadWAV("SFX/smb_pause.wav");
	sfx[14] = Mix_LoadWAV("SFX/smb_pipe.wav");
	sfx[15] = Mix_LoadWAV("SFX/smb_powerup_appears.wav");
	sfx[16] = Mix_LoadWAV("SFX/smb_powerup.wav");
	sfx[17] = Mix_LoadWAV("SFX/smb_pipe.wav");
	sfx[18] = Mix_LoadWAV("SFX/smb_stomp.wav");
	sfx[19] = Mix_LoadWAV("SFX/smb_stage_clear.wav");
	sfx[20] = Mix_LoadWAV("SFX/smb_world_clear.wav");

	bgm[0] = Mix_LoadMUS("SFX/01-overworld.mp3");
	bgm[1] = Mix_LoadMUS("SFX/02-underworld.mp3");
	bgm[2] = Mix_LoadMUS("SFX/03-underwater.mp3");
	bgm[3] = Mix_LoadMUS("SFX/04-castle.mp3");

	for(int i = 0; i < 21; ++i){
		if(sfx[i]==NULL){
			cerr << "SFX error: " << Mix_GetError() << endl;
			success = false;
		}
	}
	
	for(int i = 0; i < 4; ++i){
		if(bgm[i]==NULL){
			cerr << "BGM error: " << Mix_GetError() << endl;
			success = false;
		}
	}
	return success;
}

