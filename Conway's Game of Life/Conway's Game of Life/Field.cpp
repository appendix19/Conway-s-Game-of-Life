#include "Field.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include "heap_monitor.h"
#include <windows.h>
#include <thread>
#include <mutex>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

Field::Field (int x, int y)
	:bufferMax (10)
{
	this->x = x;
	this->y = y;
	this->pattern = new vector<int>();
	this->simulation = new vector<vector<int>*>();
	this->input = false;	
	this->bufferCur = 0;
	this->bufferQ = (int*) malloc(bufferMax*sizeof(int));
}

bool Field::isInVector(int riadok, int stlpec)
{
	int index;
	if (stlpec != -1 && stlpec < this->y) {

		if (riadok != -1 && riadok < this->x) {
			index = riadok * this->y + stlpec;
			return (std::find(pattern->begin(), pattern->end(), index) != pattern->end());
		}
	}
	return false;
}

void Field::runForward()
{
	this->input = false;
	while (!input) {
		system(CLEAR);
		this->display();

		if (!this->pattern->empty()) {
			vector<int>* novy = new vector<int>;
			*novy = *pattern;
			this->simulation->push_back(novy);
		}

		this->nextGeneration();
		Sleep(50);
	}
}

void Field::runBackward()
{
	this->input = false;
	while (!input) {
		system(CLEAR);
		this->display();
		if (this->simulation->empty()) {
			this->input = true;
			cout << "Backward simulation has finished." << endl;
			cout << "Please, run simulation forward." << endl;
		}
		else {
			vector<int>* novy = pattern;
			delete novy;

			this->pattern = this->simulation->back();
			this->simulation->pop_back();
			Sleep(50);
		}
	}
}


vector<int>* Field::getPattern()
{
	return pattern;
}

void Field::setX(int x) {
	this->x = x;
}

void Field::setY(int y) {
	this->y = y;
}

void Field::clear() {
	this->pattern->clear();
	for (vector<int>* i : *simulation) {
		delete i;
	}
	this->simulation->clear();
}

void Field::clearSimulation()
{
	for (vector<int>* i : *simulation) {
		delete i;
	}
	this->simulation->clear();
}

void Field::generateRandomNumber() { //producent
	int randomLiveCell = 0;	
	srand(time(0));

	for (int i = 0; i < x*y; i++) {		
		randomLiveCell = rand() % 2;
		std::unique_lock <std::mutex> lk (this->mutex);
		if (this->bufferCur == this->bufferMax) {
			notFull.wait (lk);
		}
		this->bufferCur++;
		this->bufferQ [this->bufferCur] = randomLiveCell;				
		lk.unlock ();
		notEmpty.notify_one();		
	}
}

void Field::convertArrayToPattern() {	//konzument
	for (int i = 0; i < x*y; i++) {		
		std::unique_lock <std::mutex> lk(this->mutex);
		if (this->bufferCur == -1) {
			notEmpty.wait(lk);
		}
		if (this->bufferQ [this->bufferCur] == 1) {
			this->pattern->push_back(i);
			this->bufferCur--;
		}
		else {
			this->bufferCur--;
		}
		lk.unlock ();
		notFull.notify_one();
	}
}

void Field::generateRandomPattern () {
	thread first(&Field::generateRandomNumber, this);
	thread second(&Field::convertArrayToPattern, this);

	first.join();
	second.join();
	
	this->clearSimulation(); //celkova simulacia sa resetuje, pretoze vznikol novy vzor
}

void Field::nextGeneration()
{
	vector <int> *newGenerationAliveCells = new vector <int>();
	*newGenerationAliveCells = *pattern;


	if (!this->pattern->empty()) {
		for (int i = 0; i < this->x; i++) {
			for (int j = 0; j < this->y; j++) {

				int aliveNeighbours = 0;
				int index = 0;

				//H¾adanie susedov

				for (int k = -1; k < 2; k++) {
					for (int l = -1; l < 2; l++) {

						if (isInVector(i + k, j + l))
							aliveNeighbours++;
					}
				}

				bool isCurrentCellAlive = isInVector(i, j);

				//Odpoèítam samého seba
				if (isCurrentCellAlive)
				aliveNeighbours--;

				int indexCell = i * this->y + j;

			

				// Bunka zomiera - nedostatocna alebo prilis velka populacia
				if (isCurrentCellAlive && (aliveNeighbours < 2 || aliveNeighbours > 3))
				{
					std::vector<int>::iterator position = std::find(newGenerationAliveCells->begin(), newGenerationAliveCells->end(), indexCell);
					if (position != newGenerationAliveCells->end())
						newGenerationAliveCells->erase(position);
				}

				// Narodi sa nova bunka
				else if (!isCurrentCellAlive && (aliveNeighbours == 3))
				{
					newGenerationAliveCells->push_back(indexCell);
				}

			}
		}
	}

	*pattern = *newGenerationAliveCells;
	delete newGenerationAliveCells;

}

void Field::display () {
	
	for (int i = 0; i < this->x; i++) {
		for (int j = 0; j < this->y; j++) {

			int index = i * this->y + j;

			if (std::find(pattern->begin(), pattern->end(), index) != pattern->end())
			{
				printf(" o"); //live
			}
			else {
				printf(" ."); //dead
			}
		}
		printf("\n"); //printf vypisuje rychlejsie ako cout <<
	}
	
}

void Field::manualInsert()
{
	int riadok = 0;       //x
	int stlpec = 0;       //y
	bool podmienka = false;
	cout << "World dimensions are: " << this->x << "x" << this->y << endl;
	while (!podmienka) {
		cout << "Please, enter the row number: ";
		cin >> riadok;
		if (riadok <= this->x && riadok > 0) {
			podmienka = true;
		}
		else {
			cout << "Row number is out of scope!" << endl;
		}
	}

	podmienka = false;
	while (!podmienka) {
		cout << "Please, enter the column number: ";
		cin >> stlpec;
		if (stlpec <= this->y && stlpec > 0) {
			podmienka = true;
		}
		else {
			cout << "Column number is out of scope!" << endl;
		}
	}
	if (checkCell(riadok, stlpec)) {
		this->pattern->push_back(this->y*(riadok - 1) + (stlpec - 1));
		sort(this->pattern->begin(), this->pattern->end());
	}
	this->clearSimulation();      //celkova simulacia sa resetuje, pretoze vznikol novy vzor
}

bool Field::checkCell(int riadok, int stlpec) {
	int cell = this->y*(riadok - 1) + (stlpec - 1);
	for (int i = 0; i < this->pattern->size(); i++) {
		if (this->pattern->at(i) == cell) {
			return false;
		}
	}
	return true;
}

void Field::patternToFile()
{
	
	for (int i : *pattern) {
		cout << i << endl;
	}

	cout << endl;

}

void Field::addCell(int index)
{
	pattern->push_back(index);	
}


void Field::removeLast() {
	this->pattern->pop_back();
}

void Field::stop()
{
	Sleep(30);
	system("pause");
	this->input = true;

}

void Field::forwardSimulation()
{
	thread first(&Field::runForward, this);
	thread second(&Field::stop, this);

	first.join();
	second.join();
}

void Field::backwardSimulation()
{
	thread first(&Field::runBackward, this);
	thread second(&Field::stop, this);

	first.join();
	second.join();

}


Field::~Field()
{
	clear();
	free ((void*)this->bufferQ);
	delete pattern;
	delete simulation;
}
