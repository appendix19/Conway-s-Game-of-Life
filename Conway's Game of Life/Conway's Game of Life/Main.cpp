#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "heap_monitor.h"
#include "Main.h"

#include <sys/types.h>
#include <stdio.h>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


Main::Main()
{
}

void saveToFile(Field* field, string& message);
//void sendPattern(string host, int port, vector<int>* pattern);

int main() {
	
	initHeapMonitor();

	Field* field = new Field (10, 10);         //ak sa nic nezada, deafultne sa vytvori prazdne pole s rozmermi 10x10

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
		if (message.empty()) {
			cout << "***************************************** " << endl;
		}
		else {
			cout << message << endl;
		}
		cout << "***************************************** " << endl;
		cout << "Your input: ";

		cin >> input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			system("CLS");
			message = "Input must be numeric.";			
			continue;
		}

		switch (input) {
		case 1: {
			system(CLEAR);
			int rows = 0;
			int columns = 0;
			cout << "***************************************** " << endl;
			cout << "         Conway's Game of Life" << endl;
			cout << "***************************************** " << endl;
			cout << "Please enter the row count: ";
			cin >> rows;
			cout << "Please enter the column count: ";
			cin >> columns;
			field->setX(rows);
			field->setY(columns);
			field->clear();
			message = "New world created. Check Simulation.";
			system(CLEAR);
			break;
		}
		case 2:
			field->generateRandomPattern();
			message = "New pattern created. Check Simulation.";
			system(CLEAR);
			break;
		case 3:
			system(CLEAR);
			cout << "***************************************** " << endl;
			cout << "         Conway's Game of Life" << endl;
			cout << "***************************************** " << endl;
			cout << "Please, enter the amout of live cells: ";
			cin >> input;
			for (int i = 0; i < input; i++) {
				system(CLEAR);
				cout << "***************************************** " << endl;
				cout << "         Conway's Game of Life" << endl;
				cout << "***************************************** " << endl;
				cout << i + 1 << ". cell" << endl;
				field->manualInsert();
			}
			message = "New pattern created. Check Simulation.";
			system(CLEAR);
			break;
		case 4:
		{
			string filename;
			cout << "Please enter the filename: ";
			cin >> filename;
			system(CLEAR);

			field->clear();
			ifstream in(filename);
			streambuf *cinbuf = cin.rdbuf();
			cin.rdbuf(in.rdbuf());

			string line = "";
			int index;
			while (getline(cin, line) && line.compare("END") != 0) {
				istringstream sin(line);
				sin >> index;
				field->addCell(index);
			}

			cin.rdbuf(cinbuf);

			message = "Pattern was successfully loaded.";
			break;
		}
		case 5:
		{
			saveToFile(field, message);
			break;
		}

		case 6:
			message = "TODO";
			system(CLEAR);
			break;
		case 7:
			//sendPattern("localhost", 6000, field->getPattern());
			system(CLEAR);
			break;
		case 8:
			system(CLEAR);
			cout << "***************************************** " << endl;
			cout << "         Conway's Game of Life" << endl;
			cout << "***************************************** " << endl;
			cout << "Please, select one of the options bellow: " << endl;
			cout << "1.Forward Simulation" << endl;
			cout << "2.Backward Simulation" << endl;			
			cout << "0.Main Menu" << endl;
			cout << "To stop simulation, press any key." << endl;
			cout << "***************************************** " << endl;
			field->display();
			cout << "***************************************** " << endl;
			cout << "Your input: ";

			cin >> input;
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				system("CLS");
				message = "Input must be numeric.";
				continue;
			}
			message.clear();
			system(CLEAR);
			switch (input) {
			case 1:
				field->forwardSimulation();
				system(CLEAR);
				break;
			case 2:
				field->backwardSimulation();
				system(CLEAR);
				break;
			case 0:
				system(CLEAR);
				break;
			default:
				message = "Invalid input.";
				system(CLEAR);
				break;
			}
			break;
			
		case 0:			
			return 0;
			break;
		default:
			message = "Invalid input.";
			system(CLEAR);
			break;
		}
	}

	delete field;
	return 0;
}


Main::~Main()
{
}

void saveToFile(Field* field, string& message)
{
	string filename;
	cout << "Please enter the filename : ";
	cin >> filename;
	system(CLEAR);

	ofstream out(filename);
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(out.rdbuf());

	field->patternToFile();
	cout << "END" << endl;

	cout.rdbuf(coutbuf);
	message = "Pattern was successfully written to file.";
}

/*
void sendPattern(string host, int port, vector<int>* pattern) {
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent* server;
	char buffer[256];
	int x = 0;

	//funkcia kniûnice sys/socket.h na zÌskanie "hostname"
	//ako prv˝ parameter zad·vame "localhost"

	server = gethostbyname(argv[1]);

	bzero((char*)&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	bcopy(
		(char*)server->h_addr,
		(char*)&serv_addr.sin_addr.s_addr,
		server->h_length
	);

	//ako druh˝ parameter zad·vame ËÌslo portu

	serv_addr.sin_port = htons(port);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//prip·jame sa na sieùov˙ adresu

	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("CHYBA!!!");
	}

	//v nekoneËnom cykle zasiela spr·vy serveru

	for (int i : *pattern) {
		printf("Zadaj spr·vu: ");
		bzero(buffer, 256);
		//fgets(buffer, 255, stdin);
		sprintf(buffer, "%ld", i);

		n = write(sockfd, buffer, strlen(buffer)); //poöle serveru spr·vu uloûen˙ v bufferi

		bzero(buffer, 256); //ËistÌ buffer
		n = read(sockfd, buffer, 255); //ËÌta spr·vu od servera

		printf("%s\n", buffer);
	}

	close(sockfd);
}

*/
