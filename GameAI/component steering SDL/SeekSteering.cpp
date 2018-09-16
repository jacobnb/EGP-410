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
	float pi = (atan(1) * 4);
	//Set rotation here.
	//this is where we want it to go.
	float velocityDirection = atan2(diff.getY(), diff.getX());// keep range positive. //PI = atan(1)*4
	/*if (velocityDirection < 0) {
		velocityDirection += 2 * pi;
	}*/
	float currentDirection = pOwner->getFacing();
	/*if (currentDirection < 0) {
		currentDirection += 2 * pi;
	}*/
	std::cout << "VelDir: " << velocityDirection << " CurDir: " << currentDirection << " diff: " << (velocityDirection - currentDirection) + 2 * atan(1) * 4 << std::endl;
	data.rotVel = velocityDirection - currentDirection;// (velocityDirection - currentDirection);// -(atan(1) * 4); //adjust range back.

	if (velocityDirection > currentDirection) {
		data.rotVel = 2;
	}
	else {
		data.rotVel = -2;
	}
	std::cout << data.rotVel << std::endl;
	this->mData = data;
	return this;
}

