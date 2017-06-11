#include "Text.h"

Text::Text():tText(renderer){
	if(TTF_Init()==-1){
		cerr << "TTF error: " << TTF_GetError() << endl;
	}
	mStart = 0;
   	showLives = 0;
	score = 0;
	coins = 0; 
	mainW = 1;
	mLives = 3;
	subW = 1;
	oldLives = 0;
	time = 360;
	showTitle = 1;
	showLives = 1;
	timer = SDL_GetTicks()/1000;
	restart = 0;
	restartTimer = 40000;
	this->mFont=TTF_OpenFont("GFX/emulogic.ttf", 8);
	tText.mFont = mFont;
}

void Text::drawHUD(){
	if(oldLives > *lives) restart = 1;
	if(showTitle) drawTitle();
	else if(showLives || restart){
	   	restartTimer = SDL_GetTicks();
		showLives = 0;
		restart = 0;
	}

	if(SDL_GetTicks()-restartTimer<2000){
	   	drawBegin();
		*death = 0;
	} else if(!showTitle && !showLives && !(*death)){
		cout << showTitle << showLives << *death << endl;
	   	*start = 1;
		showLives = 0;
	}
	
	drawStatus();
	oldLives = *lives;
}

void Text::drawStatus(){
	int height = 6;
	if(*start) time-=(SDL_GetTicks()/1000)-timer;
	timer = SDL_GetTicks()/1000;
	SDL_Color color = {255, 255, 255, 255};
	stringstream str;
	str << "MARIO" << setw(15) << std::right << "WORLD" << setw(6) << "TIME";
	tText.loadFromRenderedText(str.str().c_str(), color);
	tText.render(16, height);
	str.str(string());
	str << setw(6) << setfill('0') << score; 
	str << setfill(' ') << setw(5) << "x" << std::right << setw(2) << setfill('0') << coins;
	str << setfill(' ') << setw(4) << mainW << '-' << subW;
	str << setfill(' ') << setw(4) << "" << std::right << setw(3) << setfill('0');
	if(*start) str << time;
	tText.loadFromRenderedText(str.str().c_str(), color);
	tText.render(16, height+10);
	SDL_Rect coinIcon = {(((int)SDL_GetTicks()/500)%3)*8, 38*16, 8, 8};
	tileset->render(89, 18, &coinIcon);
}

void Text::drawTitle(){
	title->render(33, 30);
	SDL_Color color = {255, 255, 255, 255};
	tText.loadFromRenderedText("PRESS ENTER", color);
	tText.render(75, 160);
}

void Text::drawBegin(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_Color color = {255, 255, 255, 255};
	if(*lives>0){
		stringstream str;
		str << "WORLD " << mainW << "-" << subW;
		tText.loadFromRenderedText(str.str().c_str(), color);
		tText.render(85, 80);
		str.str(string());
		str << "x " << setw(2) << std::right << *lives;
		tText.loadFromRenderedText(str.str().c_str(), color);
		tText.render(118, 110);
		SDL_Rect clip = {6*BLOCK, 2*BLOCK, BLOCK, BLOCK};
		playerSprites->render(95, 106, &clip);
	} else {
		tText.loadFromRenderedText("GAME OVER", color);
		tText.render(85, 110);
		Sound::play(GAMEOVERFX);
		showTitle = 1;
		*start = 0;
	}
}

Text::~Text(){
	TTF_CloseFont(mFont);
	mFont = NULL;
	tText.free();
	TTF_Quit();
}

