#include "Main.h"
#include "Field.h"

Main::Main()
{
}

int main() {
	cout << "Hello there!" << endl;
	Field field = Field::Field (4, 4);
	field.generateRandomPattern ();
	return 0;
}


Main::~Main()
{
}
