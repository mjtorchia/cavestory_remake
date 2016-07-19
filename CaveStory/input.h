#ifndef INPUT_H
#define INPUT_H

#include <map>
#include <SDL.h>

class Input{
public:
	void beginNewFrame();

	void keyUpEvent(const SDL_Event& event); //for when key is pressed
	void keyDownEvent(const SDL_Event& event); //for when key is released

	bool wasKeyPressed(SDL_Scancode key); //names of functions describe what they do
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);
private:

	//A map is a way of holding 2 types of related information together

	//If an A was entered on the keyboard SDL_Scancode would go to where ever the A would normally be on the keyboard
	//and take the input in that spot. this is because not all keyboards are set up the sameway


	std::map<SDL_Scancode, bool> _heldKeys; //map that is going to hold keys are being held
	std::map<SDL_Scancode, bool> _pressedKeys; //map that is going to hold keys are being pressed
	std::map<SDL_Scancode, bool> _releasedKeys; //map that is going to hold keys are being released
};

#endif INPUT_H