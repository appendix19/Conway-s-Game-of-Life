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

	//vector randomLiveCells sa prekonvertuje do vector pattern
	for (int i = 0; i < x*y; i++) {
		if (randomLiveCells [i] == 1) {
			this->pattern.push_back (i);			
		}
	}

	//vypis pattern
	cout << endl;
	cout << "Prekonvertovany vector: " << endl;
	for (int i = 0; i < pattern.size(); i++) {
		cout << this->pattern[i] << endl;
	}
	
}

void Field::display () {
	if (!this->pattern.empty ()) {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				cout << 0 << ' ';
			}
			cout << endl;
		}
	}
	else {

	}
}

Field::~Field()
{
}
