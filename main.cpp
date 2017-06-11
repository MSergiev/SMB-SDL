#include "Params.h"
#include "Texture.h"

bool init();
bool loadMedia();
void close();
void eventHandler(SDL_Event&);
inline int getScroll();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Renderer* renderer;
Texture* tileset;
Texture* playerSprites;
Texture* title;
bool* start;
bool* death;
int* lives;

Texture gTileset(gRenderer);
Texture gPlayerSprites(gRenderer);
Texture gTitle(gRenderer);
Level level;
Player player;
int completion;
bool quit = 0;
bool  *showTitle, *showLives;
Uint32 restartTimer;


int main(int argc, char* argv[]){
	if(!init()) cerr << "Init failed" << endl;
	else {
		renderer = gRenderer;
		Text hud;
		int countedFrames = 0;
		Uint32 timer;
		gTileset = Texture(gRenderer);
		gPlayerSprites = Texture(gRenderer);
		gTitle = Texture(gRenderer);
		showTitle = &hud.showTitle;
		showLives = &hud.showLives;
		player.layout = &level.layout;

		tileset = &gTileset;
		playerSprites = &gPlayerSprites;
		title = &gTitle;
		start = &hud.mStart;
		death = &player.mDeath;
		lives = &hud.mLives;

		if(!loadMedia()) cerr << "Tileset loading failed" << endl;
		else{
			SDL_RenderSetScale(gRenderer, 2.5, 2.5);
			SDL_Event e;
			while(!quit){
				timer = SDL_GetTicks();
				eventHandler(e);
				player.eventHandler();
				SDL_RenderClear(gRenderer);
				level.render(player.mPosX);
				player.render();
				hud.drawHUD();
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

bool init(){
	bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO)<0){
	   	cerr << "SDL error: " << SDL_GetError() << endl;
		success = false;
	} else {
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
	if(!gTitle.loadFromFile("GFX/title.png")){
		cerr << "Title error" << endl;
		success = false;
	}
	if(!Sound::load()){
		cerr << "Sound error" << endl;
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
			case SDLK_RETURN:
				*showTitle = 0;
				break;
			case SDLK_t:
				level.toTXT();
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
