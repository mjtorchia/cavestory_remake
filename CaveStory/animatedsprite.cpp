#include "animatedsprite.h"
#include "graphics.h"
#include "sprite.h"

/* Animated Sprite class
*  Animates our sprites
*/


AnimatedSprite::AnimatedSprite(){}

AnimatedSprite::AnimatedSprite(Graphics &_graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate)
	:
	Sprite(_graphics, filePath, sourceX, sourceY, width, height, posX, posY), _frameIndex(0), _timeToUpdate(timeToUpdate), _visible(true), _currentAnimationOnce(false), _currentAnimation(""){
	
}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset)
{
	std::vector<SDL_Rect> rectangles;
	
	//this for loop works to cut up the sprite sheet and push them into the temp vector that we just created
	
	/*Example: (refer to spritesheet) For running left we'd say that there are 3 different frames for running left
	(frames=3). The first time around in the loop we'd grab the very top left frame (x value for newRect would be
	(i+x)*16 which would be (0+0)*16=0) so the x cord we start to grab from on the spritesheet would be 0. The i+x is
	what helps us move over to the next frame. when i=1 our x cord would then be (1+0)*16=16. So now the x cord we start
	to grab from on the spritesheet would be 16. Next time it would be (2+0)*16=32. You can start to see a pattern here.
	The varibles that get passed will determine the frames we need for the anmiation but the logic is the same for all of them*/
	
	for (int i = 0; i < frames; i++){
		SDL_Rect newRect = { (i + x)*width,y,width,height };
		rectangles.push_back(newRect); //q structure
	}
	//passing a name for whatever rectangle and then the rectangle itself to the pair for the map
	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));

	//passing a name for whatever offset and then the offset itself to the pair for the map
	this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations()
{
	//clears the maps
	this->_animations.clear();
	this->_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{
	//set currentAnimation to whatever once is. (false by default)
	this->_currentAnimationOnce = once;
	
	//check to see if the animation we're trying to play now is already playing. if current!=animation, then start playing the new one
	if (this->_currentAnimation != animation)
	{
		this->_currentAnimation = animation;
		//restart frame index so it will start at the beginning of our animation
		this->_frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visable)
{
	this->_visible = visable;
}

void AnimatedSprite::stopAnimation()
{
	this->_frameIndex = 0;
	this->animationDone(this->_currentAnimation);
}

/////////////////////////////////////////////
//note to self: need to understand this better
/////////////////////////////////////////////
void AnimatedSprite::update(int elapsedTime)
{
	Sprite::update();
	this->_timeElapsed += elapsedTime;

	//if true. change frames
	if (this->_timeElapsed > this->_timeToUpdate)
	{
		this->_timeElapsed -= this->_timeToUpdate;
		//if frameIndex is less than animations @ currentAnimation size - 1. size will always be 1 more than the index since index starts at 0 and size starts at 1
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1)
		{
			this->_frameIndex++;
		}
		else
		{	
			if (this->_currentAnimationOnce == true)
			{
				this->setVisible(false);
			}
			this->_frameIndex = 0;
			this->animationDone(this->_currentAnimation);
		}
	}
}

//39.08 for explination
void AnimatedSprite::draw(Graphics &_graphics, int x, int y)
{
	if(this->_visible)
	{
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
		destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
		
		destinationRectangle.w = this->_sourceRect.w * globals::SPRITE_SCALE;
		destinationRectangle.h = this->_sourceRect.h * globals::SPRITE_SCALE;

		//using the _currentAnimation and _frameIndex we can get whatever animation we need from our
		//_animations map
		SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];
		_graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle);
	}
}



//implemented in everything that is inheriting off of animated sprite
/*void AnimatedSprite::setupAnimation()
{
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(3,0,16,"RunRight",16,16,Vector2(0,0));
}*/
	
