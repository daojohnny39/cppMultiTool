#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Function {
public:
	// UTILITY
	void Run();
	void Main_Menu();
	void HeaderString(std::string title);
	void Notes_Menu();
	void PressEnter();
	void clearScreen();

	// TIME DISPLAY
	void displayTime();

	// NOTES
	void writeNotes();
	void viewNotes();
	void deleteNotes();

	// QUYNH'S FEEDING TIME CALCULATOR
	void feedTime();
};

#endif // !FUNCTIONS_H
