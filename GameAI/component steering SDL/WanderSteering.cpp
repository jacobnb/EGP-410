#include <cassert>

#include "WanderSteering.h"
#include "FaceSteering.h"
#include "SeekSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"


WanderSteering::WanderSteering(const UnitID & ownerID, const float & radius)
{
	//mType = Steering::WANDER; //not sure this is neccessary
	setOwnerID(ownerID);
	mWanderRadius = radius;
}

Steering * WanderSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	mTargetLoc = getTarget();

	//this is all seekSteering
	diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
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

Vector2D WanderSteering::getTarget()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	float wanderRadius = mWanderRadius;
	float wanderOrientation = pOwner->getFacing();
	auto maxAcceleration = pOwner->getMaxAcc();
	wanderOrientation +=  genRandomBinomial()* mWanderRate;
	auto charOrientation = Vector2D(cos(pOwner->getFacing()), sin(pOwner->getFacing()));
	auto targetOrientation = wanderOrientation + pOwner->getFacing();
	auto target = pOwner->getPositionComponent()->getPosition() 
		+ charOrientation * mWanderOffset;
	target += Vector2D(cos(targetOrientation),sin(targetOrientation)) * wanderRadius;

	return target;
}
