#include "Player.h"

Player::Player(Texture& mSpriteSheet)
	:mSpriteSheet(mSpriteSheet)
{
	mPosX=30;
	mPosY=zero;
	mVelX=0;
	mVelY=0;
	accelTimer = SDL_GetTicks();
	jumpTimer = SDL_GetTicks();
	scroll = 0;
	mushroom = 0;
	flower = 0;
	star = 0;
	starCounter = 0;
	zero = ZERO-(1+mushroom)*16;
	flip = SDL_FLIP_NONE;
}

void Player::eventHandler() 
{
	bool accelerate = (SDL_GetTicks()-accelTimer)>100;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	if(accelerate){
		if(state[SDL_SCANCODE_LEFT]){
			if(accelerate && mVelX>-MAX_VEL) mVelX-=VEL;
			flip = SDL_FLIP_HORIZONTAL;
		} else {
			if(mVelX<0)mVelX+=VEL;	
		}
		if(state[SDL_SCANCODE_RIGHT]){
			if(accelerate && mVelX<MAX_VEL) mVelX+=VEL;
			flip = SDL_FLIP_NONE;
		} else {
			if(mVelX>0)mVelX-=VEL;
		}
	
		if(state[SDL_SCANCODE_SPACE] && !isFalling()){
			if((SDL_GetTicks()-jumpTimer) < 1000 || !jumped){
				jumped = 1;
				if(accelerate && mVelY==0) {
					mVelY-=((abs(mVelX)+1)/4)*VEL+5;
					jumpTimer = SDL_GetTicks();
				}
			}
		} else {
			jumped = false;
			if(isFalling()) mVelY+=VEL;
		}
	}

	mPosX+=mVelX;
	mPosY+=mVelY; 

	calculateGround();
	blockCollide();

	if(mPosY>zero) mPosY = zero;
	if(mPosY<-15) mPosY = -15;
	//if(!isFalling()) mVelY=0;
	

	std::cout << "PX:" << mPosX << " PY:" << 
	mPosY << " VX:" <<  mVelX << " VY:" <<  mVelY << 
	" Z:" << zero << " GR:" << !isFalling() << std::endl;

	if(accelerate) accelTimer = SDL_GetTicks();
}

void Player::render() 
{
	SDL_Rect clip;
	if(isFalling())
		clip = {4*16, 2*16-2*mushroom*16+3*flower*16+(3*starCounter*16), 16, 16*(1+mushroom)};
	else if(mVelX!=0)
		clip = {((mPosX/32)%3)*16, 2*16-2*mushroom*16+3*flower*16+(3*starCounter*16), 16, 16*(1+mushroom)};
	else
		clip = {6*16, 2*16-2*mushroom*16+3*flower*16+(3*starCounter*16), 16, 16*(1+mushroom)};
	if(star) starCounter = (starCounter+1)%11;

	mSpriteSheet.render(OFFSET, mPosY, &clip, 0.0f, NULL, flip);
}

bool Player::isFalling(){
	return abs(zero-mPosY)>0;
}

Block& Player::getFromIndex(int x, int y){
	x/=16; y/=16;
	if(y<0 || y>(LHEIGHT+2)) y = 0;
	if(x<0 || x>LLENGTH) x = 0;
	return layout->at(y+1)[x+1+(OFFSET/16)];
}

void Player::calculateGround(){
	//getFromIndex(mPosX, mPosY) = Block(true, true, 0, 0);
	int tmp = HEIGHT/2;
	for(int i = mPosY+8; i < (ZERO-MHEIGHT*16); i+=16){
		if(!getFromIndex(mPosX, i).passThrough){
			tmp = (i/16);
			break;
		}
	}
	zero = (tmp*16-8);
	std::cout << zero << endl;
	//zero = ZERO-(1+mushroom)*16;
}

void Player::blockCollide(){
	if(!getFromIndex(mPosX, mPosY).passThrough && mVelX>0) mVelX = 0;
	if(!getFromIndex(mPosX-16, mPosY).passThrough && mVelX<0) mVelX = 0;
	if(!getFromIndex(mPosX, mPosY-16).passThrough && mVelY<0) mVelY = 0;
	if(!getFromIndex(mPosX, mPosY).passThrough && mVelY>0) mVelY = 0;
}

Player::~Player(){}
