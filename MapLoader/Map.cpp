#include "Map.h"


//////////////////////////
// TERRITORY DEFINTIONS //
//////////////////////////

//Constructor and destructor definitions
Territory::Territory()
{
	territoryName = new string("");
	ownerName = new string("");
	armiesCount = new int(0);
	numberOfConnections = new int(0);
	connectedTerritories = NULL;
}

Territory::Territory(const Territory& original)
{
	territoryName = new string(original.getTerritoryName());
	ownerName = new string(original.getOwnerName());
	armiesCount = new int(original.getArmiesCount());
	numberOfConnections = new int(original.getNumberConnections());

	connectedTerritories = new string[*numberOfConnections];

	string* tArray = original.getConnectedTerritories();

	for (int i = 0; i < *numberOfConnections; i++)
	{
		connectedTerritories[i] = tArray[i];
	}
}

Territory::~Territory()
{
	delete territoryName;
	delete ownerName;
	delete armiesCount;
	delete numberOfConnections;
	delete[]connectedTerritories;
}


//Getter and setter definitions
string Territory::getTerritoryName() const
{
	return *this->territoryName;
}

bool Territory::setTerritoryName(string name)
{
	bool flag = *this->territoryName != name;

	if (flag)
	{
		*this->territoryName = name;
	}

	return flag;
}

string Territory::getOwnerName() const
{
	return *this->ownerName;
}

bool Territory::setOwnerName(string owner)
{
	bool flag = *this->ownerName != owner;

	if (flag)
	{
		*this->ownerName = owner;
	}

	return flag;
}

int Territory::getArmiesCount() const
{
	return *this->armiesCount;
}

bool Territory::setArmiesCount(int armies)
{
	bool flag = *this->armiesCount != armies;

	if (flag)
	{
		*this->armiesCount = armies;
	}

	return flag;
}

int Territory::getNumberConnections() const
{
	return *this->numberOfConnections;
}

string* Territory::getConnectedTerritories() const
{
	return this->connectedTerritories;
}

bool Territory::setConnections(int size, const string* t)
{
	bool flag = this->connectedTerritories != t;

	if (flag)
	{
		*this->numberOfConnections = size;

		this->connectedTerritories = new string[size];

		for (int i = 0; i < size; i++)
		{
			this->connectedTerritories[i] = t[i];
		}
	}

	return flag;
}

// This function adds a single connection to a territory.
bool Territory::addConnection(const string& tName)
{
	// Flag for return.
	bool flag = true;

	// Check that no other territory of that name is connected
	for (int i = 0; i < *this->numberOfConnections && flag; i++)
	{
		flag = !(this->connectedTerritories[i] == tName);
	}

	if (flag)
	{
		// Clone the old array
		string* cloneArray = new string[*this->numberOfConnections];

		for (int j = 0; j < *this->numberOfConnections; j++)
		{
			cloneArray[j] = this->connectedTerritories[j];
		}

		// Delete and reassign the connection list with an additional space reserved
		delete[] this->connectedTerritories;
		this->connectedTerritories = new string[++ * this->numberOfConnections];

		// Copy the cloned array back and add the new connection
		for (int k = 0; k < *this->numberOfConnections; k++)
		{
			if (k != *this->numberOfConnections - 1)
			{
				this->connectedTerritories[k] = cloneArray[k];
			}
			else
			{
				this->connectedTerritories[k] = tName;
			}
		}

		delete[] cloneArray;
	}

	return flag;
}


//Overload definitions
Territory& Territory::operator= (const Territory& t)
{
	if (this != &t)
	{
		this->territoryName = new string(t.getTerritoryName());
		this->ownerName = new string(t.getOwnerName());
		this->armiesCount = new int(t.getArmiesCount());
		this->numberOfConnections = new int(t.getNumberConnections());

		this->connectedTerritories = new string[this->getNumberConnections()];

		string* tArray = t.getConnectedTerritories();

		for (int i = 0; i < *this->numberOfConnections; i++)
		{
			this->connectedTerritories[i] = tArray[i];
		}
	}

	return *this;
}

