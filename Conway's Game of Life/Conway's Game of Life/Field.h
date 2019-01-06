#include "heap_monitor.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Field
{
private:
	vector <int>* pattern;                 //vector zivych buniek, reprezentujuci sucasny vzor pola
	vector <vector <int>*>* simulation;    //vector vsetkych vektorov zo simulacie (potrebny pre spatnu simulaciu)
	int x;				                   //pocet stlpcov
	int y;			                       //pocet riadkov
	bool input;

	bool isInVector (int, int);                  //true ak bunka na zadanych suradniciach je ziva
	bool checkCell (int riadok, int stlpec);     //true ak sa bunka este neneachadza medzi zivymi bunkami 
	void nextGeneration();                       //dalsia iteracia
	void runForward();                           //funkcia pre vlakno (spustenie simulacie)
	void runBackward();                          //funkcia pre vlakno (spustenie simulacie)
	void stop();                                 //funkcia pre vlakno (zastavenie simulacie vstupom od uzivatela)

public:	
	void setX(int x);
	void setY(int y);
	void clearPattern();
	void generateRandomPattern();               //vytvorenie nahodneho vzoru	
	void display();                             //vypise momentalny stav pola
	void manualInsert();                        //rucne vkladanie zivych buniek	
	void forwardSimulation();
	void backwardSimulation();
	
	Field (int, int);                  //konstruktor pre vytvorenie prazdneho pola
	~Field ();
};

