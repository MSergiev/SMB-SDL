#ifndef TEXT_H
#define TEXT_H

#include "Params.h"
#include <SDL2/SDL_ttf.h>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "Texture.h"
using std::stringstream;
using std::setw;
using std::setfill;
using std::time;

class Text
{
public:
	int score, coins, mainW, subW, time;
	bool showHUD, showMenu, showBegin;
	Text(SDL_Renderer* mRenderer, Texture* mTileset);
	void drawHUD();
	void drawMenu();
	void drawBegin();
	~Text();
private:
	SDL_Renderer* mRenderer;
	Uint32 timer;
	Texture* mTileset;
	TTF_Font* mFont;
	Texture tScore;
};

#endif