ostream& operator<< (ostream& out, const Territory& t)
{
	out << "       " << "Territory name: " << t.getTerritoryName() << endl;
	out << "       " << "Owner: " << t.getOwnerName() << endl;
	out << "       " << "Number of Armies: " << t.getArmiesCount() << endl;
	out << "       " << "Connected territories(" << t.getNumberConnections() << "):" << endl;

	string* territories = t.getConnectedTerritories();

	out << "       ";

	for (int i = 0; i < t.getNumberConnections(); i++)
	{
		out << territories[i] << ", ";

		if (i % 3 == 0 && i != 0)
		{
			out << endl << "       ";
		}
	}

	return out << endl;
}


//////////////////////////
// CONTINENT DEFINTIONS //
//////////////////////////


//Constructor and destructor definitions
Continent::Continent()
{
	continentName = new string("");
	numberOfTerritories = new int(0);
	territories = NULL;
}

Continent::Continent(const Continent& original)
{
	continentName = new string(original.getContinentName());
	numberOfTerritories = new int(original.getNumberTerritories());
	territories = new Territory[*numberOfTerritories];

	Territory* tArray = original.getTerritories();

	for (int i = 0; i < *numberOfTerritories; i++)
	{
		territories[i] = tArray[i];
	}
}

Continent::~Continent()
{
	delete continentName;
	delete numberOfTerritories;
	delete[]territories;
}


//Getter and setter definitions
string Continent::getContinentName() const
{
	return *this->continentName;
}

bool Continent::setContinentName(const string name)
{
	bool flag = *this->continentName != name;

	if (flag)
	{
		*this->continentName = name;
	}

	return flag;
}

int Continent::getNumberTerritories() const
{
	return *this->numberOfTerritories;
}

Territory* Continent::getTerritories() const
{
	return this->territories;
}

bool Continent::setTerritories(int size, const Territory* territories)
{
	bool flag = this->territories != territories;

	if (flag)
	{
		*this->numberOfTerritories = size;

		this->territories = new Territory[size];

		for (int i = 0; i < size; i++)
		{
			this->territories[i] = territories[i];
		}
	}

	return flag;
}

// This function adds a single territory to a continent
bool Continent::addTerritory(const Territory& t)
{
	// Flag for return
	bool flag = true;

	// Check that the continent doesn't already contain a territory of that name
	for (int i = 0; i < *this->numberOfTerritories && flag; i++)
	{
		flag = !(this->territories[i].getTerritoryName() == t.getTerritoryName());
	}

	if (flag)
	{
		// Clone the old territory array, delete and remake it with the new size and copy the information back
		Territory* cloneArray = new Territory[*this->numberOfTerritories];

		for (int j = 0; j < *this->numberOfTerritories; j++)
		{
			cloneArray[j] = this->territories[j];
		}

		delete[] this->territories;
		this->territories = new Territory[++ * this->numberOfTerritories];

		for (int k = 0; k < *this->numberOfTerritories; k++)
		{
			if (k != *this->numberOfTerritories - 1)
			{
				this->territories[k] = cloneArray[k];
			}
			else
			{
				this->territories[k] = t;
			}
		}

		delete[] cloneArray;
	}

	return flag;
}


//Overload definitions
Continent& Continent::operator= (const Continent& c)
{
	if (this != &c)
	{
		this->continentName = new string(c.getContinentName());
		this->numberOfTerritories = new int(c.getNumberTerritories());

		this->territories = new Territory[this->getNumberTerritories()];

		Territory* cArray = c.getTerritories();

		for (int i = 0; i < *this->numberOfTerritories; i++)
		{
			this->territories[i] = cArray[i];
		}
	}

	return *this;
}

ostream& operator<< (ostream& out, const Continent& c)
{
	out << "Continent name: " << c.getContinentName() << endl;
	out << "Territories(" << c.getNumberTerritories() << "):" << endl;

	Territory* territories = c.getTerritories();

	for (int i = 0; i < c.getNumberTerritories(); i++)
	{
		out << territories[i] << endl;
	}

	return out;
}


//////////////////////////
//	MAP DEFINTIONS      //
//////////////////////////


//Constructor and destructor definitions
Map::Map()
{
	numberOfContinents = new int(0);
	continents = NULL;
	territoryAdjacencyMatrix = NULL;
}

Map::Map(const Map& original)
{
	numberOfContinents = new int(original.getNumberContinents());
	continents = new Continent[*numberOfContinents];

	Continent* cArray = original.getContinents();

	for (int i = 0; i < *numberOfContinents; i++)
	{
		continents[i] = cArray[i];
	}

	buildTerritoryAdjacencyMatrix();
}

