#include <Trackable.h>
#include "Steering.h"

class SeekSteering;
class FaceSteering;
class WanderSteering : public Steering
{
public:
	friend class WanderAndChaseSteering;
	//need to pass radius and center?
	WanderSteering(const UnitID& ownerID, const float& radius = 100.0, float wanderOffset = 100.0, float wanderRate = 10.0);
	~WanderSteering();
protected:
	virtual Steering* getSteering();
private:
	float mWanderOffset;
	float mWanderRate;
	float mWanderRadius;
	Vector2D getTarget();
	SeekSteering* mpSeekSteering;
};