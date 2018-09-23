#include "KeydownMessage.h"
#include "Game.h"
#include "UnitManager.h"
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
			gpGame->deleteRandomEnemyUnit();
			break;
		}
		case KEY_ESCAPE: {
			gpGame->quitLoop();
			break;
		}
		case KEY_ENTER:
		{
			gpGame->spawnEnemyAtRandomLoc();
			break;
		}

	}
	
}
