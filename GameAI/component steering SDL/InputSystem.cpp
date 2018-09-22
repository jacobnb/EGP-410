#include "InputSystem.h"
#include <stdio.h>
#include <assert.h>

#include <sstream>
#include <SDL.h>

#include "GameMessage.h"
#include "Vector2D.h"
#include "Defines.h"
#include "Game.h"
#include "PlayerMoveToMessage.h"
InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	
}

std::string InputSystem::getKeyState()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_RETURN]) {
		return "return";
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		return "right";
	}
	if(state[SDL_SCANCODE_UP])
	{
		return "left";
	}
	else
	{
		return "NULL";
	}
}

int  InputSystem::getMouseState()
{
	SDL_PumpEvents();
	if (SDL_GetMouseState(&mXMouse,&mYMouse))
	{
		if (SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			return 1;
		}
		if (SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			return 2;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

void InputSystem::update() //handles mouse events for menu.
{
	////fire mouseInput;
	//EventSystem::getInstance()->fireEvent(MouseInputEvent(getMouseState()));
	////fire x and y mouse input
	//EventSystem::getInstance()->fireEvent(MoveEvent(mXMouse,mYMouse));
}

void InputSystem::update(int numEvents) //Handles keyboard events for game loop
{ 
	SDL_Event nextEvent;
	for (int c = 0; c < numEvents; c++) {
		if (!SDL_PollEvent(&nextEvent)) {
			return;
		}
		switch (nextEvent.type)
		{
		case SDL_KEYDOWN: //esc calls pause
			//cout << "keydown: " << SDL_GetKeyName(nextEvent.key.keysym.sym) << endl;
			//mpEventSystem->fireEvent(KeyEvent(SDL_GetKeyName(nextEvent.key.keysym.sym)));
			break;
		case SDL_KEYUP:
			break;
		case SDL_QUIT: //clicks on red X?
			//mpEventSystem->fireEvent(KeyEvent("Close window"));
			break;
		default:
			break;

		}
	}
}

void InputSystem::updateAll()
{
	SDL_Event nextEvent;
	while (true)
	{
		if (!SDL_PollEvent(&nextEvent)) {
			return;
		}
		switch (nextEvent.type)
		{
		case SDL_KEYDOWN: 
			//mpEventSystem->fireEvent(KeyEvent(SDL_GetKeyName(nextEvent.key.keysym.sym)));
			break;
		case SDL_KEYUP:
			break;
		case SDL_QUIT: //clicks on red X
			//mpEventSystem->fireEvent(KeyEvent("Close window"));
			break;
		default:
			break;

		}
	}
}

void InputSystem::clearQueue()
{
	SDL_PumpEvents();
	SDL_FlushEvents(SDL_APP_LOWMEMORY, SDL_LASTEVENT);
}

void InputSystem::stuffFromGame()
{

	SDL_PumpEvents();
	int x, y;
	SDL_GetMouseState(&x, &y);

	//==Mouse Text==//
	//create mouse text
	std::stringstream mousePos;
	mousePos << x << ":" << y;
	//write text at mouse position
	//mpGraphicsSystem->writeText(*mpFont, (float)x, (float)y, mousePos.str(), BLACK_COLOR);


	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		
		Vector2D pos(x, y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		//MESSAGE_MANAGER->addMessage(pMessage, 0);
	}

}

