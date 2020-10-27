// hw4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
using namespace std;

//The "Node" Class that is a piece of data
class Task
{
public:
	Task(); //constructor
	Task(string nameInput);
	string name = "";
	Task* next = nullptr;
	Task* prev = nullptr;
	int label = 0; // Only important in TopSort
};

Task::Task()
{
	next = nullptr;
	prev = nullptr;
}

Task::Task(string nameInput)
{
	name = nameInput;
	Task* next = nullptr;
	Task* prev = nullptr;
}



class Digraph {
public:
	Digraph(); //constructor
	~Digraph(); //destructor
	Digraph(int size, vector <string> TaskData); //constructor
	void EdgeAddition(int index, string newLink); //adds a new Task newlink to the end of the head Task's LL
	void EdgeDeletion(int index, string delLink); //TODO

	//void TopologicalSort(); //MUST USE DFT FOUND IN BOOK //TODO
	//void DFSOutTopLabel(Task TopList, int v);
	//void DFSOutTopLabel(vector<Task> TopList, int v);
//	void AcyclicCheck(); //TODO

	void PrintAllTasks();//prints all Tasks

	vector<Task> TaskArray; //array of unique Header Tasks (for the LL)
	int TaskSize; // the size of taskArray 

};

//Defines TaskSize as 0
Digraph::Digraph()
{
	TaskSize = 0;
}

Digraph::~Digraph() {}

// Creates Array of Task From User Input For Class Digraph
Digraph::Digraph(int size, vector <string> TaskData)
{

	TaskSize = size;

	for (int i = 0; i < size; i++)
	{	
		Task tempTask = Task(TaskData.at(i));
		TaskArray.push_back(tempTask);
	}

	//TODO: Delete tempTask Here

}

//prints all Task Tasks
void Digraph::PrintAllTasks()
{
	for (int i = 0; i < TaskSize - 1; i++)
	{
		cout << TaskArray.at(i).name + ", ";
	}
	cout << TaskArray.at(TaskSize - 1).name;

}

//basic Linked List Iteration of a new Task into the Task in the array 
void Digraph::EdgeAddition(int index, string newLink)
{
	Task* header = &TaskArray.at(index); // TODO Might want header relationships
	Task* temp = &TaskArray.at(index);
	while (newLink != temp->name && temp->next != nullptr)
	{
		temp = temp->next;
	}
	if (newLink != temp->name) {
		temp->next = new Task(newLink);
		temp->next->prev = temp; // TODO Reevaluate if this is needed later
	}
}

void Digraph::EdgeDeletion(int index, string delLink)
{
	Task* temp = &TaskArray.at(index);
	while (delLink != temp->name && temp->next != nullptr)
	{
		temp = temp->next;
	}
	if (delLink == temp->name) {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		temp = nullptr;
		delete(temp);
	}
}




class UserInterface {
public:
	UserInterface();
	void Menu();
	void TaskInput();
	void RelationInput();
	int ErrorHandling(int section, int index1 = 0);

	Digraph d;

private:

};

UserInterface::UserInterface() {}

//FUNCTION USED TO ENSURE USER INPUT FOR INDEX IS VALID
int UserInterface::ErrorHandling(int section, int index1) {
	bool inputValid = false;
	string tempFrom;
	int index;

	while (!(inputValid)) { //LOOP UNTIL INPUT IS VALID
		if (section == 1) // IF THIS IS INDEX 1, PRINT RELATION MESSAGE ACCORDING TO INDEX 1
			cout << endl << "Relation Goes From Index: ";
		else //ELSE, PRINT ACCORDING TO INDEX 2
			cout << endl << "Relation Goes To Index: ";
		cin >> tempFrom; //ENTER INDEX OF TASK
		//TRY TO CONVERT STRING TO INTEGER. IF NOT POSSIBLE, PRINT ERROR MESSAGE.
		try {
			index = stoi(tempFrom); //CONVERT STRING TO INT 
			if (index >= 1 && index <= d.TaskArray.size() && index != index1) { //IF IT IS WITHIN RANGE AND NOT EQUAL TO THE FIRST INDEX...
				inputValid = true; //EXIT LOOP 
			}
			else { //ELSE PRINT MESSAGE STATING INVALID INPUT
				cout << "Input out of range. Try again. ";
			}
		}
		catch (std::invalid_argument& index) {
			cout << "Could not convert input to integer. Try again.\n";
		}
	}

	return index; //RETURN INDEX
}

