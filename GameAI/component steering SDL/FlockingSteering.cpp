#include "FlockingSteering.h"
#include "AlignSteering.h"
#include "CohesionSteering.h"
#include "SeparationSteering.h"
#include "WanderSteering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

FlockingSteering::FlockingSteering(const UnitID & ownerID)
{
	setOwnerID(ownerID);
	mpAlignSteer = new AlignSteering(ownerID);
	mpCohesionSteer = new CohesionSteering(ownerID);
	mpSeparationSteer = new SeparationSteering(ownerID);
	mpWanderSteer = new WanderSteering(ownerID);
}

FlockingSteering::~FlockingSteering()
{
	delete mpAlignSteer;
	delete mpCohesionSteer;
	delete mpSeparationSteer;
	delete mpWanderSteer;
}

void FlockingSteering::incrementCohesionRadius(float toAdd)
{
	mpCohesionSteer->incrementRadius(toAdd);
}

void FlockingSteering::incrementAlignRadius(float toAdd)
{
	mpAlignSteer->incrementRadius(toAdd);
}

void FlockingSteering::incrementSeparationRadius(float toAdd)
{
	mpSeparationSteer->incrementRadius(toAdd);
}

float FlockingSteering::getCohesionRadius()
{
	return mpCohesionSteer->getRadius();
}

float FlockingSteering::getAlignRadius()
{
	return mpAlignSteer->getRadius();
}

float FlockingSteering::getSeparationRadius()
{
	return mpSeparationSteer->getRadius();
}

Steering * FlockingSteering::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	auto data = pOwner->getPhysicsComponent()->getData();
	auto cohesionVel = mpCohesionSteer->getSteering()->getData().acc;
	auto separationVel = mpSeparationSteer->getSteering()->getData().acc;
	auto alignVel = mpAlignSteer->getSteering()->getData().acc;
	auto wanderVel = mpWanderSteer->getSteering()->getData().acc;
	data.acc = cohesionVel * mCohesionMult
		+ separationVel * mSeparationMult
		+ alignVel * mAlignMult
		+ wanderVel * mWanderMult;

	//I think all the steerings include face (through seek) but if not, add face here.
	this->mData = data;
	return this;
}
