#ifndef GRAPHICS_H
#define GRAPHICS_H
//#include <SDL.h>
#include <iostream>
using namespace std;

//forward delcaring. Allows for me to use my pointers below
//even if the SDL.h hasnt been included
struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
public:
	Graphics();
	~Graphics();
private:
	SDL_Window* _window;	//Creates the window
	SDL_Renderer* _renderer;	//Does all of the drawing to the window
};




#endif