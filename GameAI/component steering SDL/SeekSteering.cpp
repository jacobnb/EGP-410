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

int SeekSteering::testMe(const int value)
{
	return value;
}



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
	
	//find rotation velocity
	float velocityDirection = atan2(diff.getY(), diff.getX());
	float currentDirection = pOwner->getFacing();
	float rotation = getRotation(velocityDirection, currentDirection);
	
	data.rotVel = rotation*2;
	//std::cout << data.rotVel << std::endl;
	this->mData = data;
	return this;
}

/*
24 # 1. Calculate the target to delegate to face
25 26 # Update the wander orientation 
27 wanderOrientation += randomBinomial() * wanderRate

28 29 # Calculate the combined target orientation 
30 targetOrientation = wanderOrientation + 
31 character.orientation

32 33 # Calculate the center of the wander circle 
34 target = character.position + 
35 wanderOffset * character.orientation.asVector()

36 37 # Calculate the target location 
8 target += wanderRadius * targetOrientation.asVector()

39 40 # 2. Delegate to face 
41 steering = Face.getSteering()
42 43 # 3. Now set the linear acceleration to be at full 
44 # acceleration in the direction of the orientation 
45 steering.linear = maxAcceleration * 
46 character.orientation.asVector()
47*/
