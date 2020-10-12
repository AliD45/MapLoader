#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Map.h"

using namespace std;

class MapLoader
{

public:
	
	//Constructors and Destructors
	MapLoader(string filePath);
	MapLoader(const MapLoader& mapLoader);
	~MapLoader();


	//read map File
	void ReadMapFile(string filePath);

	//Getter, returns Map pointer.
	Map* getMap() const;

	string getMapName() const;

	MapLoader& operator=(const MapLoader& m);

	friend ostream& operator<<(ostream& out, const MapLoader& t);

private:
	Map* loadedMap;
	string mapName;
	vector<Continent> continents;
	vector<Territory> territories;
	void CreateTerritory(string line);
	void CreateContinent(string line);
	void createConnections(string territory);
};

