#include "Player.h"

Player::Player() {
	mPosX=OFFSET;
	mPosY=ZERO;
	mVelX=0;
	mVelY=0;
	oldVelX = 0;
	accelTimer = SDL_GetTicks();
	jumpTimer = SDL_GetTicks();
	restartTimer = 0;
	scroll = 0;
	restart = 0;
	up = 0; down = 0; left = 0; right = 0;
	oUp = 0; oDown = 0; oLeft = 0; oRight = 0;
	jumped = 0;
	mushroom = 0;
	flower = 0;
	star = 0;
	starCounter = 0;
	flip = SDL_FLIP_NONE;
}

void Player::eventHandler() 
{
	if(*start && !Sound::playing()) Sound::music(OVERWORLD);
	accelerate = (SDL_GetTicks()-accelTimer)>100;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if(accelerate && *start){
		if(state[SDL_SCANCODE_Z]){
			run = 1;
		} else {
			run = 0;
		}
		
		if(state[SDL_SCANCODE_LEFT] && !left){
			if(mVelX>-MAX_VEL) mVelX-=(VEL+run*2);
			flip = SDL_FLIP_HORIZONTAL;
		} else {
			if(mVelX<0) mVelX+=VEL;	
		}

		if(state[SDL_SCANCODE_RIGHT] && !right){
			if(mVelX<MAX_VEL) mVelX+=(VEL+run*2);
			flip = SDL_FLIP_NONE;
		} else {
			if(mVelX>0) mVelX-=VEL;
		}
	
		if(state[SDL_SCANCODE_X] && down && !up){
			if(mVelY==0) {
				jumped = 1;
				mVelY-=GRAVITY-(MAX_VEL-abs(mVelX));
				Sound::play(SJUMPFX);
			}
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
		
		mVelY+=VEL;
	}

	blockCollide(mPosX, mPosY);
	
	mPosX+=mVelX;
	mPosY+=mVelY; 

	if(down && mVelY==0 && oDown) mPosY = round(mPosY/16)*16;
	
	cout << "PX:" << mPosX << " PY:" << 
	mPosY << " VX:" <<  mVelX << " VY:" <<  mVelY << 
	"   X:" << *death << " S:" << *start << " L:" << *lives << 
	"   U:" << up << " D:" << down << " L:" << left << " R:" << right << endl;

	if(accelerate) accelTimer = SDL_GetTicks();
	if(mPosY>(ZERO+2*BLOCK)) mDeath = 1;
	if(mDeath && *start) {(*lives)--; *start = 0; Sound::pause(); Sound::play(DEATHFX); restartTimer = SDL_GetTicks(); }
	if(mDeath && SDL_GetTicks() - restartTimer>1000) { mPosX = OFFSET; mPosY = ZERO; };
	jumped = 0;
}

void Player::render() 
{
	SDL_Rect clip;
	if(abs(mVelX)<abs(oldVelX) && mVelX!=0)
	clip = {3*BLOCK, 2*BLOCK-2*mushroom*BLOCK+3*flower*BLOCK+(3*starCounter*BLOCK), BLOCK, BLOCK*(1+mushroom)};
	else if(!down)
		clip = {4*BLOCK, 2*BLOCK-2*mushroom*BLOCK+3*flower*BLOCK+(3*starCounter*BLOCK), BLOCK, BLOCK*(1+mushroom)};
	else if(mVelX!=0)
		clip = {((mPosX/(BLOCK*2))%3)*BLOCK, 2*BLOCK-2*mushroom*BLOCK+3*flower*BLOCK+(3*starCounter*BLOCK), BLOCK, BLOCK*(1+mushroom)};
	else
		clip = {6*BLOCK, 2*BLOCK-2*mushroom*BLOCK+3*flower*BLOCK+(3*starCounter*BLOCK), BLOCK, BLOCK*(1+mushroom)};
	if(star) starCounter = (starCounter+1)%11;

	playerSprites->render(OFFSET, mPosY-BLOCK+8-mushroom*BLOCK, &clip, 0.0f, NULL, flip);
	oldVelX = mVelX;
}

Block& Player::getBlock(int x, int y){
	x/=BLOCK; y/=BLOCK;
	if(y<0 || y>=MHEIGHT) y = 0;
	if(x<0 || x>=MLENGTH) x = 0;
	return layout->at(y)[x+(OFFSET/BLOCK)];
}

void Player::blockCollide(int x, int y){
	int off = -238;
	up	  = (!getBlock(x+off+BLOCK/2, y).passThrough);
	down  = (!getBlock(x+off+BLOCK/2, y+BLOCK).passThrough);
	left  = (!getBlock(x+off, y).passThrough);
	right = (!getBlock(x+off+BLOCK, y).passThrough);
	
	if(left || right){
	   	if((left!=oLeft ||  right!=oRight) && mVelX!=0){
			Sound::play(BUMPFX);
			mVelX = 0;
		}
	}

	if(down){
		if(!jumped) mVelY = 0;
	}

	if(up){
		if(!down && oUp!=up){
		   	mVelY = 0;
			Sound::play(BUMPFX);
		}
	}

	oUp = up; oDown = down, oLeft=left, oRight=right;
}

Player::~Player(){}
