#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using std::cerr;
using std::endl;
using std::string;

class Texture
{
public:
	Texture(SDL_Renderer* mRenderer);
	~Texture();
	bool loadFromFile(string path);
	void free();
	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth() const;
	int getHeight() const;
	
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	int mWidth, mHeight;
};

#endif
