Skip to content
Search or jump to…

Pulls
Issues
Marketplace
Explore

@AliD45
Your GitHub academic discount coupon has expired
If you’re still eligible, you may re - apply.
If you’re no longer eligible, you may either update your payment information, or downgrade your account.
If you have any questions, please contact GitHub Education.

J - Snape
/
comp345
Private
1
0
0
Code
Issues
Pull requests
Actions
Projects
Security
Insights
comp345 / MapDriver / Map.h
@J - Snape
J - Snape Added final validation check and divided MapDriver into 3 test cases
Latest commit 07b9025 2 days ago
History
1 contributor
117 lines(92 sloc)  2.84 KB

#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Territory
{
public:

	//Constructors and destructor
	Territory();
	Territory(const Territory& original);
	~Territory();

	// Getter and setter functions
	// Every setter returns a boolean indicating success or failure of
	// the set.
	string getTerritoryName() const;
	bool setTerritoryName(string name);

	string getOwnerName() const;
	bool setOwnerName(string owner);

	int getArmiesCount() const;
	bool setArmiesCount(int armies);


	int getNumberConnections() const;
	string* getConnectedTerritories() const;
	bool setConnections(int size, const string* t);
	bool addConnection(const string& tName);

	//Operator overloads
	Territory& operator=(const Territory& t);
	friend ostream& operator<<(ostream& out, const Territory& t);


private:
	string* territoryName;
	string* ownerName;
	int* armiesCount;
	int* numberOfConnections;
	string* connectedTerritories;
};

class Continent
{
public:

	//Constructors and destructor
	Continent();
	Continent(const Continent& original);
	~Continent();

	// Getter and setter functions
	// Every setter returns a boolean indicating success or failure of
	// the set.
	string getContinentName() const;
	bool setContinentName(const string name);

	int getNumberTerritories() const;
	Territory* getTerritories() const;
	bool setTerritories(int size, const Territory* territories);
	bool addTerritory(const Territory& t);

	//Operator overloads
	Continent& operator=(const Continent& t);
	friend ostream& operator<<(ostream& out, const Continent& t);

private:
	string* continentName;
	int* numberOfTerritories;
	Territory* territories;
};

class Map
{
public:

	//Constructors and destructor
	Map();
	Map(const Map& original);
	~Map();

	// Getter and setter functions
	// Every setter returns a boolean indicating success or failure of
	// the set.
	int getNumberContinents() const;
	Continent* getContinents() const;
	bool setContinents(int size, const Continent* continents);
	bool addContinent(const Continent& c);

	int getNumberTerritories() const;
	Territory* getTerritories() const;

	// Matrix building and verification functions
	// Called during any insertion in order to refresh the adjacency matrix
	void buildTerritoryAdjacencyMatrix();
	// Generic DFS recursive function that tests for connectivity of a given adjacency matrix
	bool checkConnectivity(int currentCount, bool* visitationList, vector<vector<string>>* territoryAdjacencyList) const;
	// Specific continent connectivity verification, calls checkConnectivity
	bool checkContinentConnectivity(Continent continent) const;

	// Verification function
	bool validate() const;

	//Operator overloads
	Map& operator=(const Map& m);
	friend ostream& operator<<(ostream& out, const Map& t);

private:
	int* numberOfContinents;
	Continent* continents;
	vector<vector<string>>* territoryAdjacencyMatrix;
};
