#include <cassert>

#include "Steering.h"
#include "SeekSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


SeekSteering::SeekSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID, bool shouldFlee /*= false*/)
	: Steering()
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::SEEK;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

//int SeekSteering::testMe(const int value)
//{
//	return value;
//}

Steering* SeekSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	//are we seeking a location or a unit?
	
	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	if (mType == Steering::SEEK)
	{
		diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	else
	{
		diff = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}

	diff.normalize();
	diff *= pOwner->getMaxAcc();

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data.acc = diff;
	const float pi = (atan(1) * 4);
	float velocityDirection = atan2(diff.getY(), diff.getX());// keep range positive. //PI = atan(1)*4
	float currentDirection = pOwner->getFacing();
	//std::cout << "VelDir: " << velocityDirection << " CurDir: " << currentDirection << " diff: " << (velocityDirection - currentDirection) + 2 * atan(1) * 4 << std::endl;
	float rotation = velocityDirection - currentDirection;
	if (rotation > pi) {
		rotation -= 2 * pi;
	}
	else if (rotation < -pi) {
		rotation += 2 * pi;
	}
	data.rotVel = 2*rotation;
	//std::cout << data.rotVel << std::endl;
	this->mData = data;
	return this;
}

