#include <cassert>

#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

WanderSteering::WanderSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	mType = Steering::WANDER; //not sure this is neccessary
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering * WanderSteering::getSteering()
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

	//find rotation velocity
	float velocityDirection = atan2(diff.getY(), diff.getX());
	float currentDirection = pOwner->getFacing();
	float rotation = getRotation(velocityDirection, currentDirection);

	data.rotVel = rotation * 2;
	//std::cout << data.rotVel << std::endl;
	this->mData = data;
	return this;
}
