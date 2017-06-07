#include "Player.h"

Player::Player(Texture& mSpriteSheet)
	:mSpriteSheet(mSpriteSheet)
{
	mPosX=OFFSET;
	mPosY=0;
	mVelX=0;
	mVelY=0;
	oldVelX = 0;
	accelTimer = SDL_GetTicks();
	jumpTimer = SDL_GetTicks();
	scroll = 0;
	mushroom = 0;
	flower = 0;
	star = 0;
	starCounter = 0;
	flip = SDL_FLIP_NONE;
}

void Player::eventHandler() 
{
	bool accelerate = (SDL_GetTicks()-accelTimer)>100;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	if(accelerate){
		if(state[SDL_SCANCODE_Z]){
			run = 1;
		} else {
			run = 0;
		}
		
		if(state[SDL_SCANCODE_LEFT]){
			if(mVelX>-MAX_VEL) mVelX-=(VEL*(1+run));
			flip = SDL_FLIP_HORIZONTAL;
		} else {
			if(mVelX<0) mVelX+=VEL;	
		}

		if(state[SDL_SCANCODE_RIGHT]){
			if(mVelX<MAX_VEL) mVelX+=(VEL*(1+run));
			flip = SDL_FLIP_NONE;
		} else {
			if(mVelX>0) mVelX-=VEL;
		}
	
		if(state[SDL_SCANCODE_X] && !isFalling()){
			if(mVelY==0) {
				mVelY-=GRAVITY-(MAX_VEL-mVelX);
			}
		} else {
			mVelY+=VEL;
		}

		/*if(state[SDL_SCANCODE_DOWN]){
			if(mVelY<MAX_VEL) mVelY+=VEL;
		} else {
			if(mVelY>0) mVelY-=VEL;
		}

		if(state[SDL_SCANCODE_UP]){
			if(mVelY>-MAX_VEL) mVelY-=VEL;
		} else {
			if(mVelY<0) mVelY+=VEL;
		}*/
	}

	blockCollide();
	
	mPosX+=mVelX;
	mPosY+=mVelY; 

	std::cout << "PX:" << mPosX << " PY:" << 
	mPosY << " VX:" <<  mVelX << " VY:" <<  mVelY << 
	" GR:" << !isFalling() << std::endl;

	if(accelerate) accelTimer = SDL_GetTicks();
}

void Player::render() 
{
	SDL_Rect clip;
	if(abs(mVelX)<abs(oldVelX) && mVelX!=0)
	clip = {3*BLOCK, 2*BLOCK-2*mushroom*BLOCK+3*flower*BLOCK+(3*starCounter*BLOCK), BLOCK, BLOCK*(1+mushroom)};
	else if(isFalling())
		clip = {4*BLOCK, 2*BLOCK-2*mushroom*BLOCK+3*flower*BLOCK+(3*starCounter*BLOCK), BLOCK, BLOCK*(1+mushroom)};
	else if(mVelX!=0)
		clip = {((mPosX/(BLOCK*2))%3)*BLOCK, 2*BLOCK-2*mushroom*BLOCK+3*flower*BLOCK+(3*starCounter*BLOCK), BLOCK, BLOCK*(1+mushroom)};
	else
		clip = {6*BLOCK, 2*BLOCK-2*mushroom*BLOCK+3*flower*BLOCK+(3*starCounter*BLOCK), BLOCK, BLOCK*(1+mushroom)};
	if(star) starCounter = (starCounter+1)%11;

	mSpriteSheet.render(OFFSET, mPosY-BLOCK+4-mushroom*BLOCK, &clip, 0.0f, NULL, flip);
	oldVelX = mVelX;
}

bool Player::isFalling(){
	return mVelY!=0;
}

Block& Player::getBlock(int x, int y){
	x/=BLOCK; y/=BLOCK;
	if(y<0 || y>=MHEIGHT) y = 0;
	if(x<0 || x>=MLENGTH) x = 0;
	return layout->at(y)[x+(OFFSET/BLOCK)];
}

void Player::blockCollide(){
//R	
	if(!getBlock(mPosX+BLOCK, mPosY).passThrough|!getBlock(mPosX+BLOCK, mPosY-BLOCK).passThrough && mVelX>0) mVelX = 0;
//L
	if(!getBlock(mPosX, mPosY).passThrough && mVelX<0) mVelX = 0;
//D	
	if(!getBlock(mPosX+BLOCK, mPosY+BLOCK).passThrough|!getBlock(mPosX, mPosY+BLOCK).passThrough && mVelY>0) mVelY = 0;
//U
	if(!getBlock(mPosX, mPosY-8).passThrough && mVelY<0) mVelY = 0;
}

Player::~Player(){}
