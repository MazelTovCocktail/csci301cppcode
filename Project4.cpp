//Sean Conrad
//CSCI 301 Section 1
//Project 4, Linked List Concordance
//Due: 2/21/17

//Making an Alphabetically ordered list using Link Lists
//This program will give the concordance of text
//A concordance is a list of words and how many times they appear in the text
//The words will be ordered alphabetically.
//This program supports text files as well as user input.
//User may manually insert one word at a time.
//File loading will catch errors and ask user for a file name if a file cant be opened.
//A word is defined by a string a no more than 8 alpha characters.
//Any non alpha characters will be treated as a space between two words.

//#ifndef LIST_H
//#define LIST_H
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <cstdlib>
using namespace std;

class List
{
	public:
		typedef string item;                 //item is the primary node data member.
		List() { first = NULL; }             //default constructor.
		void insertWord(const item&);        //creates a new node for a word or adjusts the count of an exists word.
		bool isPresent(const item&) const;   //returns bool value. checks if word is present in the list.
		int length() const;                  //return the number of nodes in the list as an integer.
		void readFile();                     //pulls words from any text file to user chooses.
		friend std::ostream& operator << (std::ostream& out_s, const List& l);
		void menu() const;                   //displays menu commands.
		string preInsert();                  //formatts the users word before sending it to insertWord().
		int getCount(item&);
		
	private:
		struct node                          //private data types
		{
			int count;                       //count is number of time a word appears
			item word;                       //item is defined above. here we are using it as a string
			node *next;                      //pointer that points to the next node or is NULL
		};
		node *first;                         //first pointer points to the first node only
		node* get_node(const int, const item&, node*);//creates new nodes. Its a private function
};

//#endif

//#include "list.h"
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <cassert>
//#include <cstdlib>
//using namespace std;


//function for creating new nodes.
//used for greatly simplifying functions.
//Parameters: Count value (usually 1), word to be inserted, and an address of the next node or NULL.
List::node* List::get_node(const int count, const item& word, node* link)
{
	node *temp;
	temp = new node;
	temp->word=word;
	temp->count=count;
	temp->next=link;
	return temp;
}

//insertWord function. It will either insert a word if not already in the list
//or add 1 to the count if that word is already present.
//takes 1 word at a time. uses a string variable.
void List::insertWord(const item& entry)
{
	node* prev;
	
	//special case. List has no nodes or...
	//...entry is supposed to go before the first node.
	if(first == NULL || entry < first->word)
	{
		first = get_node(1,entry,first);
	}
	//Here it will create a new node for a word that is not already in the list
	//It will maintain alphabetical order when it inserts a new node.
	else if(!isPresent(entry))
	{
		prev = first;
		while(prev->next != NULL && prev->next->word <= entry)
			prev = prev->next;
		prev->next = get_node(1,entry,prev->next);
	}
	//If word is present, it will add 1 to the respective nodes count.
	//It searches for the entry word and stops once it is found.
	else
	{
		prev = first;
		while(prev->next != NULL && prev->word != entry)
			prev = prev->next;
		prev->count += 1;
	}
}

//preInsert is used only when the user wants to manually insert a word
//It formatts the user input but it only supports one word at a time.
//If a user enters a string of words it will only insert the first word.
string List::preInsert()
{
	char ch;
	item str;
	int i =0;
	
	cin.ignore();
	std::cout<<"Enter a word to insert: "<<endl;
	cin.get(ch);
	
	while(ch >= ' ')
	{
		if(isalpha(ch) && i<8)
		{
			str += tolower(ch);
			++i;
		}
		else
		{
			if(str > "")
			{
				insertWord(str);
				str = "";
			}
			i=0;
		}
		cin.get(ch);
	}
	insertWord(str);
	return str;
}

//returns a bool value if a specific string variable is present.
//uses a string variable as a parameter.
bool List::isPresent(const item& entry) const
{
	node* cursor;
	
	for(cursor = first; cursor != NULL && cursor->word != entry; cursor = cursor->next)
		;
	return (cursor != NULL);
	
}

//returns the count of a node associated with a word
//if word does not exist it returns a 0.
int List::getCount(item& entry)
{
	node* cursor;
	
	for(cursor = first; cursor != NULL && cursor->word != entry; cursor = cursor->next)
		;
	if(cursor != NULL && cursor->count > 0)
		return cursor->count;
	else
		return 0;
}

