#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
using namespace std;


class Digraph{
public: 
	Digraph();
	void Constructor();
	void Destructor();
	void EdgeAddition();
	void EdgeDeletion();
	//ETC. FUNCTIONS
	void TopologicalSorting(); //MUST USE DFT FOUND IN BOOK
	void AcycliCheck();

};

Digraph::Digraph() {}

void Digraph::Constructor() {
	//ADD CONSTRUCTOR CODE 
}

void Digraph::Destructor() {
	//ADD DESTRUCTOR CODE
}

class UserInterface {
public:
	UserInterface();
	void Menu();
	void UserData();

private:

};

UserInterface::UserInterface() {}

void UserInterface::UserData() {
	vector <string> userArray;
	string choice;
	int dataIndex;

	cout << "How many tasks are to be completed?\n";
	cin >> dataIndex; // USER ENTERS HOW MANY TASKS MUST BE COMPLETE 

	//USER ENTERS THE AMOUNT OF TASKS THEY SPECIFIED. THIS IS PLACED IN AN ARRAY.
	for (int i = 0; i < dataIndex; i++) {
		cout << "Enter task name: ";
		if (i == 0) cin.ignore();
		getline(cin, choice, '\n');
		userArray.push_back(choice);
	}

	//PRINT DATA IN THE RECEiVED ORDER BACK TO THE USER 
	cout << "\nTasks to be completed include:\n";
	for (int i = 0; i < dataIndex; i++) {
		cout << i+1 << ": " << userArray[i] << endl;
	}

}

void UserInterface::Menu() {
	bool run = true;
	UserData();
}

// END UI

//START MAIN

int main() {
	UserInterface UI;
	UI.Menu();
	cout << "Done! Press any key to exit...\n";
	cin.get();
	cin.ignore();
	return 0;
}