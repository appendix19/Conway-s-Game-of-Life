#include "heap_monitor.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Field
{
private:
	vector <int> pattern; //vector zivych buniek, reprezentujuci sucasny vzor pola
	int x;				  //pocet stlpcov
	int y;			      //pocet riadkov

public:
	void generateRandomPattern ();     //vytvorenie nahodneho vzoru
	void nextGeneration();
	void display ();                   //vypise momentalny stav pola
	Field (int, int);                  //konstruktor pre vytvorenie prazdneho pola
	~Field ();
};

