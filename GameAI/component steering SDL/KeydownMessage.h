#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class KeydownMessage :public GameMessage
{
public:
	KeydownMessage(const char& key);
	~KeydownMessage();

	void process();

private:
	Vector2D mKey;
};