#include "Main.h"
#include "Field.h"

Main::Main()
{
}

int main() {
	
	Field field = Field::Field (4, 3);

	cout << "Nahodny vector:" << endl;
	field.generateRandomPattern ();
	cout << endl;

	cout << "Vysledne pole:" << endl;
	field.display();
	cout << endl;
	
	return 0;
}


Main::~Main()
{
}
