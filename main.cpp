#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
using namespace std;

//The "Node" Class that is a piece of data

//-----------------------------------------------------------------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------------------------------------------------------------

class Digraph {
public:
	Digraph(); //constructor
	~Digraph(); //destructor
	Digraph(int size, vector <string> TaskData); //constructor
	void EdgeAddition(int index, string newLink); //adds a new Task newlink to the end of the head Task's LL
	void EdgeDeletion(int index, string delLink); //TODO

	void TopologicalSort(); //TopSort Recursive
	void DFSOutTopLabel(vector<bool> &Mark, int v); //Topsort Recursive Helper Function
	void PrintTopLinkedList();
	Task* TopList = new Task();
	Task* TopLinkedListTail = new Task();

	//void DFSOutTopLabel(Task TopList, int v);
	//void DFSOutTopLabel(vector<Task> TopList, int v);
//	void AcyclicCheck(); //TODO
	void PrintAllRelations(int status);
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
Digraph::Digraph(int size, vector <string> TaskData) {

	TaskSize = size;

	for (int i = 0; i < size; i++)
	{
		Task tempTask = Task(TaskData.at(i));
		TaskArray.push_back(tempTask);
	}

	//TODO: Delete tempTask Here
}

//prints all Task Relationa
void Digraph::PrintAllRelations(int status = 0)
{
	int countNullRelations = 0;

	cout << "------------" << endl;
	if (status == 0) {
		cout << "All Relations:" << endl;
	}
	else {
		cout << "Final Relations:\n";
	}

	for (int i = 0; i < TaskSize; i++)
	{
		Task* header = &TaskArray.at(i); // TODO Might want header relationships
		Task* temp = &TaskArray.at(i);
		if (header->next == nullptr) {
			countNullRelations++;
		}
		while (temp->next != nullptr)
		{
			temp = temp->next;
			cout << "(" << header->name << ", " << temp->name << ")" << endl;
		}

	}

	if (countNullRelations == TaskSize) {
		cout << "\nNo relations exist!\n";
	}

	cout << "------------" << endl;

}

//prints all Task Tasks
void Digraph::PrintAllTasks()
{
	cout << "\nTABLE OF TASKS\n";
	cout << "-------------------" << endl;
	cout << "[INDEX] [TASK]" << endl;
	cout << "-------------------" << endl;
	for (int i = 0; i < TaskSize; i++)
	{
		cout << "[" << i + 1 << "] [" << TaskArray.at(i).name << "]" << endl;
	}
	cout << "-------------------" << endl;
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
	else {
		cout << endl << "\nRelation (" << (*header).name << ", " << (*temp).name << ") already exists!\n";
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
		if (temp->next != NULL)
		{
			temp->next->prev = temp->prev;
		}
		temp = nullptr;
		delete(temp);
	}
	else {
		cout << "\nRelation does not exist!\n";
	}
}

void Digraph::TopologicalSort() //Look at Page 233
{
	std::vector<bool> Mark(TaskSize, false);
	for (int v = 0; v < TaskSize; v++)
	{
		if (!Mark.at(v))
		{
			DFSOutTopLabel(Mark, v);
		}
	}
}

void Digraph::DFSOutTopLabel(vector<bool> &Mark, int v) // Look at Page 233's recursive function
{
	Mark.at(v) = true;
	for (int w = 0; w < TaskSize; w++)
	{
		// w is the vertex we are iterating through
		// Edge from V to W
		// if W is Marl.at(w) == false, recursivley call
		Task* temp = TaskArray.at(v).next;
		while (temp != nullptr)
		{
			if (temp->name == TaskArray.at(w).name) //for each w in v st (v,w) spans E
			{
		 		if (Mark.at(w) == false)
				{
					DFSOutTopLabel(Mark, w);
				}
			}
			temp = temp->next;
		}
	}

	//This is Where I'm messing up below (pretty sure above is all right)

	if (TopList->name == "")
	{
		TopList->name = TaskArray.at(v).name;
	}
	else
	{
		Task* toAdd = new Task(TaskArray.at(v).name);
		Task* temp = TopList;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		temp->next = toAdd;
	}

	

}

void Digraph::PrintTopLinkedList()
{
	/*Task* temp = TopList;
	while (temp->prev != nullptr)
	{
		temp = temp->prev;
	}
	
	while (temp->next != nullptr)
	{
		cout << temp->name << ", ";
		temp = temp->next;
	}
	cout << temp->name;*/
	cout << "TopSorted Order:" << endl;

	Task* temp = TopList;
	while (temp->next != nullptr)
	{
		cout << temp->name << ", ";
		temp = temp->next;
	}
	cout << temp->name;


}

//-----------------------------------------------------------------------------------------------------------------------------------

class UserInterface {
public:
	UserInterface();
	void Menu();
	void TaskInput();
	void RelationInput();
	void RelationDelete();
	int ErrorHandling(int section, int index1 = 0);
	void TopSort();

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
	//Initialize Digraph
	d = Digraph(dataIndex, userArray);

}

void UserInterface::RelationInput()
{
	string tempFrom;
	string tempTo;
	string tempExit;
	int index1;
	int index2;
	bool inputValid = false;

	//user input
	d.PrintAllTasks(); //print tasks for user
	cout << "\nSTART RELATION INPUT (FOR ADD)\n";
	cout << "--------------------------------";
	index1 = ErrorHandling(1); //CALL ERROR HANDLING FOR INDEX1
	index2 = ErrorHandling(2, index1); //CALL ERROR HANDLING FOR INDEX2, THIS TIME WITH INDEX1 SO IT CAN ENSURE INDEX2 != INDEX1
	tempFrom = d.TaskArray.at(index1 - 1).name; //FIND IN TASKARRAY WHAT RELATION IT IS GOING FROM  (MUST SUBTRACT 1 FOR 0 INDEXING)
	tempTo = d.TaskArray.at(index2 - 1).name; //FIND IN TASKARRAY WHAT RELATION IT IS GOING TO (MUST SUBTRACT 1 FOR 0 INDEXING)
	cout << "\nNew relation: (" << tempFrom << ", " << tempTo << ")" << endl; //PRINT OUT TO ENSURE IT IS GOING FROM X TO Y CORRECTLY
	d.EdgeAddition(index1 - 1, tempTo); // SET EDGE ADDITION
	d.PrintAllRelations();
}


void UserInterface::RelationDelete()
{
	bool exit = false;
	string tempFrom;
	string tempTo;
	string tempExit;
	int index1;
	int index2;
	d.PrintAllTasks(); // print tasks for user
	cout << "\nSTART RELATION INPUT (FOR DELETE)\n";
	cout << "--------------------------------";

	//user input
	index1 = ErrorHandling(1); //CALL ERROR HANDLING FOR INDEX1
	index2 = ErrorHandling(2, index1); //CALL ERROR HANDLING FOR INDEX2, THIS TIME WITH INDEX1 SO IT CAN ENSURE INDEX2 != INDEX1
	tempFrom = d.TaskArray.at(index1 - 1).name; //FIND IN TASKARRAY WHAT RELATION IT IS GOING FROM  (MUST SUBTRACT 1 FOR 0 INDEXING)
	tempTo = d.TaskArray.at(index2 - 1).name; //FIND IN TASKARRAY WHAT RELATION IT IS GOING TO (MUST SUBTRACT 1 FOR 0 INDEXING)
	cout << "\nDeleted relation: (" << tempFrom << ", " << tempTo << ")" << endl; //PRINT OUT TO ENSURE IT IS GOING FROM X TO Y CORRECTLY

	d.EdgeDeletion(index1 - 1, tempTo); // SET EDGE DELETION
	d.PrintAllRelations();
}

void UserInterface::TopSort()
{
	cout << "----------------" << endl << "Before TopSort:";
	d.PrintAllTasks();
	cout << "TopSorting........." << endl;
	d.TopologicalSort();
	d.PrintTopLinkedList();
}


void UserInterface::Menu()
{
	bool run = true;
	char choice;
	TaskInput();

	while (run) { //while user wants to edit data...
		// menu statement
		cout << "\nWhat would you like to do? \n 1. Add a new relation. \n 2. Delete a relation. \n 3. Topological Sort \n 4. Acyclic Check \n 5. Print Tasks and Relations \n 0. Exit.\n"; //TODO ; ADD OTHER RELATIONS
		cout << "Enter the number corresponding with your selection: ";
		cin >> choice; //user enters choice number
		switch (choice) {
		case '1':
			RelationInput(); //if user enters 1, add relation
			break;
		case '2':
			RelationDelete(); //if user enters 2, delete relation 
			break;
		case '3':
			TopSort();
			break;
		case '4':
			//TODO: ADD ACYCLIC CHECK FUNCTION
			break;
		case '5':
			d.PrintAllTasks();
			d.PrintAllRelations();
			break;
		case '0':
			//if user enters 0, print final relations and exit loop
			cout << endl;
			d.PrintAllRelations(1);
			run = false; //break loop
			break;
		default:
			cout << "Please enter a valid choice. \n"; //if choice was not valid, print an error statement 
			break;
		}
	}

	//TODO: Destructor, Edge Deletion, Topological Sort, Acylic Check (pretty sure acylic check is ez but not 100%)
}


//-----------------------------------------------------------------------------------------------------------------------------------

//START MAIN

int main() {
	UserInterface UI;
	UI.Menu();
	cout << "\nThank you! Press any key to exit...\n";
	cin.get();
	cin.ignore();
	return 0;
}
