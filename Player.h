#ifndef PLAYER_H
#define PLAYER_H

#include "Texture.h"
#include "Sound.h"
#include "Params.h"

class Player
{
public:
	Player();
	void eventHandler();
	void render();
	Block& getBlock(int x, int y);
	void blockCollide(int x, int y);
	~Player();

	Uint32 accelTimer, jumpTimer, restartTimer;
	Layout* layout;
	bool up, down, left, right;
	bool oUp, oDown, oLeft, oRight;
	bool scroll, accelerate, jumped;
	bool mushroom, flower, star;
	bool run;
	bool restart, mDeath;
	int starCounter;
	int mPosX, mPosY;
	int mVelX, mVelY;
	int oldVelX;
	SDL_RendererFlip flip;
};

#endif
