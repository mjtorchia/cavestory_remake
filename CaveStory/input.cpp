#include "input.h"

/* Input class
* Keeps track of keyboard state
*/

//This function gets called at the begining of each new frame
//to reset the keys that are no longer relavant
void Input::beginNewFrame(){
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}
//This gets called when a key has been pressed
void Input::keyDownEvent(const SDL_Event& event){
	/*Since we pressed a key we want to set that key in _pressedkeys equal to true.
	This will set the scancode of _pressedkeys that was pressed equal to true.
	So if A was pressed then the A scancode in _pressedKeys would have a bool value of true.
	Same thing applies to held keys because technically, in that frame, the scancode is being held*/
	this->_pressedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = true;
}
//This gets called when a key is released
void Input::keyUpEvent(const SDL_Event& event){
	/*The same principle applies from keyDownEvent. When a key is released we need to tell
	the _releasedKeys map that that scancode has been released (true). And since we've released it
	its not longer being held so we have to do the same thing to the scancode of _heldkeys*/
	this->_releasedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = false;
}
//This checks if a certain key was pressed druing the current frame
bool Input::wasKeyPressed(SDL_Scancode key){
	//this will return a bool associated with the key that is being passed into wasKeyPressed
	return this->_pressedKeys[key];
}
//This checks if a certain key was released druing the current frame
bool Input::wasKeyReleased(SDL_Scancode key){
	//same thing from wasKeyPressed is applied here
	return this->_releasedKeys[key];
}
//This checks if a certain key was held druing the current frame
bool Input::isKeyHeld(SDL_Scancode key){
	return this->_heldKeys[key];
}