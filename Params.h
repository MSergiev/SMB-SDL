#ifndef PARAMS_H
#define PARAMS_H

#define WIDTH 800
#define HEIGHT 600
#define LHEIGHT 14
#define LLENGTH 250
#define VEL 2
#define MAX_VEL 4
#define ZERO HEIGHT/2-(LHEIGHT*16)/3-10
#define FPS 60
#define TICKS_PER_FRAME 1000/FPS
#define OFFSET 32
#define MLENGTH LLENGTH
#define MHEIGHT LHEIGHT+4

#include <vector>

enum Item
{ 
	NOTHING, COIN, MUSHROOM, STAR, ONEUP
};

struct Coords
{
	Coords(int x, int y){
		this->x=x;
		this->y=y;
	}
	int x, y;
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
#endif
