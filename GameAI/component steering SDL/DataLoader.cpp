#include "DataLoader.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include "FlockMessage.h"

void DataLoader::loadData()
{
	std::ifstream dataStream;
	dataStream.open(mFilePath, std::ifstream::in);
	assert(dataStream.is_open());

	std::string str;

	std::getline(dataStream, str, ':');
	std::getline(dataStream, str, ',');
	std::string mBikeOnePath = str;

	//Cohesion Factor
	//Separation Factor
	//Alignment Factor
	//Wander Factor
	//Cohesion Radius
	//Alignment Radius
	//Separation Radius

}

int DataLoader::stoi(std::string str)
{
	int num = 0;
	try
		//https://stackoverflow.com/questions/18534036/checking-the-int-limits-in-stoi-function-in-c
	{
		num = stoi(str);
	}
	catch (std::invalid_argument& e)
	{
		e; //deals with compiler warning
		std::cout << "Error in data loading";
		return false;
	}
	catch (std::out_of_range& e)
	{
		e;//deals with compiler warning
		std::cout << "Error in data loading";
		return false;
	}
	return 0;
}
