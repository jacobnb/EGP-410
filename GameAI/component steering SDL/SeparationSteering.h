#pragma once
#include <Trackable.h>
#include "Steering.h"
#include <vector>

class Unit;
class SeekSteering;

class SeparationSteering : public Steering
{
public:
	SeparationSteering(const UnitID& ownerID, float detectionRadius = 100);
	~SeparationSteering();
	inline void setRadius(const float detectionRadius) { mDetectRadius = detectionRadius; };
protected:
	virtual Steering* getSteering();
private:
	float mDetectRadius;
	SeekSteering* mpSeekSteering;
	Vector2D getVectorAwayFromUnits(std::vector<Vector2D>* unitLocations, const Vector2D& selfLoc);
};