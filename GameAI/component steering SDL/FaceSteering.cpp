#include <cassert>

#include "FaceSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

FaceSteering::FaceSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID)
{
	//mType = Steering::FACE;
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering * FaceSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	//vector to target.
	auto diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	//find rotation velocity
	float targetDirection = atan2(diff.getY(), diff.getX());
	float currentDirection = pOwner->getFacing();
	float rotation = getRotation(targetDirection, currentDirection);
	data.rotVel = rotation * 2;
	this->mData = data;
	return this;
}