//This function will count the nodes and return an non negative integer.
//If the list has no nodes it will return a 0.
int List::length() const
{
	node* cursor;
	int count=0;
	
	for(cursor = first; cursor != NULL; cursor = cursor->next)
		++count;
	return count;
}

//read file will pull text from a text file chosen by the user.
void List::readFile()
{
	ifstream myfile; //name of the input file stream.
	string fileName; //string var used for the name of the file to be opened.
	string str; //string var where we are appending characters to.
	char ch; //character variable. Used to hold and check 1 character at a time.
	int i=0; //counts the number of characters in str.
	
	//ask user for a file to open. Set initial conditions for error detection.
	std::cout<<"Please enter a file to open"<<endl;
	std::cin>>fileName;
	myfile.open(fileName);
	
	//This loop will trigger if myfile cant be opened
	//will continue to loop if a myfile cant be opened
	while(myfile.fail() && fileName != "quit")
	{
		std::cout<<"Please enter an existing text file WITH file extension."<<endl;
		cin>>fileName;
		myfile.open(fileName);
	}
	
	//The following loop examines text one character at a time using .get().
	if(fileName != "quit")
		myfile.get(ch);
	while( myfile.good() )
	{
		//If the word to be inserted is 8 character long
		//OR if the character being check is not alpha or str has at least 1 character.
		if(isalpha(ch) && i < 8)
		{
			str += tolower(ch); //essentially appends the lower case alpha charactr to str.
			++i; //increments i
		}
		//If the character in question in non alpha or...
		//...the current string is 8 characters long.
		else
		{
			//checks here to make sure str isnt empty.
			//passes str to insertWord(), defined above.
			if(str > "")
			{
				insertWord(str); //sends the string to insertWord()
				str=""; //resets str to an empty string.
			}
			i=0; //resets i
		}
		myfile.get(ch); //gets the next character in the file.
	}
	//close file.
	myfile.close();
}

//use cout<<l1 to print the list.
//overloads << operator for output of each nodes contents.
//writes output to terminal
ostream& operator << (ostream& out_s, const List& l)
{
	List::node *cursor;
	//this function includes some formatting too!
	out_s<<"______________________\n";
	for(cursor = l.first; cursor != NULL && cursor->next != NULL; cursor=cursor->next)
	{
		out_s<<cursor->count<<".........."<<cursor->word<<endl;
	}
	if(cursor != NULL)
		out_s<<cursor->count<<".........."<<cursor->word;
	out_s<<"\n______________________";
	
	return out_s;
}

//class menu of all operations the user can access.
void List::menu() const
{
	//some formatting here. Used as a user command guide. Can be accessed with 'h'
	std::cout<<"\nList of user commands:"<<std::endl;
	std::cout<<"i   insert a single word"<<std::endl;
	std::cout<<"f   pull words from a text file"<<std::endl;
	std::cout<<"l   prints the number of nodes in the list"<<std::endl;
	std::cout<<"p   prints the words and count"<<std::endl;
	std::cout<<"c   prints the count of a specific word"<<std::endl;
	std::cout<<"q   quits closes the program"<<std::endl;
	std::cout<<"h   shows this menu again"<<std::endl;
}


//#include "list.h"
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <cassert>
//#include <cstdlib>
//using namespace std;

//main program.
int main()
{
	List l1; //object l1
	
	//essential variables used for the menu.
	char choice;
	string str;
	int n1, i;
	char ch;
	
	l1.menu();//call class menu for greater usability
	
	//menu driven programs are great!
	do
	{
		std::cin>>choice;
		switch(choice)
		{
			case 'i':
				str = l1.preInsert();
				str = "";
				break;
			case 'f':
				l1.readFile();
				break;
			case 'l':
				n1=l1.length();
				std::cout<<n1<<std::endl;
				break;
			case 'c':
				std::cin>>str;
				n1 = l1.getCount(str);
				std::cout<<str<<" appears "<<n1<<" times."<<endl;
				break;
			case 'p':
				std::cout<<l1;
				std::cout<<endl;
				break;
			case 'h':
				l1.menu();
				break;
			case 'q':
				std::cout<<"Bye!"<<std::endl;
				break;
			default:
				std::cout<<"Please enter a valid option."<<std::endl;
		}
	}while(choice != 'q');
	return 0;
	//thats it.
}
