#include "KeydownMessage.h"

KeydownMessage::KeydownMessage(const char& key)
	:GameMessage(KEYDOWN_MESSAGE)
	, mKey(key)
{
}

KeydownMessage::~KeydownMessage()
{
}

void KeydownMessage::process()
{
	if (mKey == 'D') {
		std::cout << "delete random unit\n";
	}
}
