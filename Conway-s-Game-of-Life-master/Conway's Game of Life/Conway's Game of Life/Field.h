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
	int x;				  //pocet riadkov
	int y;			      //pocet stlpcov

public:
	void setX (int x);
	void setY (int y);	
	void clearPattern ();
	void generateRandomPattern ();              //vytvorenie nahodneho vzoru
	void nextGeneration();                      //dalsia iteracia
	void display ();                            //vypise momentalny stav pola
	void manualInsert();                        //rucne vkladanie zivych buniek
	bool checkCell (int riadok, int stlpec);    //true ak bunka na zadanych suradniciach nie je ziva
	Field (int, int);                           //konstruktor pre vytvorenie prazdneho pola
	~Field ();
};

