#include "Texture.h"

Texture::Texture(SDL_Renderer* mRenderer) 
{
	this->mRenderer = mRenderer;
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture() 
{
	free();
}

bool Texture::loadFromFile(string path) 
{
	SDL_Texture* tex = NULL;
	SDL_Surface* loaded = IMG_Load(path.c_str());
	if(loaded==NULL) cerr << "Texture error: " << IMG_GetError() << endl;
	else {
		SDL_SetColorKey(loaded, SDL_TRUE, SDL_MapRGB(loaded->format, 255, 0, 255));
		tex = SDL_CreateTextureFromSurface(mRenderer, loaded);
		if(tex==NULL) cerr << "Texture error: " << SDL_GetError() << endl;
		else{
			mWidth = loaded->w;
			mHeight = loaded->h;
		}	
		SDL_FreeSurface(loaded);
	}
	mTexture = tex;
    return mTexture!=NULL;
}

void Texture::free() 
{
	if(mTexture!=NULL){
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(mTexture, r, g, b);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(int x, int y, SDL_Rect * clip, double angle, SDL_Point* center, SDL_RendererFlip flip) 
{
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	if(clip!=NULL){
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(mRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() const 
{
    return mWidth;
}

int Texture::getHeight() const 
{
    return mHeight;
}
