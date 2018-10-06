#include "SeparationSteering.h"
#include "SeekSteering.h"
#include "Game.h"
#include "Unit.h"
#include "UnitManager.h"

SeparationSteering::SeparationSteering(const UnitID & ownerID, float detectionRadius)
{
	mDetectRadius = detectionRadius;
	setOwnerID(ownerID);
	mpSeekSteering = new SeekSteering(ownerID, ZERO_VECTOR2D);
}

SeparationSteering::~SeparationSteering()
{
	delete mpSeekSteering;
}

Steering * SeparationSteering::getSteering()
{
	//set up
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	auto data = pOwner->getPhysicsComponent()->getData();

	//Find location
	Vector2D targetLoc = getVectorAwayFromUnits(
		getUnitsInRadius(
			pOwner->getPositionComponent()->getPosition(),
			mDetectRadius,
			gpGame->getUnitManager()->getAllUnits() //cache this in steering.h to speed up performcance
		),
		pOwner->getPositionComponent()->getPosition()
	);

	setTargetLoc(targetLoc);

	//Seek location
	mpSeekSteering->setTargetLoc(targetLoc);
	data = mpSeekSteering->getSteering()->getData();

	this->mData = data;
	return this;
}

Vector2D SeparationSteering::getVectorAwayFromUnits(std::vector<Vector2D>* unitLocations, const Vector2D& selfLoc)
{
	Vector2D away = Vector2D(-200, -200);
	for (std::vector<Vector2D>::iterator it = unitLocations->begin();
		it != unitLocations->end(); it++) {
		away += (*it - selfLoc);
	}
	if (unitLocations->size() > 0) {
		away *= (1.0 / unitLocations->size());
	}
	return away*-1;
}
