#include "Text.h"

Text::Text(SDL_Renderer* mRenderer, Texture* mTileset)
:tScore(Texture(mRenderer)){
	if(TTF_Init()==-1){
		cerr << "TTF error: " << TTF_GetError() << endl;
	}
	score = 0;
	coins = 0; 
	mainW = 1;
	subW = 1;
	time = 360;
	timer = SDL_GetTicks()/1000;
	this->mRenderer=mRenderer;
	this->mTileset=mTileset;
	this->mFont=TTF_OpenFont("GFX/emulogic.ttf", 8);
	tScore.mFont = mFont;
}

void Text::drawHUD(){
	int height = 6;
	if(showHUD){
		time-=(SDL_GetTicks()/1000)-timer;
		timer = SDL_GetTicks()/1000;
		SDL_Color color = {255, 255, 255, 255};
		stringstream str;
		str << "MARIO" << setw(15) << std::right << "WORLD" << setw(6) << "TIME";
		tScore.loadFromRenderedText(str.str().c_str(), color);
		tScore.render(16, height);
		str.str(string());
		str << setw(6) << setfill('0') << score; 
		str << setfill(' ') << setw(5) << "x" << std::right << setw(2) << setfill('0') << coins;
		str << setfill(' ') << setw(4) << mainW << '-' << subW;
		str << setfill(' ') << setw(4) << "" << std::right << setw(3) << setfill('0') << time;
		tScore.loadFromRenderedText(str.str().c_str(), color);
		tScore.render(16, height+10);
		SDL_Rect coinIcon = {(((int)SDL_GetTicks()/500)%3)*8, 38*16, 8, 8};
		mTileset->render(89, 18, &coinIcon);
	}
}

void Text::drawMenu(){

}

void Text::drawBegin(){

}

Text::~Text(){
	TTF_CloseFont(mFont);
	mFont = NULL;
	tScore.free();
	TTF_Quit();
}

