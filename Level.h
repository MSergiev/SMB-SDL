#ifndef LEVEL_H
#define LEVEL_H

#include "Params.h"
#include "Texture.h"

class Level
{
public:
	int length, palette, flagpole;
	Layout layout;
	Level(Texture& mTileset);
	void render(int scroll=0);
	void blockCollision(int posX, int posY);
	void toTXT();
	~Level();

private:
	int world, level, bgRepeat;
	Uint32 animationTimer;
	Texture& mTileset;
	SDL_Color bgColor; 
	void generate();
	void createFlagpole();
	void createCastle(int height);
};

#endif