void UserInterface::TaskInput() {
	vector <string> userArray;
	string choice;
	int dataIndex;
	bool validChoice = true;

	//ENSURE THAT THE CHOICE ENTERED IS VALID. IF IT IS NOT, DO NOT MOVE ON UNTIL USER INPUT IS VALID
	while (validChoice) {
		cout << "How many tasks are to be completed?\n";
		cin >> dataIndex; // USER ENTERS HOW MANY TASKS MUST BE COMPLETE 

		if (dataIndex <= 1) {
			cout << "ERROR : TASK NUMBER MUST BE GREATER THAN 1!\n"; //THERE MUST BE MORE THAN 1 TASK!
		}
		else {
			validChoice = false;
		}
	}

	//USER ENTERS THE AMOUNT OF TASKS THEY SPECIFIED. THIS IS PLACED IN AN ARRAY.
	for (int i = 0; i < dataIndex; i++)
	{
		cout << "Enter task name: ";
		if (i == 0) cin.ignore();
		getline(cin, choice, '\n');
		userArray.push_back(choice);
	}

	//PRINT DATA IN THE RECEiVED ORDER BACK TO THE USER 
	cout << "\nTasks to be completed include:\n";
	for (int i = 0; i < dataIndex; i++)
	{
		cout << i + 1 << ": " << userArray[i] << endl;
	}

	//Initialize Digraph
	d = Digraph(dataIndex, userArray);

}

void UserInterface::RelationInput()
{
	bool exit = false;
	string tempFrom;
	string tempTo;
	string tempExit;
	int index1;
	int index2;
	bool inputValid = false;

	while (!exit)
	{
		//user input
		cout << endl << "List of Tasks: " << endl;
		d.PrintAllTasks();
		index1 = ErrorHandling(1); //CALL ERROR HANDLING FOR INDEX1
		index2 = ErrorHandling(2, index1); //CALL ERROR HANDLING FOR INDEX2, THIS TIME WITH INDEX1 SO IT CAN ENSURE INDEX2 != INDEX1

		//add edge from strings (may have to do some string checking here in the future if we care)
		//d.EdgeAddition(tempFrom, tempTo);
		tempFrom = d.TaskArray.at(index1 - 1).name; //FIND IN TASKARRAY WHAT RELATION IT IS GOING FROM  (MUST SUBTRACT 1 FOR 0 INDEXING)
		tempTo = d.TaskArray.at(index2 - 1).name; //FIND IN TASKARRAY WHAT RELATION IT IS GOING TO (MUST SUBTRACT 1 FOR 0 INDEXING)
		cout << "Going from " << tempFrom << " to " << tempTo << endl; //PRINT OUT TO ENSURE IT IS GOING FROM X TO Y CORRECTLY
		d.EdgeAddition(index1 - 1, tempTo); // SET EDGE ADDITION

		cout << endl << "Enter another Relation? [y/n]:	";
		cin >> tempExit;

		//check end condition
		if (tempExit == "y" || tempExit == "yes" || tempExit == "Yes")
		{
			exit = false;
		}
		else
		{
			exit = true;
		}
		cout << endl;
	}
}

void UserInterface::Menu()
{
	bool run = true;
	TaskInput();
	RelationInput();
	//TODO: Destructor, Edge Deletion, Topological Sort, Acylic Check (pretty sure acylic check is ez but not 100%)
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







// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

/*//this chunk here prints how do do input in a user friendly way but requires at least 3 inputs from before, a fallback is given in the else that isnt as good
	if (d.TaskSize > 2)
	{
		string s1 = d.TaskArray.at(0).name;
		string s2 = d.TaskArray.at(1).name;
		string s3 = d.TaskArray.at(2).name;
		cout << "\nPlease specify an order relation on pairs of tasks.\n\nEXAMPLES:\n\n" + s3 + " " + s1 + "			(indicates that Task:" + s3 + " must precede Task:" + s1 + ") \n" + s2 + " " + s3 + "		(indicates that Task:" + s2 + " must precede Task:" + s3 + ") \n" + s1 + " " + s2 + "		(indicates that Task:" + s3 + " must precede Task:" + s1 + ") \n";
	}
	else
	{
		cout << "\nspecify an order relation on pairs of tasks, e.g.,\n 3 1 (indicates that Task 3 must precede Task 1) \n 7 5 (indicates that Task 7 must precede Task 5) \n 5 1 (indicates that Task 5 must precede Task 1) \n";
	}
	//end chunk */

	//------------------------
