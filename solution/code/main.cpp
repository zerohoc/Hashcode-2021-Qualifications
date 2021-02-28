#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <windows.h>
#include <algorithm>
#include <map> 

class Street {
public:
	std::string name;
	int length;

	Street(std::string streetName, int par_length)
		: name(streetName), length(par_length)
	{};
};

class Intersection {
public:
	int id;
	std::vector<Street> incomingStreetList;
};

void ReadInputs(std::string & path, std::vector<Intersection> & intersectionList)
{
	std::cout << "ReadInputs Operation Starts!" << std::endl;

	std::ifstream ReadFile(path);
	std::string text;
	std::string line;
	while (ReadFile.good())
	{
		std::getline(ReadFile, line);
		text += line;
		text += "\n";
	}

	std::stringstream stream(text);

	int simDuration = 0; 
	int intersectionNumber = 0;
	int streetNumber = 0;
	int carNumber = 0;
	int reachingScore = 0;

	stream >> simDuration >> intersectionNumber >> streetNumber >> carNumber >> reachingScore;

	intersectionList.resize(intersectionNumber);

	for (int i = 0; i < streetNumber; i++)
	{
		//fills intersection list
		int startIntersection = 0;
		int endIntersection = 0;
		std::string streetName;
		int timeToTravel = 0;

		stream >> startIntersection >> endIntersection >> streetName >> timeToTravel;

		intersectionList[endIntersection].id = endIntersection;
		intersectionList[endIntersection].incomingStreetList.push_back(Street(streetName, timeToTravel));
	}

	for (int i = 0; i < carNumber; i++)
	{

		int pathCount = 0;
		stream >> pathCount;

		for (int j = 0; j < pathCount; j++)
		{
			std::string pathName;
			stream >> pathName;
		}
	}

	ReadFile.close();
}

void HandleTrafficSignals(std::vector<Intersection> & intersectionList, std::vector<std::vector<std::pair<std::string, int>>> & trafficSignalList)
{
	//traverses all incoming streets and 
	//gives every one of them a 1 second green time
	trafficSignalList.resize(intersectionList.size());
	for (int i = 0; i < intersectionList.size(); i++)
	{
		for (int j = 0; j < intersectionList[i].incomingStreetList.size(); j++)
		{
			int greenLightDuration = 1;
			trafficSignalList[i].push_back(
				std::make_pair(intersectionList[i].incomingStreetList[j].name,
					greenLightDuration
				));
		}
	}
}

void WriteOutput(std::string & path, std::vector<std::vector<std::pair<std::string, int>>> & trafficSignalList)
{
	std::ofstream WriteFile(path);
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(WriteFile.rdbuf()); //redirect std::cout to out.txt!

	std::cout << trafficSignalList.size() << std::endl;
	
	for (int i = 0; i < trafficSignalList.size(); i++)
	{
		std::cout << i << std::endl;
		std::cout << trafficSignalList[i].size() << std::endl;
		for (int j = 0; j < trafficSignalList[i].size(); j++)
		{
			std::cout << trafficSignalList[i][j].first << " " << trafficSignalList[i][j].second << std::endl;
		}
	}
	
	std::cout.rdbuf(coutbuf); //reset to standard output again
	WriteFile.close();
}

int main()
{
	std::vector<std::string> paths{
		"a",
		"b",
		"c",
		"d",
		"e",
		"f",
	};

	int fileCount = 1;
	for (std::string path : paths)
	{
		std::vector<Intersection> intersectionList;
		ReadInputs(path, intersectionList);
		
		std::vector<std::vector<std::pair<std::string, int>>> trafficSignalList;
		HandleTrafficSignals(intersectionList, trafficSignalList);

		std::string outPath = path + "_out";
		WriteOutput(outPath, trafficSignalList);

		std::cout << "File # " << fileCount++ << " Done!" << std::endl << std::endl;

		std::cout << "-------------------------------" << std::endl << std::endl;
	}
}
