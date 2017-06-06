#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <pugixml.hpp>
#include "Texture.h"
#include "Params.h"

class Level
{
public:
	int length, palette, flagpole;
	//Block map[LHEIGHT+2][LLENGTH];
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
