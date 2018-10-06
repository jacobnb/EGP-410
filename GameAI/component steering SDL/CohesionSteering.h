#pragma once
#include <Trackable.h>
#include "Steering.h"
#include <vector>

class Unit;
class SeekSteering;

class CohesionSteering : public Steering
{
public:
	CohesionSteering(const UnitID& ownerID, float detectionRadius = 200);
	~CohesionSteering();
	inline void setRadius(const float detectionRadius) { mDetectRadius = detectionRadius; };
protected:
	virtual Steering* getSteering();
private:
	float mDetectRadius;
	SeekSteering* mpSeekSteering;
	std::vector<Vector2D>* getUnitsInRadius(Vector2D ownerPosit, std::vector<Unit*> allUnits);
	//pass in position and gpGame->getUnitManager()->getAllUnits(); so it's more easily testable.
	Vector2D getCenterOfUnits(std::vector<Vector2D>* unitLocations);
};