Map::~Map()
{
	for (int i = 0; i < territoryAdjacencyMatrix->size(); i++)
	{
		territoryAdjacencyMatrix->at(i).empty();
	}
	delete territoryAdjacencyMatrix;
	delete numberOfContinents;
	delete[] continents;
}


//Getter and setter definitions
int Map::getNumberContinents() const
{
	return *this->numberOfContinents;
}

Continent* Map::getContinents() const
{
	return this->continents;
}

bool Map::setContinents(int size, const Continent* continents)
{
	bool flag = this->continents != continents;

	if (flag)
	{
		*this->numberOfContinents = size;

		this->continents = new Continent[size];

		for (int i = 0; i < size; i++)
		{
			this->continents[i] = continents[i];
		}
	}

	buildTerritoryAdjacencyMatrix();

	return flag;
}

// This function adds a continent to a map, using the same logic as
// Continent::addTerritory and Territory::addConnection
bool Map::addContinent(const Continent& c)
{
	bool flag = true;

	for (int i = 0; i < *this->numberOfContinents && flag; i++)
	{
		flag = !(this->continents[i].getContinentName() == c.getContinentName());
	}

	if (flag)
	{
		Continent* cloneArray = new Continent[*this->numberOfContinents];

		for (int j = 0; j < *this->numberOfContinents; j++)
		{
			cloneArray[j] = this->continents[j];
		}

		delete[] this->continents;
		this->continents = new Continent[++ * this->numberOfContinents];

		for (int k = 0; k < *this->numberOfContinents; k++)
		{
			if (k != *this->numberOfContinents - 1)
			{
				this->continents[k] = cloneArray[k];
			}
			else
			{
				this->continents[k] = c;
			}
		}

		delete[] cloneArray;
	}

	buildTerritoryAdjacencyMatrix();

	return flag;
}

int Map::getNumberTerritories() const
{
	int territoryCount = 0;

	for (int i = 0; i < getNumberContinents(); i++)
	{
		territoryCount += continents[i].getNumberTerritories();
	}

	return territoryCount;
}

Territory* Map::getTerritories() const
{
	int territoryNumber = getNumberTerritories();

	Territory* territories = new Territory[territoryNumber];
	int tCount = 0;

	for (int k = 0; k < getNumberContinents() && tCount < territoryNumber; k++)
	{
		for (int l = 0; l < continents[k].getNumberTerritories() && tCount < territoryNumber; l++)
		{
			territories[tCount] = continents[k].getTerritories()[l];
			tCount++;
		}
	}

	return territories;
}


// Matrix building and verification function definitions
void Map::buildTerritoryAdjacencyMatrix()
{
	// If a matrix already exists, delete it and remake it
	int territoryNumber = 0;

	if (territoryAdjacencyMatrix != NULL)
	{
		territoryNumber = territoryAdjacencyMatrix->size();

		for (int i = 0; i < territoryNumber; i++)
		{
			territoryAdjacencyMatrix->at(i).empty();
		}
		delete territoryAdjacencyMatrix;
	}

	territoryAdjacencyMatrix = new vector<vector<string>>;

	// For each territory, place itself in the first column space of the matrix,
	// as our logic assumes that the beginnings of each row contains the name of the row
	for (int j = 0; j < getNumberTerritories(); j++)
	{
		Territory targetedTerritory = getTerritories()[j];
		vector<string> row;

		row.push_back(targetedTerritory.getTerritoryName());

		// Place the connections for the targeted territory after it in the line
		for (int k = 0; k < targetedTerritory.getNumberConnections(); k++)
		{
			row.push_back(targetedTerritory.getConnectedTerritories()[k]);
		}
		territoryAdjacencyMatrix->push_back(row);
	}
}

