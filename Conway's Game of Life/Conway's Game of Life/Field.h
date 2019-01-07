#include "heap_monitor.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>


using namespace std;

class Field
{
private:
	vector <int>* pattern;					//vector zivych buniek, reprezentujuci sucasny vzor pola
	vector <vector <int>*>* simulation;    //vector vsetkych vektorov zo simulacie (potrebny pre spatnu simulaciu)

	int x;				  //pocet stlpcov
	int y;			      //pocet riadkov

	bool isInVector(int, int); //true ak bunka na zadanych suradniciach nie je ziva
	bool volatile input;
	void runForward();                           //funkcia pre vlakno (spustenie simulacie)
	void runBackward();                          //funkcia pre vlakno (spustenie simulacie)


public:
	vector <int>* getPattern();
	void setX(int x);
	void setY(int y);
	void clear();
	void clearSimulation();
	void generateRandomPattern();              //vytvorenie nahodneho vzoru
	void nextGeneration();                      //dalsia iteracia
	void display();                            //vypise momentalny stav pola
	void manualInsert();                        //rucne vkladanie zivych buniek
	bool checkCell(int riadok, int stlpec);
	void patternToFile();
	void addCell(int index);
	void stop();                     //function for thread
	void forwardSimulation();
	void backwardSimulation();
	Field (int, int);                  //konstruktor pre vytvorenie prazdneho pola
	~Field ();
};

