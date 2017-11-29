//Sean Conrad
//CSCI 301 Section 1
//Project 5 Due 3 March 2017

//This program uses an unordered list of characters stored in a doubly linked list.
//It takes 1 line of characters at a time and processes those characters 1 at a time.
//each character will be stored in its own node.
//'#' characters will delete the last node in the list.
//an input like: Aa#Bb#Cc# will have an ouput like: ABC
//A space signifies the end of an input.


//#ifndef LIST_H
//#define LIST_H
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

class List
{
	public:
		typedef char item; //item is the data contained in each node. Can be any data type, here it is a char.
		List()  //constructor
		{ 
			first = NULL;
			last = NULL;	
		}
		~List();  //destructor
		void appendItem(const item&);  //appends a character to the end of a list. Needs a char to append as the parameter.
		void removeLast(); //No parameters. Removes the last character in the list.
		void lineInput(); //processes the input line character by character and called removeLast() or appendItem().
		friend std::ostream& operator << (std::ostream& out_s, const List& l);
		void classMenu();  //Class menu. An easy built in function for how this class is intended to be used.
		
	private:
		struct node //node structure. Contains 1 data member and two pointers.
		{
			item data;
			node *forward;
			node *backward;
		};
		node* first; //Points to first node in the list
		node* last; //Points to the last node in the list.
		node* get_node(const item& entry, node* forwardLink, node* backwardLink); //returns a pointer address to a new node.
};

//#endif

//#include "LIST_H"
//#include <iostream>
//#include <cassert>
//#include <string>

//Returns a pointer address to a newly created node.
List::node* List::get_node(const item& entry, node* forwardLink, node* backwardLink)
{

	node *temp;
	temp = new node;
	temp->data = entry;
	temp->forward = forwardLink;
	temp->backward = backwardLink;
	return temp;
}

//default destructor. deletes every node in the list...
List::~List()
{
	node *temp;
	
	while(first != NULL)
	{
		temp = first;
		first = first->forward;
		delete temp;
	}
	last = first;
}

void List::appendItem(const item& entry)
{
	if(first == NULL) //Special case: List is empty. This will run if its the first time adding a node, or first node was previously deleted.
	{
		first = get_node(entry, NULL, NULL); //get_node() is given NULL values since we are adding the first node in the list.
		last = first;
	}
	else //Will run if at least 1 node already exists.
	{
		last->forward = get_node(entry, NULL, last); //Connecting the pointers of the last node to the new node.
		last = last->forward; //Move *last up one node.
	}
}

//This function deletes the last node.
void List::removeLast()
{
	node *p;
	p=last; //*p is required to delete the node.
	
	//Runs if the list has more than 1 node.
	if(last != NULL && last != first)
	{
		last = last->backward;
		last->forward=NULL;
		delete p;
	}
	//Runs if there is only 1 node in the list.
	else if(last != NULL && last == first)
	{
		last = NULL;
		first = NULL;
		delete p;
	}
	//Do nothing if the list is empty...
}

//This function prompts the user for input and processes the characters 1 at a time.
//It will called removeLast() and appendItem() as needed.
void List::lineInput()
{
	char ch;
	cin.ignore();
	std::cout<<"Please enter a string of characters. # will delete most last character."<<std::endl;
	cin.get(ch); //Using cin.get()
	
	while(ch != '\n') //While loop will stop once it reaches the end of stream or encounters a space.
	{
		if(ch == '#')
		{
			removeLast();
		}
		else
		{
			appendItem(ch);
		}
		cin.get(ch);
	}
}

//Friend function for overloading the << operator for output.
//Use with the line std::cout<<OBJECT_NAME;
ostream& operator << (ostream& out_s, const List& l)
{
	List::node *cursor;
	//this function includes some formatting too!
	out_s<<"______________________\n";
	for(cursor = l.first; cursor != NULL && cursor->forward != NULL; cursor=cursor->forward)
	{
		out_s<<cursor->data<<endl;
	}
	if(cursor != NULL)
		out_s<<cursor->data<<endl;
	out_s<<"\n______________________";
	
	return out_s;
}

//Class menu. This is here to show how the class is intended to be used by the user.
void List::classMenu()
{
	std::cout<<"i   Input command. Type a string a characters you want to input. # will delete the previous character."<<std::endl;
	std::cout<<"p   Print list command. Prints the values contained within the list."<<std::endl;
	std::cout<<"d   Delete command. This will delete the entire list."<<std::endl;
	std::cout<<"q   Quit command. This will quit and close the program."<<std::endl;
	std::cout<<"m   Menu command. This will show this menu of commands again"<<std::endl;
	std::cout<<"TIPS: \nCommands must be lowercase. \nThe program doesn't support spaces during input. \nAn input like: Aa#Bb#Cc#! \nHas an output like: ABC!"<<std::endl;
}

//#include "LIST_H"
//#include <iostream>
//#include <cassert>
//#include <string>

int main()
{
	List l1;
	l1.classMenu();
	char choice;
	
	do
	{
		std::cin>>choice;
		switch(choice)
		{
			case 'i':
				l1.lineInput();
				break;
			case 'p':
				std::cout<<l1;
				std::cout<<std::endl;
				break;
			case 'd':
				l1.~List();
				break;
			case 'q':
				std::cout<<"Bye!";
				break;
			case 'm':
				l1.classMenu();
				break;
			default:
				std::cout<<"Command not valid. Please use a valid command from the menu."<<endl;
				l1.classMenu();
				break;
		}
	}while(choice != 'q');
	return 0;
}






