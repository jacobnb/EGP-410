#include "KeydownMessage.h"
#include "Game.h"
#include "UnitManager.h"
#include "DataLoader.h"
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
			gpGame->deleteRandomEnemyUnit();
			break;
		}
		case KEY_ESCAPE: {
			gpGame->getDataLoader()->writeData();
			gpGame->quitLoop();
			break;
		}
		case KEY_ENTER:
		{
			gpGame->spawnEnemyAtRandomLoc();
			break;
		}
		case KEY_A: {
			gpGame->spawnTenBoids();
			break;
		}

	}
	
}
