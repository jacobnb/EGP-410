#include "KeydownMessage.h"
#include "Game.h"
#include "GameMessageManager.h"
KeydownMessage::KeydownMessage(const KeyType& key)
	:GameMessage(KEYDOWN_MESSAGE)
	, mKey(key)
{
}

KeydownMessage::~KeydownMessage()
{
}

void KeydownMessage::process()
{
	switch (mKey) {
		case KEY_D: {
			//should also delete a random boid
			break;
		}
		case KEY_ESCAPE: {
			break;
		}
		case KEY_ENTER:
		{
			break;
		}
		case KEY_A: {
			break;
		}
	}
}
