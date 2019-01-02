#include "Field.h"
#include <algorithm>

Field::Field (int x, int y)
{
	this->x = x;
	this->y = y;	
}

void Field::setX (int x) {
	this->x = x;
}

void Field::setY (int y) {
	this->y = y;	
}

void Field::clearPattern() {
	this->pattern.clear ();
}

void Field::generateRandomPattern () {

	int randomLiveCell = 0;
	vector <int> randomLiveCells;
	srand (time (0));
	
	//do randomLiveCells sa vygeneruju nahodne 0 a 1
	for (int i = 0; i < x*y; i++) {
		randomLiveCell = rand () % 2;
		randomLiveCells.push_back (randomLiveCell);		
	}

	//vector randomLiveCells sa prekonvertuje do vector pattern
	for (int i = 0; i < x*y; i++) {
		if (randomLiveCells [i] == 1) {
			this->pattern.push_back (i);			
		}
	}	
}

void Field::nextGeneration()
{
	vector <int> newGenerationDeadCells;
	vector <int> newGenerationAliveCells;

	if (!this->pattern.empty()) {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {

				int aliveNeigbours = 0;
				int index = 0;

				//H¾adanie ¾avého suseda

				int riadokLaveho = 0;
				int stlpecLaveho = 0;

				if (j - 1 < 0 && i - 1 < 0) {
					stlpecLaveho = -1;
					riadokLaveho = -1;
				}

				if (j - 1 < 0 && i - 1 >= 0) {
					stlpecLaveho = x;
					riadokLaveho = i - 1;
				}

				if (j - 1 >= 0 && i >= 0) {
					stlpecLaveho = j - 1;
					riadokLaveho = i;
				}

				if (stlpecLaveho != -1) {
					index = riadokLaveho * x + stlpecLaveho;
					try {
						if (std::find(pattern.begin(), pattern.end(), index) != pattern.end()) {
							aliveNeigbours++;
						}
					}
					catch (std::out_of_range e) {
						cout << "Left neighbour of cell with index " << i << " is out of range!";
					}
				}

				//H¾adanie pravého suseda

				int riadokPraveho = 0;
				int stlpecPraveho = 0;

				if (j + 1 >= x && i + 1 >= y) {
					stlpecPraveho = -1;
					riadokPraveho = -1;
				}

				if (j + 1 >= x && i + 1 < y) {
					stlpecPraveho = 0;
					riadokPraveho = i + 1;
				}

				if (j + 1 < x && i + 1 < y) {
					stlpecPraveho = j + 1;
					riadokPraveho = i;
				}

				if (stlpecPraveho != -1) {
					index = riadokPraveho * x + stlpecPraveho;
					try {
						if (std::find(pattern.begin(), pattern.end(), index) != pattern.end()) {
							aliveNeigbours++;
						}
					}
					catch (std::out_of_range e) {
						cout << "Right neighbour of cell with index " << i << " is out of range!";
					}
				}

				//H¾adanie horného suseda

				int riadokHorneho = 0;
				int stlpecHorneho = 0;

				if (i - 1 < 0) {
					stlpecHorneho = -1;
					riadokHorneho = -1;
				}

				if (i - 1 >= 0) {
					stlpecHorneho = j;
					riadokHorneho = i - 1;
				}

				if (stlpecPraveho != -1) {
					index = riadokHorneho * x + stlpecHorneho;
					try {
						if (std::find(pattern.begin(), pattern.end(), index) != pattern.end()) {
							aliveNeigbours++;
						}
					}
					catch (std::out_of_range e) {
						cout << "Upper neighbour of cell with index " << i << " is out of range!";
					}
				}

				//H¾adanie dolného suseda

				int riadokDolneho = 0;
				int stlpecDolneho = 0;

				if (i + 1 >= y) {
					stlpecDolneho = -1;
					riadokDolneho = -1;
				}

				if (i + 1 < y) {
					stlpecDolneho = j;
					riadokDolneho = i + 1;
				}

				index = riadokDolneho * x + stlpecDolneho;

				if (stlpecPraveho != -1) {
					
					try {
						if (std::find(pattern.begin(), pattern.end(), index) != pattern.end()) {
							aliveNeigbours++;
						}
					}
					catch (std::out_of_range e) {
						
					}
				}

				int indexCell = i * x + j;

				if (aliveNeigbours < 2 || aliveNeigbours > 3) {
					newGenerationDeadCells.push_back(indexCell);
				}

				if (aliveNeigbours == 2 || aliveNeigbours == 3) {
					newGenerationAliveCells.push_back(indexCell);
				}

			}
		}
	}

	pattern = newGenerationAliveCells;

}

void Field::manualInsert() {
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
	if (checkCell (riadok, stlpec)) {
		this->pattern.push_back (this->y*(riadok - 1) + (stlpec - 1));
		sort (this->pattern.begin(), this->pattern.end());		
	}	
}

bool Field::checkCell (int riadok, int stlpec) {
	int cell = this->y*(riadok - 1) + (stlpec - 1);
	for (int i = 0; i < this->pattern.size(); i++) {
		if (this->pattern.at (i) == cell) {
			return false;
		}
	}
	return true;
}


void Field::display () {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {

			int index = i * y + j;

			if (std::find(pattern.begin(), pattern.end(), index) != pattern.end())
			{
				cout << 1 << ' ';
			}
			else {
				cout << 0 << ' ';
			}
		}
		cout << endl;
	}	
}

Field::~Field()
{
}
