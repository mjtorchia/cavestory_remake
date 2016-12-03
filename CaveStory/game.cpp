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


	//init player and level
	this->_level = Level("Map 1", Vector2(100, 100), _graphics);
	this->_player = Player(_graphics,_level.getPlayerSpawnPonit());
	
	

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
		//if you're holding the left key
		else if (_input.isKeyHeld(SDL_SCANCODE_LEFT) == true)
		{
			this->_player.moveLeft();
		}
		//if you're holding the right key
		else if (_input.isKeyHeld(SDL_SCANCODE_RIGHT) == true)
		{
			this->_player.moveRight();
		}

		if (_input.wasKeyPressed(SDL_SCANCODE_Z) == true)
		{
			this->_player.jump();
		}
		//if neither key is being held
		if (!_input.isKeyHeld(SDL_SCANCODE_LEFT) && !_input.isKeyHeld(SDL_SCANCODE_RIGHT))
		{
			this->_player.stopMoving();
		}

		//keeps track of how long each iteration of the game loop takes
		const int CURRENT_TIME_MS = SDL_GetTicks();	

		//keeps track of how long current frame took to run
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;

		//this passes in the lesser value between the two arguments
		this->update(std::min(ELAPSED_TIME_MS,MAX_FRAME_TIME));

		//keeps the time updated
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(_graphics);


	}//end of while loop
}
void Game::draw(Graphics &graphics){
	//first clear renderer
	graphics.clear();

	this->_level.draw(graphics);

	//calls the draw function from the sprite class, not the game class
	this->_player.draw(graphics);
	graphics.flip();
}
void Game::update(float elapsedTime){
	this->_player.update(elapsedTime);
	this->_level.update(elapsedTime);

	//Check collisions
	std::vector<Rectangle> other;
	//checkTileCollisions will check whatever we pass with all of the level collsion rectangles and return a vector with all of the collisions
	if ((other = this->_level.checkTileCollision(this->_player.getBoundingBox())).size() > 0)
	{
		//player collided with at least one tile. this will move the player accordingly
		this->_player.handleTileCollision(other);
	}
	//Check slopes
	std::vector<Slope> otherSlopes;
	if ((otherSlopes = this->_level.checkSlopeCollision(this->_player.getBoundingBox())).size() > 0)
	{
		this->_player.handleSlopeCollision(otherSlopes);
	}
}