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

void Function::Main_Menu() {
	int choice;
	cout << "SELECT A TOOL" << endl;
	cout << "1. Display Time" << endl;
	cout << "2. Geometry" << endl;
	cout << "3. Trigonometry" << endl;
	cout << "4. Calculus" << endl;
	cout << "5. WRITE VERY SECRETIVE NOTES" << endl;
	cout << "6. VIEW VERY SECRETIVE NOTES" << endl;
	cout << "7. DELETE VERY SECRETIVE NOTES" << endl;
	cout << "8. Exit" << endl;
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
			cout << "Geometry" << endl;
			break;
		case 3:
			cout << "Trigonometry" << endl;
			break;
		case 4:
			cout << "Calculus" << endl;
			break;
		case 5:
			cout << "WRITE VERY SECRETIVE NOTES" << endl;
			writeNotes();
			break;
		case 6:
			cout << "VIEW VERY SECRETIVE NOTES" << endl;
			viewNotes();
			break;
		case 7:
			cout << "DELETE VERY SECRETIVE NOTES" << endl;
			deleteNotes();
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
	file << notes << " - " << __DATE__ << " " << __TIME__ << endl;
	file.close();

	cout << "Notes saved!" << endl;
	
	PressEnter();
	Main_Menu();
}

void Function::viewNotes() {
	clearScreen();

	string line;
	ifstream file("notes.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close();
	}
	else {
		cout << "Unable to open file" << endl;
	}

	PressEnter();
	Main_Menu();
}

void Function::deleteNotes() {
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
	Main_Menu();
}