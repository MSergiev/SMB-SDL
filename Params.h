#ifndef PARAMS_H
#define PARAMS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <pugixml.hpp>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::fstream;

#include "Texture.h"
#include "Sound.h"
#include "Text.h"

#define WIDTH 600
#define HEIGHT 600
#define LHEIGHT 14
#define LLENGTH 250
#define BLOCK 16
#define VEL 2
#define MAX_VEL 2
#define ZERO HEIGHT/2-(LHEIGHT*BLOCK)/3-10
#define FPS 60
#define TICKS_PER_FRAME 1000/FPS
#define OFFSET BLOCK*2
#define MLENGTH LLENGTH
#define MHEIGHT LHEIGHT+4
#define GRAVITY 9.8

enum Item
{ 
	NOTHING, COIN, MUSHROOM, STAR, ONEUP
};

struct Block
{
	Block(bool exists = false, bool passThrough = true,
		   	int texX = 0, int texY = 0, Item contains = NOTHING,
		   	bool breakable = false, bool animated = false,
			int frames = 0,
			int nextFrameX = 0, int nextFrameY = 0 ){
		this->exists=exists;
		this->passThrough=passThrough;
		this->texX=texX;
		this->texY=texY;
		this->initX=texX;
		this->initY=texY;
		this->contains=contains;
		this->breakable=breakable;
		this->animated=animated;
		this->frames=frames;
		this->nextFrameX=nextFrameX;
		this->nextFrameY=nextFrameY;
	}
	bool exists;
	bool passThrough;
	int texX, texY;
	int initX, initY;
	Item contains;
	bool breakable;
	bool animated;
	int frames;
	int nextFrameX;
	int nextFrameY;
};

typedef std::vector< std::vector<Block> > Layout;

#include "Level.h"
#include "Player.h"

#endif
