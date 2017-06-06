#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "Texture.h"
#include "Params.h"

class Player
{
public:
	Player(Texture& mSpriteSheet);
	void eventHandler();
	void render();
	bool isFalling();
	Block& getFromIndex(int x, int y);
	void calculateGround();
	void blockCollide();
	~Player();

	Uint32 accelTimer, jumpTimer;
	Layout* layout;
	bool jumped;
	bool scroll;
	bool mushroom, flower, star;
	int starCounter;
	Texture& mSpriteSheet;
	int mPosX, mPosY;
	int mVelX, mVelY;
	int zero;
	SDL_RendererFlip flip;
};

#endif
