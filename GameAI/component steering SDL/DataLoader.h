#pragma once
#include <Trackable.h>
class DataLoader : public Trackable
{
public:
	void loadData();
	void writeData();
	inline float getStartingCohesionFactor() { return mCohesionFactor; };
	inline float getStartingSeparationFactor() { return mSeparationFactor; };
	inline float getStartingAlignmentFactor() { return mAlignmentFactor; };
	inline float getStartingWanderFactor() { return mWanderFactor; };
	inline float getStartingCohesionRadius() { return mCohesionRadius; };
	inline float getStartingAlignmentRadius() { return mAlignmentRadius; };
	inline float getStartingSeparationRadius() { return mSeparationRadius; };
private:
	const std::string mFilePath = "data.txt";
	float stringToFloat(std::string str);

	float mCohesionFactor;
	float mSeparationFactor;
	float mAlignmentFactor;
	float mWanderFactor;
	float mCohesionRadius;
	float mAlignmentRadius;
	float mSeparationRadius;
};