// Verification function, checks that the map is a connected
// graph, that continents are connected sub-graphs and
// that each territory belong to one and only one continent
bool Map::validate() const
{
	// Validity flag
	bool validMap = true;

	cout << "Validating..." << endl;

	// Count number of territories
	int territoryCount = getNumberTerritories();

	// Count the continents
	int continentCount = getNumberContinents();

	///////////// Verify that each territory belongs to one and only one continent /////////////
	Territory* territories = getTerritories();
	Continent* continents = getContinents();
	int count = 0;
	for (int k = 0; k < territoryCount && validMap; k++)
	{
		count = 0;

		for (int l = 0; l < continentCount; l++)
		{
			for (int m = 0; m < continents[l].getNumberTerritories(); m++)
			{
				if (territories[k].getTerritoryName() == continents[l].getTerritories()[m].getTerritoryName())
				{
					count++;
				}
			}
		}

		if (count > 1)
		{
			cout << "Validation failed. Territory '" << territories[k].getTerritoryName()
				<< "' belongs to more than one continent." << endl;
			validMap = false;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////


	/////////////  Verify that the map is a connected graph ///////////////////////////////////
	// Instantiate visited array
	bool* visitedTerritory = new bool[territoryCount];

	for (int i = 0; i < territoryCount; i++)
	{
		visitedTerritory[i] = false;
	}

	// Check connectivity
	if (validMap)
	{
		validMap = checkConnectivity(0, visitedTerritory, territoryAdjacencyMatrix);

		if (!validMap)
		{
			cout << "Validation failed. Map not connected." << endl;
		}
	}

	delete[] visitedTerritory;
	/////////////////////////////////////////////////////////////////////////////////////////


	///////////// Verify that each continent is a connected sub-graph ///////////////////////
	for (int j = 0; j < continentCount && validMap; j++)
	{
		validMap = checkContinentConnectivity(getContinents()[j]);
		if (!validMap)
		{
			cout << "Validation failed. Continent '" << getContinents()[j].getContinentName()
				<< "' is not a connected sub-graph." << endl;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////

	if (validMap)
	{
		cout << "Validation successful." << endl;
	}

	return validMap;
}

// This function performs a depth-first search (DFS) on the adjacency list in order
// to verify connectivity of the list given
bool Map::checkConnectivity(int currentCount, bool* visited, vector<vector<string>>* adjacencyList) const
{
	// Mark current node as visited
	visited[currentCount] = true;
	int targetedNode = currentCount;
	int columns = adjacencyList->at(currentCount).size();

	// Iterate through neighbours of the current node
	for (int j = 0; j < columns; j++)
	{
		string neighbourName = adjacencyList->at(targetedNode).at(j);

		// Find the node that the neighbour is referring to
		for (int k = 0; k < adjacencyList->size(); k++)
		{
			if (adjacencyList->at(k).at(0) == neighbourName)
			{
				currentCount = k;
				break;
			}
		}

		// Check if that neighbour's been visited, if not, call this function recursively
		// for a depth first approach
		if (!visited[currentCount])
		{
			checkConnectivity(currentCount, visited, adjacencyList);
		}
	}

	bool flag = true;

	for (int l = 0; l < adjacencyList->size() && flag; l++)
	{
		if (!visited[l])
		{
			flag = false;
		}
	}

	return flag;
}

bool Map::checkContinentConnectivity(Continent continent) const
{
	// Instantiate a new adjacency list
	vector<vector<string>> continentExclusiveAdjacencies;

	// Fill the adjacency list with only the territories that are part of same continent
	for (int i = 0; i < territoryAdjacencyMatrix->size(); i++)
	{
		for (int j = 0; j < continent.getNumberTerritories(); j++)
		{
			if (territoryAdjacencyMatrix->at(i).at(0) == continent.getTerritories()[j].getTerritoryName())
			{
				continentExclusiveAdjacencies.push_back(territoryAdjacencyMatrix->at(i));
			}
		}
	}

	// Instantiate visited array
	int sizeOfContinentAdjacencies = continentExclusiveAdjacencies.size();
	bool* visitedTerritory = new bool[sizeOfContinentAdjacencies];

	for (int j = 0; j < sizeOfContinentAdjacencies; j++)
	{
		visitedTerritory[j] = false;
	}

	// Call the DFS function
	return checkConnectivity(0, visitedTerritory, &continentExclusiveAdjacencies);
}


//Overload definitions
Map& Map::operator=(const Map& m)
{
	if (this != &m)
	{
		this->numberOfContinents = new int(m.getNumberContinents());

		this->continents = new Continent[this->getNumberContinents()];

		Continent* cArray = m.getContinents();

		for (int i = 0; i < *this->numberOfContinents; i++)
		{
			this->continents[i] = cArray[i];
		}
	}

	this->buildTerritoryAdjacencyMatrix();

	return *this;
}

ostream& operator<< (ostream& out, const Map& m)
{
	out << "Continents(" << m.getNumberContinents() << "):" << endl;

	Continent* continents = m.getContinents();

	for (int i = 0; i < m.getNumberContinents(); i++)
	{
		out << continents[i] << endl << endl;
	}

	return out;
}
