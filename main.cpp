#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Level.h"
#include "Player.h"
#include "Params.h"
using namespace std;

bool init();
bool loadMedia();
void close();
void eventHandler(SDL_Event&);
inline int getScroll();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture gTileset(gRenderer);
Texture gPlayerSprites(gRenderer);
Level level(gTileset);
Player player(gPlayerSprites);
int completion;
bool quit = false;

int main(int argc, char* argv[]){
	if(!init()) cerr << "Init failed" << endl;
	else {
		int countedFrames = 0;
		Uint32 timer;
		gTileset = Texture(gRenderer);
		gPlayerSprites = Texture(gRenderer);
		cout << "----" << endl;
		level.toTXT();
		player.layout = &level.layout;
		if(!loadMedia()) cerr << "Tileset loading failed" << endl;
		else{
			SDL_RenderSetScale(gRenderer, 2.5, 2.5);
			SDL_Event e;
			while(!quit){
				timer = SDL_GetTicks();
				eventHandler(e);
				player.eventHandler();
				float avg = countedFrames/((SDL_GetTicks()-timer)/1000.f);
				if(avg>2000000) avg = 0;
				level.render(getScroll());
				player.render();
				SDL_RenderPresent(gRenderer);
				++countedFrames;
				int frameTicks = SDL_GetTicks()-timer;
				if(frameTicks<TICKS_PER_FRAME) SDL_Delay(TICKS_PER_FRAME-frameTicks);
			}
		}
	}
	close();
	return 0;
}

int getScroll(){
	//if(player.mPosX>64&&player.mPosX<level.flagpole*16-128){ player.scroll=false; return player.mPosX;}
	player.scroll=true;
	//if(player.mPosX<=64) return 64;
	//return (level.flagpole*16-128);
	return player.mPosX;
}

bool init(){
	bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO)<0){
	   	cerr << "SDL error: " << SDL_GetError() << endl;
		success = false;
	} else {
		//if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) cerr << "Linear filtering not enabled" << endl;
		gWindow = SDL_CreateWindow("SMB", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
				WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if(gWindow==NULL){
		   	cerr << "Window error: " << SDL_GetError() << endl;
			success = false;
		} else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer==NULL){
				cerr << "Render error: " << SDL_GetError() << endl;
				success = false;
			} else {
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags) & imgFlags)){
					cerr << "Image error: " << IMG_GetError() << endl;
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	if(!gTileset.loadFromFile("GFX/tileset.png")){
		cerr << "Tileset error" << endl;
		success = false;
	}
	if(!gPlayerSprites.loadFromFile("GFX/player.png")){
		cerr << "Spritesheet error" << endl;
		success = false;
	}
	return success;
}

void eventHandler(SDL_Event& e)
{
	while(SDL_PollEvent(&e)!=0){
		if(e.type==SDL_QUIT) quit = true;
		if(e.type==SDL_KEYDOWN){
		switch(e.key.keysym.sym){
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
		}
	}
}

void close(){
	gTileset.free();
	gPlayerSprites.free();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;
	IMG_Quit();
	SDL_Quit();
}
