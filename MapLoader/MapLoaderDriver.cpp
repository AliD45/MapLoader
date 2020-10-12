#include "MapLoader.h"
using namespace std;


void testSolarMap() {
	MapLoader mapLoader = MapLoader("solar.map");
	cout << mapLoader;
}

void testGoogleMap() {
	MapLoader mapLoader = MapLoader("google.map");
	cout << mapLoader;
}

void testInvalidMap() {
	MapLoader mapLoader = MapLoader("invalidMap.map");
	cout << mapLoader;
}

int main() {

	//testSolarMap();

	//testGoogleMap();

	testInvalidMap();
	
}
