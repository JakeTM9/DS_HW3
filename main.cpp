// hw4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
using namespace std;

//Header Node (I like calling them Node because it helps me think and code 
//-> Can switch to Header classname Later
class Node
{
public:
	Node(); //constructor
	Node(string nameInput);
	string name = "";
	Node* next;
};

Node::Node() { Node* next = NULL; };

Node::Node(string nameInput)
{
	name = nameInput;
	Node* next = NULL;
}



class Digraph {
public:
	Digraph(); //constructor
	Digraph(int size, vector <string> headerData); //constructor
	void Destructor();
	void EdgeAddition(string head,string newLink); //adds a new Node newlink to the head node in the headerNodeArray
//	void EdgeDeletion();
	
//	void TopologicalSorting(); //MUST USE DFT FOUND IN BOOK
//	void AcycliCheck();

	void PrintAllHeaders();//prints all headers

	Node GetHeaderByName(string name); //returns header Node given a string
	vector<Node> headerNodeArray;
	int headerSize;

};

//Creates Empty Header Node Array
Digraph::Digraph() 
{ 
	headerSize = 0;
}

// Creates Array of Header Nodes From User Input For Class Digraph
Digraph::Digraph( int size, vector <string> headerData) 
{

	headerSize = size;

	for (int i = 0; i < size; i++) 
	{
		Node tempNode = Node(headerData.at(i));
		headerNodeArray.push_back(tempNode);

	}

	//TODO: Delete tempNode Here
	
}

//prints all header nodes
void Digraph::PrintAllHeaders()
{
	for (int i = 0; i < headerSize; i++)
	{
		cout << headerNodeArray.at(i).name + ", ";
	}
}

//basic Linked List Iteration-> once head/temp hits a NULL it adds newLink to the end of the Linked List
void Digraph::EdgeAddition(string head, string newLink)
{
	for (int i = 0; i < headerSize; i++)
	{
		if (head == headerNodeArray.at(i).name)
		{
			headerNodeArray.at(i).next = new Node(newLink);
		}
	}
	//GetHeaderByName(head).next = new Node(newLink);
/*
	if (head->next == NULL)
	{
		head->next = newLink;
	}
	else
	{
		Node* temp = head->next;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newLink;
	}
	*/
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
		cout << i + 1 << ": " << userArray[i] << endl;
	}

	//Passes Data to Digraph Class
	Digraph d = Digraph(dataIndex, userArray);

	//Order Relation USER INPUT -------------------------------------------------------------------

	//this chunk here prints how do do input in a user friendly way but requires at least 3 inputs from before, a fallback is given in the else that isnt as good
	if (d.headerSize > 2)
	{
		string s1 = d.headerNodeArray.at(0).name;
		string s2 = d.headerNodeArray.at(1).name;
		string s3 = d.headerNodeArray.at(2).name;

		cout << "\nPlease specify an order relation on pairs of tasks.\n\nEXAMPLES:\n\n" + s3 + " " + s1 + "			(indicates that Task:" + s3 + " must precede Task:" + s1 + ") \n" + s2 + " " + s3 + "		(indicates that Task:" + s2 + " must precede Task:" + s3 + ") \n" + s1 + " " + s2 + "		(indicates that Task:" + s3 + " must precede Task:" + s1 + ") \n";
	}
	else
	{
		cout << "\nspecify an order relation on pairs of tasks, e.g.,\n 3 1 (indicates that Task 3 must precede Task 1) \n 7 5 (indicates that Task 7 must precede Task 5) \n 5 1 (indicates that Task 5 must precede Task 1) \n";
	}
	//end chunk

	//this chunk here handles the user input
	bool exit = false;
	string tempFrom;
	string tempTo;
	string tempExit;
	vector <string> relationFromData;
	vector <string> relationToData;
	while (!exit)
	{
		//user input
		cout << "Relation Goes From: ";
		cin >> tempFrom;
		relationFromData.push_back(tempFrom);
		cout << endl << "Relation Goes To: ";
		cin >> tempTo;
		relationToData.push_back(tempTo);

		cout << endl << "Enter another Relation? [y/n]:	";
		cin >> tempExit;

		//get pointers for EdgeAddition

		//add edge
		d.EdgeAddition(tempFrom, tempTo);
			
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

class HeaderArray
{
public:

};





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
