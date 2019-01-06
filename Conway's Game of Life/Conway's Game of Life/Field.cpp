#include "Field.h"
#include <thread>
#include <algorithm>
#include <windows.h>

Field::Field (int x, int y)
{
	this->x = x;
	this->y = y;
	this->input = false;
	this->pattern = new vector<int>();
}

bool Field::isInVector(int riadok, int stlpec)
{
	int index;
	if (stlpec != -1 || stlpec < x) {
		index = riadok * x + stlpec;
		return (std::find(pattern->begin(), pattern->end(), index) != pattern->end());
	}

	return false;
}

void Field::setX(int x) {
	this->x = x;
}

void Field::setY(int y) {
	this->y = y;
}

void Field::clearPattern() {
	this->pattern->clear();
}


void Field::generateRandomPattern () {

	int randomLiveCell = 0;
	vector <int> randomLiveCells;
	srand (time (0));
	
	//do randomLiveCells sa vygeneruju nahodne 0 a 1
	for (int i = 0; i < x*y; i++) {
		randomLiveCell = rand() % 2;
		randomLiveCells.push_back(randomLiveCell);
	}

	//vector randomLiveCells sa prekonvertuje do vector pattern
	for (int i = 0; i < x*y; i++) {
		if (randomLiveCells [i] == 1) {
			this->pattern->push_back(i);
		}
	}
	
}

void Field::nextGeneration()
{
	vector <int> *newGenerationAliveCells = new vector <int>();
	*newGenerationAliveCells = *pattern;


	if (!this->pattern->empty()) {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {

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

				int indexCell = i * x + j;

			

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

				// Ostava rovnaka
				else if (isCurrentCellAlive)
				{
					//newGenerationAliveCells->push_back(indexCell);
				}

			}
		}
	}

	*pattern = *newGenerationAliveCells;
	delete newGenerationAliveCells;

}

void Field::display () {
	
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {

			int index = i * x + j;

			if (std::find(pattern->begin(), pattern->end(), index) != pattern->end())
			{
				printf (" o"); //live
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

void Field::simulation() {
	thread first (&Field::run, this);
	thread second (&Field::stop, this);

	first.join();
	second.join();	
}

void Field::run() {
	while (!input) {
		system("CLS");
		this->display();
		this->nextGeneration();
		Sleep(100);
	}
	this->input = false;	
}

void Field::stop () {
	int a = 1;
	cin >> a;
	while (a != 0) {
		cin >> a;
	}
	this->input = true;
}

Field::~Field()
{
	delete pattern;
}
