#pragma once
#include <Trackable.h>
class DataLoader : public Trackable
{
public:
	void loadData();
private:
	const std::string mFilePath = "data.txt";
	int stoi(std::string str);
};