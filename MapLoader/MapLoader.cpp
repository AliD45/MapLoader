#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "MapLoader.h"
#include "Map.h"

using namespace std;

MapLoader::MapLoader(string filePath) {
    loadedMap = new Map();
    mapName = filePath;
    ReadMapFile(filePath);
}

MapLoader::MapLoader(const MapLoader& mapLoader) {

    loadedMap = mapLoader.getMap();
    mapName = mapLoader.getMapName();
}

MapLoader::~MapLoader() {
    delete loadedMap;
}

Map* MapLoader::getMap() const {
    return loadedMap;
}

string MapLoader::getMapName() const{
    return mapName;
}

void MapLoader::ReadMapFile(string filePath) {
    string line;
    ifstream map(filePath);
    const char* t = " \t\n\r\f\v";
    bool continentFlag = false, territoryFlag = false, bordersFlag = false;

    if (map.is_open())
    {
        while (getline(map, line))
        {
            if (line == "[continents]") { //Start reading Continents
                continentFlag = true;
                while(getline(map, line) && !line.empty()){ //Stop reading when empty line is found
                    line.erase(line.find_last_not_of(t) + 1); //remove all sapces a the end of line.
                    CreateContinent(line);
                }
            }

            if (line == "[countries]") { //Start reading Countries
                territoryFlag = true;
                while (getline(map, line) && !line.empty()) { //Stop reading when empty line is found
                    line.erase(line.find_last_not_of(t) + 1); //remove all sapces a the end of line.
                    CreateTerritory(line);
                }
            }

            if (line == "[borders]") { //Start reading Boundries/Connections
                bordersFlag = true;
                while (getline(map, line) && !line.empty()) { //Stop reading when empty line is found
                    line.erase(line.find_last_not_of(t) + 1); //remove all sapces a the end of line.
                    createConnections(line);
                }
            }            
        }
        map.close();//close file.

        if (!continentFlag || !territoryFlag || !bordersFlag) {
            cout << "Invalid Map File. Please load a Valid map file" << endl;
            cout << "Missing Continents, Countries OR Borders" << endl;
            exit(1);
        }


        for (int i = 0; i < continents.size(); i++) {

            for (int j = 0; j < continents[i].getNumberTerritories(); j++) {
                string terrName = continents[i].getTerritories()[j].getTerritoryName();
                auto it = find_if(territories.begin(), territories.end(), [&terrName](const Territory& obj) {return obj.getTerritoryName() == terrName; }); //Find match in oerder link connections 

                if(it != territories.end()) // if match is found
                {
                    continents[i].getTerritories()[j] = it[0];// reassign Territories respectively.
                }
            }

            loadedMap->addContinent(continents.at(i));// Add Continent to Map object
        }
    }
    else cout << "Unable to open file";
}


//Creates the Continents from the map file line.
void MapLoader::CreateContinent(string line) {
    
    vector<string> data;
    Continent continent;
    size_t current, previous = 0;
    current = line.find(' ');//find the space between each field
    while (current != string::npos) {//Loop until end of line
        data.push_back(line.substr(previous, current - previous)); //Get current field
        previous = current + 1;
        current = line.find(' ', previous); //update space position
    }
    if (previous < line.size())
        data.push_back(line.substr(previous));//Last element in line

    if (data.size() != 3) {
        cout << "Invalid Map File. Please load a Valid map file" << endl;
        exit(1);
    }

    continent.setContinentName(data[0]); //Set Continent name from Field
    continents.push_back(continent); //Add it to vector
}

//Creates the Territory from the map file line.
void MapLoader::CreateTerritory(string line) {

    vector<string> data;
    Territory territory;
    size_t current, previous = 0;
    current = line.find(' ');//find the space between each field
    while (current != string::npos) {//Loop until end of line
        data.push_back(line.substr(previous, current - previous));//Get current field
        previous = current + 1;
        current = line.find(' ', previous);//update space position   
    }
    if (previous < line.size())
        data.push_back(line.substr(previous));//Last element in line

    if (data.size() != 5) {
        cout << "Invalid Map File. Please load a Valid map file" << endl;
        exit(1);
    }

    territory.setTerritoryName(data[1]);//Set Territory name from Field
    territories.push_back(territory);
    try
    {
        int i = stoi(data[2]) - 1;//Get Continent Index from line field
        if (continents.size() == 0) {
            cout << "Invalid Map File. Please load a Valid map file" << endl;
            cout << "Missing Continents" << endl;
            exit(1);
        }else {
            continents[i].addTerritory(territory);//Add correspoding Territory to its Continent
        }
    }
    catch (invalid_argument const& e)//incase data field is not an integer (Invalid Map)
    {
        cout << "Bad input: invalid_argument thrown" << '\n';
        cout << "Please make sure Map file is Valid" << '\n';
    }
    catch (out_of_range const& e)
    {
        cout << "Integer overflow: out_of_range thrown" << '\n';
    }
}

//Creates & sets the Connections from the map file line.
void MapLoader::createConnections(string line) {

    vector<string> data;
    Territory territory;
    size_t current, pos, previous = 0;
    pos = line.find(' ');
    current = line.find(' ');
      
    try
    {
        int terrIndex = stoi(line.substr(0, current)) - 1; //Get index of Territory to establish connections
        string con = line.substr(current+1); //Corresponding connections

        while (pos != string::npos) {
            data.push_back(con.substr(previous, pos - previous));
            previous = pos + 1;
            pos = con.find(' ', previous);
        }
        if(previous < con.size())
            data.push_back(con.substr(previous));//Last element in line

        string* connection = new string[data.size()];
        for (int i = 0; i < data.size(); i++) {
            connection[i] = data.at(i);
        }

        if (territories.size() == 0) {
            cout << "Invalid Map File. Please load a Valid map file" << endl;
            cout << "Missing Territories" << endl;
            exit(1);
        }
        else {
            territories[terrIndex].setConnections(data.size(), connection);// Set Territory Connections.
        }
    }
    catch (std::invalid_argument const& e)
    {
        std::cout << "Bad input: std::invalid_argument thrown" << '\n';
    }
    catch (std::out_of_range const& e)
    {
        std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
    }

}

//Overload definitions
MapLoader& MapLoader::operator=(const MapLoader& m)
{
    if (this != &m)
    {
        this->mapName = m.mapName;

        this->loadedMap = m.loadedMap;
    }
    return *this;
}

ostream& operator<< (ostream& out, const MapLoader& m)
{
    out << "Displaying Map Loaded By MapLoader " << m.getMapName() << endl;
    out << *m.getMap() << endl;

    return out;
}
