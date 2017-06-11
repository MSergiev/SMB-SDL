#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "Texture.h"
#include "Sound.h"
#include "Params.h"
using std::stringstream;
using std::setw;
using std::setfill;
using std::time;

class Text
{
public:
	int score, coins, mainW, subW, time;
	int oldLives;
	int mLives;
	bool mStart, restart;
	bool showTitle, showLives;
	
	Text();
	void drawHUD();
	void drawStatus();
	void drawTitle();
	void drawBegin();
	~Text();
private:
	Uint32 timer, restartTimer;
	TTF_Font* mFont;
	Texture tText;
};

#endif
