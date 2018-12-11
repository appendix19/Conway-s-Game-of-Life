#include "Field.h"

Field::Field (int x, int y)
{
	this->x = x;
	this->y = y;	
}

void Field::generateRandomPattern () {

	int randomLiveCell = 0;
	vector <int> randomLiveCells;
	srand (time (0));
	
	//do randomLiveCells sa vygeneruju nahodne 0 a 1
	for (int i = 0; i < x*y; i++) {
		randomLiveCell = rand () % 2;
		randomLiveCells.push_back (randomLiveCell);
		cout << randomLiveCells [i] << endl;
	}

	//vector randomLiveCells sa prekonvertuje do vectoru pattern
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			
		}
	}
}

void Field::display() {
	
}

Field::~Field()
{
}
