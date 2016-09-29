#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include "sprite.h"
#include <string>
#include <map>
#include "globals.h"
#include <vector>

//forward declare
class Graphics;

/* Animated Sprite Class
* Holds logic for animating sprites
*/

class AnimatedSprite :public Sprite{
public:
	
	AnimatedSprite();
	
	
	//timeToUpdate is how long until we're suppose to go on to the next frame in the animation
	AnimatedSprite(Graphics&_graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY, float timeToUpdate);
	//timeToUpdate is how long until you move to the next frame in the animation
	
	//passing string animation because we're going to be categorizing animations by name
	//optional parameter once will automatically cast once to false if not specifically casted
	/*void playAnimation
	* plays animation provided its not already playing
	*/
	void playAnimation(std::string animation, bool once = false);
	
	/* void update
	*  updates the animated sprite (based off elapsedTime);
	*/
	void update(int elapsedTime);
	
	/* void draw
	*  draws sprite to the screen
	*/
	void draw(Graphics &_graphics, int x, int y);

	/* void setupAnimation()
	*  a required function that sets up all animations for a sprite
	*  any class that animates a sprite must have this implemented.
	*
	* Virtual because we're not going to be implementing it in the animatedsprite class
	*/
	virtual void setupAnimation();

protected:
	double _timeToUpdate;
	
	//if current Animation has played once through?
	bool _currentAnimationOnce;
	std::string _currentAnimation;


	/* void addAnimation
	*  adds an animations to the map of animations for the sprite
	*/
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);
	
	/* void resetAnimation
	*  resets all animations associated with the sprite
	*/
	void resetAnimations();

	/* void stopAnimation
	*  stops the current animation
	*/
	void stopAnimation();

	/* void setVisable
	*  changes the visability of the animated sprite
	*/
	void setVisible(bool visable);

	/* void animationsDone
	*  logic that happens when an animation ends
	*/
	virtual void animationDone(std::string currentAnimation);



private:
	//ep5 @ 16 mins for explaination
	//map to hold all of our animations.
	//the vector of Rect holds each 16x16 animation
	std::map<std::string, std::vector<SDL_Rect>> _animations;

	//If ever our animation is not 16x16 then we want to move to where the sprite is being draw
	//and we'll give it an offset by however many pixles needed and it will be stored in this map
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed=0.0;
	bool _visible;

};


#endif