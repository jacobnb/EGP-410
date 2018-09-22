#include <Trackable.h>
#include "Steering.h"

class SeekSteering;
class FaceSteering;
class WanderSteering : public Steering
{
public:
	//need to pass radius and center?
	WanderSteering(const UnitID& ownerID, const float& radius);
	~WanderSteering();
protected:
	virtual Steering* getSteering();
private:
	float mWanderOffset = 100.0f;
	float mWanderRate = 10.0f;
	float mWanderRadius;
	Vector2D getTarget();
	SeekSteering* mpSeekSteering;
};