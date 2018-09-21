#include "Steering.h"


void Steering::update()
{
	Steering* pTemp = getSteering();
	if (pTemp != NULL)
	{
		mData = pTemp->getData();
	}
}

float Steering::getRotation(float targetDirection, float currentDirection)
{
	float rotation = targetDirection - currentDirection;
	const float pi = (atan(1) * 4);
	//might have a problem if rotation is more than 2Pi
	if (rotation > pi) {
		rotation -= 2 * pi;
	}
	else if (rotation < -pi) {
		rotation += 2 * pi;
	}
	return rotation;
}
