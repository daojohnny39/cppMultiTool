#pragma warning(disable : 4996)

#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <string>
#include "Functions.h"

using namespace std;

void Function::Run() {
	Main_Menu();
}

void Function::HeaderString(string title) {
	cout << "==============================" << endl;
	cout << " " << title << endl;
	cout << "==============================" << endl;
}

void Function::Main_Menu() {
	clearScreen();
	HeaderString("MAIN MENU");

	int choice;
	cout << "SELECT A TOOL" << endl;
	cout << "1. Display Time" << endl;
	cout << "2. Notes Menu" << endl;
	cout << "3. Quynh's Feeding Time Calculator" << endl;
	cout << "4. Exit" << endl;
	cout << endl << "Enter your choice: " << endl;
	cout << ">> ";
	cin >> choice;

	while (cin.fail() || choice < 1 || choice > 8) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again: " << endl;
		cout << ">> ";
		cin >> choice;
	}

	switch (choice) {
		case 1:
			cout << "Display Time" << endl;
			displayTime();
			break;
		case 2:
			cout << "Notes Menu" << endl;
			Notes_Menu();
			break;
		case 3:
			cout << "Quynh's Feeding Time Calculator" << endl;
			feedTime();
			break;
		case 4:
			cout << "Exit" << endl;
			exit(0);
			break;
	}
}

void Function::Notes_Menu() {
	clearScreen();
	HeaderString("NOTES MENU");

	int choice;
	cout << "1. WRITE VERY SECRETIVE NOTES" << endl;
	cout << "2. VIEW VERY SECRETIVE NOTES" << endl;
	cout << "3. DELETE VERY SECRETIVE NOTES" << endl;
	cout << "4. Back" << endl;
	cout << endl << "Enter your choice: " << endl;
	cout << ">> ";
	cin >> choice;

	while (cin.fail() || choice < 1 || choice > 5) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input. Please try again: " << endl;
		cout << ">> ";
		cin >> choice;
	}

	switch (choice) {
	case 1:
		cout << "WRITE VERY SECRETIVE NOTES" << endl;
		writeNotes();
		break;
	case 2:
		cout << "VIEW VERY SECRETIVE NOTES" << endl;
		viewNotes();
		break;
	case 3:
		cout << "DELETE VERY SECRETIVE NOTES" << endl;
		deleteNotes();
		break;
	case 4:
		cout << "Exit" << endl;
		Main_Menu();
		break;
	}
}

void Function::PressEnter() {
	cout << endl;
	cout << "Press ENTER to continue..." << endl;
	cin.ignore();
	cin.get();

	system("cls");
}

void Function::clearScreen() {
	system("cls");
}

void Function::displayTime() {
	clearScreen();

	time_t now = time(0); 
	char* dt = ctime(&now);
	cout << "The local date and time is: " << dt << endl;

	PressEnter();
	Main_Menu();
}

void Function::writeNotes() {
	clearScreen();

	string notes;
	cout << "Enter your notes: " << endl;
	cout << ">> ";
	cin.ignore();
	getline(cin, notes); 
	ofstream file;
	file.open("notes.txt", ios::app);
	file << " - " << __DATE__ << " " << __TIME__ << " --- " << notes << endl;
	file.close();

	cout << "Notes saved!" << endl;
	
	PressEnter();
	Notes_Menu();
}

void Function::viewNotes() {
	clearScreen();

	int count = 1;
	string line;
	ifstream file("notes.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << count << ". " << line << endl;
			count++;
		}
		file.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}

	PressEnter();
	Notes_Menu();
}

void Function::deleteNotes() {
	clearScreen();

	string line;
	int lineNumber = 1;

	ifstream file("notes.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << lineNumber << ". " << line << endl;
			lineNumber++;
		}
		file.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}

	cout << "Enter the line number you want to delete: " << endl;
	cout << ">> ";

	int lineNum;
	cin >> lineNum;

	ifstream file2("notes.txt");
	ofstream file3("temp.txt");
	int count = 0;
	if (file2.is_open()) {
		while (getline(file2, line)) {
			count++;
			if (count != lineNum) {
				file3 << line << endl;
			}
		}
		file2.close();
		file3.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}

	remove("notes.txt");
	rename("temp.txt", "notes.txt");

	cout << "Line " << lineNum << " deleted!" << endl;
	
	PressEnter();
	Notes_Menu();
}

void Function::feedTime() {
	clearScreen();
	HeaderString("QUYNH FEED TIME CALCULATOR");

	int const hourTime = 60;
	int hourMl = 550;
	
	// Equation variables
	// Equation: (550)x = (60)currMl		ex: currMl = 100	
	//			 550x = 6000
	//			 x = 6000/550
	//			 x = ~11
	//			 return 60 - 11 (= 49)
	//			 49 minutes left until finished

	int currMl;
	int diffInput;
	int minsPast;
	int minsLeft;
	int rightSideEQ;

	cout << "Would you like to do a custom target amount?: " << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	cout << "3. Back" << endl << endl;
	cout << ">> ";
	cin >> diffInput;

	if (diffInput == 1) {
		clearScreen();

		cout << "Enter target amount: " << endl;
		cout << ">> ";
		cin >> diffInput;

		hourMl = diffInput;
	}
	else if (diffInput == 2) {
		clearScreen();
		cout << "Default target amount is: 550ml" << endl;
	}
	else if (diffInput == 3) {
		clearScreen();
		Main_Menu();
	}
	else {
		cout << "Invalid input. Default target amount is 550ml" << endl;
	}

	cout << "Enter current ML: " << endl;
	cout << ">> ";
	cin >> currMl;

	rightSideEQ = hourTime * currMl;
	minsPast = rightSideEQ / hourMl;
	minsLeft = hourTime - minsPast;

	clearScreen();

	cout << "Time left until finished: " << minsLeft << " minutes" << endl << endl;
	cout << "Current ML: " << currMl << endl;

	PressEnter();
	Main_Menu();
}