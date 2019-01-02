#include "heap_monitor.h"
#include "Main.h"
#include "Field.h"

Main::Main()
{
}

int main() {
	
	initHeapMonitor();

	Field field = Field::Field (5, 4);

	cout << "Nahodny vector:" << endl;
	field.generateRandomPattern ();
	cout << endl;

	cout << "Vysledne pole:" << endl;
	field.display();
	cout << endl;
		
	field.nextGeneration();
	cout << "Nova generacia:" << endl;
	field.display();
	cout << endl;
	
	return 0;
	
}


Main::~Main()
{
}
