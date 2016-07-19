#include <SDL.h>
#include "game.h"
#include "graphics.h"
#include "input.h"
#include <algorithm>
/*Game class
* Holds all info for our main game loop
*/

namespace{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

//Initializes everything then calls the game loop after that
Game::Game(){
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}
Game::~Game(){
}
void Game::gameLoop(){
	Graphics _graphics;
	Input _input;
	SDL_Event _event;	//object that holds whatever event happens for a frame.

	int LAST_UPDATE_TIME = SDL_GetTicks();	// gets num of milliseconds since SDL was init

	//start of game loop
	while (true){
		_input.beginNewFrame();
			//every frame SDL will poll for events and place them in event
		if (SDL_PollEvent(&_event)){

			//if the event type from PollEevnt was a key down event
			if (_event.type == SDL_KEYDOWN){

					//if the key was not repeated
					if (_event.key.repeat == 0){

						//execute
						_input.keyDownEvent(_event);
				}//end of if(_event.key.repeat == 0)

			}//end of if(_event.type ==SDL_KEYDOWN)

			//end of if(_event.type == SDL_KEYDOWN)
			else if (_event.type == SDL_KEYUP){
				_input.keyUpEvent(_event);
			}

			//if the event causes the program to quit then exit the game loop (close the game)
			else if (_event.type == SDL_QUIT){
				return;
			}
		}//end of if(SDL_PollEvent)

		//if Escape was pressed the game will close
		if (_input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true){
			return;
		}

		//keeps track of how long each iteration of the game loop takes
		const int CURRENT_TIME_MS = SDL_GetTicks();	

		//keeps track of how long current frame took to run
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		//this passes in the lesser value between the two arguments
		this->update(std::min(ELAPSED_TIME_MS,MAX_FRAME_TIME));

		//keeps the time updated
		LAST_UPDATE_TIME = CURRENT_TIME_MS;


	}//end of while loop
}
void Game::draw(Graphics &graphics){
}
void Game::update(float elapsedTime){
}