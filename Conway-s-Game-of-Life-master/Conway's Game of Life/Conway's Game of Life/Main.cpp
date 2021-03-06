#include <string>
#include <stdlib.h>
#include "heap_monitor.h"
#include "Field.h"
#include "Main.h"

Main::Main()
{
}

int main() {
	
	initHeapMonitor();

	Field field = Field::Field (10, 10);         //ak sa nic nezada, deafultne sa vytvori prazdne pole s rozmermi 10x10
		
	int input = 0;
	string message;
	while (true) {
		cout << "***************************************** " << endl;
		cout << "         Conway's Game of Life" << endl;
		cout << "***************************************** " << endl;
		cout << "Please, select one of the options bellow: " << endl;
		cout << "1.New World" << endl;                             //novy prazdny svet so zadanymi rozmermi
		cout << "2.Randomly Defined Pattern" << endl;			   //nahodny vzor
		cout << "3.Manually Defined Pattern" << endl;              //rucne definovane zive bunky
		cout << "4.Load Pattern" << endl;                          //nacitanie vzoru z lokalneho suboru
		cout << "5.Save Pattern" << endl;                          //ulozenie vzoru z lokalneho suboru
		cout << "6.Receive Pattern" << endl;                       //nacitanie vzoru zo serveru
		cout << "7.Send Pattern" << endl;                          //ulozenie vzoru na server
		cout << "8.Simulation" << endl;                            //predna + spatna simulacia + moznost kedykolvek prerusit simulaciu
		cout << "0.Exit" << endl;
		cout << "***************************************** " << endl;
		if (message.empty ()) {
			cout << "***************************************** " << endl;
		}
		else {
			cout << message << endl;
		}		
		cout << "***************************************** " << endl;
		cout << "Your input: ";		
		cin >> input;
		
		switch (input) {
		case 1: {
			system("CLS");
			int rows = 0;
			int columns = 0;			
			cout << "***************************************** " << endl;
			cout << "         Conway's Game of Life" << endl;
			cout << "***************************************** " << endl;
			cout << "Please enter the row count: ";
			cin >> rows;
			cout << "Please enter the column count: ";
			cin >> columns;			
			field.setX (rows);
			field.setY (columns);
			field.clearPattern ();
			message = "New world created. Check Simulation.";
			system("CLS");
			break;
		}			
		case 2:
			field.generateRandomPattern();
			message = "New pattern created. Check Simulation.";
			system("CLS");
			break;
		case 3:
			system("CLS");
			cout << "***************************************** " << endl;
			cout << "         Conway's Game of Life" << endl;
			cout << "***************************************** " << endl;
			cout << "Please, enter the amout of live cells: ";
			cin >> input;
			for (int i = 0; i < input; i++) {
				system("CLS");
				cout << "***************************************** " << endl;
				cout << "         Conway's Game of Life" << endl;
				cout << "***************************************** " << endl;
				cout << i+1 << ". cell" << endl;
				field.manualInsert();
			}			
			message = "New pattern created. Check Simulation.";
			system("CLS");
			break;
		case 4:
			message = "TODO";
			system("CLS");
			break;
		case 5:
			message = "TODO";
			system("CLS");
			break;
		case 6:
			message = "TODO";
			system("CLS");
			break;
		case 7:
			message = "TODO";
			system("CLS");
			break;
		case 8:
			system("CLS");
			cout << "***************************************** " << endl;
			cout << "         Conway's Game of Life" << endl;
			cout << "***************************************** " << endl;
			cout << "Please, select one of the options bellow: " << endl;
			cout << "1.Forward Simulation" << endl;                             
			cout << "2.Backward Simulation" << endl;			  
			cout << "3.Stop Simulation" << endl;              
			cout << "0.Main Menu" << endl;       
			cout << "***************************************** " << endl;
			field.display();
			cout << "***************************************** " << endl;
			cout << "Your input: ";
			cin >> input;
			message.clear();
			system("CLS");
			break;
		case 0:
			exit(EXIT_SUCCESS);
			break;
		default:	
			message = "Invalid input.";
			system ("CLS");
			break;
		}			
	}
	return 0;	
}

Main::~Main()
{
}
