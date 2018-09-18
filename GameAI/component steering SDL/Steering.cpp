#include "Steering.h"


void Steering::update()
{
	Steering* pTemp = getSteering();
	if (pTemp != NULL)
	{
		mData = pTemp->getData();
	}
}

float Steering::getRotation(float velocityDirection, float currentDirection)
{
	float rotation = velocityDirection - currentDirection;
	const float pi = (atan(1) * 4);
	if (rotation > pi) {
		rotation -= 2 * pi;
	}
	else if (rotation < -pi) {
		rotation += 2 * pi;
	}
	return rotation;
}
