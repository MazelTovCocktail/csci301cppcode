//Sean Conrad
//CSCI 301 Section 1
//Project 6 Recursive Concordance
//Due 16 March 2017

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
//#ifndef LIST_H
//#define LIST_H

using namespace std;

class List
{
	public:
		typedef string item;
		List()
		{ 
			first = NULL; 
		}  //Constructor, inline.
		~List(); //Deconstructor
		//calls the private recursive function length(). Return an int of number of nodes in the list.
		int UseLength()
		{
			node* p=first;
			int count = 0;
			return length(p,count);
		}
		//Call the private recursive function present(). Returns a bool if word is present.
		bool UsePresent(const item& entry)
		{
			node* p = first;
			return present(entry, p); 
		}
		//calls private recursive function getCount(). Returns an int. 0 if entry not found.
		int UseGetCount(const item& entry)
		{
			node* p = first;
			return getCount(entry,p);
		}
		//calls the private recursive function insertWord()
		void UseInsertWord(const item& entry)
		{
			node* p = first;
			bool isPresent = present(entry,p);
			p=first;
			insertWord(entry,p, isPresent);
		}
		//calls the private recursive function removeWord()
		//Only calls function if entry already exists in List.
		void UseRemoveWord(const item& entry)
		{
			//requires 2 pointers
			//*p points to first node
			//*prev is undefined.
			node* p = first;
			node* prev;
			if(present(entry,p))
				removeWord(entry,p,prev);
		}
		//Gets file name via user input, calls recursive function readFile() for adding characters.
		void UseReadFile();
		void classMenu();
		friend ostream& operator << (std::ostream& out_s, List& l);
	
	private:
		struct node
		{
			int count;
			item word;
			node *next;
		};
		node *first;
		node* get_node(int count, const item& word, node* link);
		int length(node* cursor, int count);
		bool present(const item& entry, node* p);
		int getCount(const item& entry, node* p);
		void insertWord(const item& entry, node* p, bool isPresent);
		void removeWord(const item& entry, node* p, node* prev);
		void readFile(string str,int i, char ch, ifstream& myfile);
		void r_write(ostream& o_f, node *p);
};
//#endif

//#include "list.h"
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <cstdlib>
//using namespace std;

//returns a node pointer to a newly created node.
List::node* List::get_node(int count, const item& word, node* link)
{
	node *temp;
	temp = new node;
	temp->next = link;
	temp->word = word;
	temp->count = count;
	return temp;
}

//destructor
//Deletes every node in the list.
List::~List()
{
	node* temp;
	while(first != NULL)
	{
		temp = first;
		first = first->next;
		delete temp;
	}
}

//returns an int value
//counts the number of nodes in the list.
//*p must be equal to first, count = 0.
int List::length(node* cursor, int count)
{
	//Escape condition. cursor reached end of list
	//OR list if empty.
	if(cursor == NULL)
		return count;
	//Move cursor up the list to the next node.
	//Increment count by 1.
	else
		length(cursor=cursor->next, ++count);
}

//*p must be set equal to *first upon first call.
//searches the list. If entry is found return true, else return false.
bool List::present(const item& entry, node* p)
{
	//If *p has reached the end of the list.
	//OR list is empty.
	if(p == NULL)
		return false;
	//If a match is found, returns bool true.
	else if(p->word == entry)
		return true;
	//Moves *p up the list to the next node.
	else
		present(entry, p=p->next);	
}

//*p must be set equal to *first upon first function call.
//returns int count of a node in the list.
//if entry cant be found, returns a 0.
int List::getCount(const item& entry, node* p)
{
	//if list is empty or *p has reached the end of the list.
	if(p == NULL)
		return 0;
	//general case: If target node is found.
	else if(p->word == entry)
		return p->count;
	//advance *p to next node.
	else
		getCount(entry, p=p->next);
}

//Only call this function if present() is false.
//Assumes this as a precondition.
//*p must be set = to *first.
void List::insertWord(const item& entry, node* p, bool isPresent)
{
	//Entry is not in the list yet.
	if(!isPresent)
	{
		//If list is empty or entry goes before first node.
		if(first == NULL || first->word > entry)
			first = get_node(1, entry, first);
		
		//If p is on last node and last node goes before entry.
		else if(p->next == NULL)
			p->next = get_node(1,entry,p->next);
		
		//Insert between two nodes.
		else if(p->next->word > entry)
			p->next = get_node(1,entry,p->next);
		
		//advance p to next node.
		else
			insertWord(entry, p=p->next, isPresent);
	}
	//Entry is present in the list.
	else if(isPresent)
	{
		if(p->word == entry)
			p->count += 1;
		else
			insertWord(entry, p=p->next, isPresent);
	}
}

//only run if present() returns a true value.
//Assumes value to be removed is already present in the list.
void List::removeWord(const item& entry, node* p, node* prev)
{
	//If entry is found in the first node.
	//Works if only 1 node is present.
	if(first->word == entry)
	{
		p = first;
		first = first->next;
		delete p;
	}
		
	//If *p has found the target node.
	//Works if *p is at last node.
	else if(p->word == entry)
	{
		prev->next = p->next;
		delete p;
	}
	
	//If p->word does not match entry
	//Set prev = p.
	//Advance p up the list 1 node.
	else
	{
		prev = p;
		p=p->next;
		removeWord(entry,p,prev);
	}
}

//function for opening/closing the file and asking user for input.
//Also used to call the private recursive function readFile().
void List::UseReadFile()
{	//variables needed for reading and opening files.
	char ch;
	int i = 0;
	string fileName;
	string str;
	ifstream myfile;
	
	//Attempts to open the file. Sets condition for while() loop.
	cin.ignore();
	std::cout<<"Please type a file you wish to open, including the file extension."<<endl;
	cin>>fileName;
	myfile.open(fileName);
	//Will loop until file is opened or user types 'quit'
	while(myfile.fail() && fileName != "quit")
	{
		std::cout<<"File not found.\nPlease enter a different file name."<<endl;
		std::cout<<"Use the file extension and file path in necessary. Type 'quit' to back out."<<endl;
		cin>>fileName;
		myfile.open(fileName);
	}
	//Only calls readFile() if a file was opened.
	if(fileName != "quit")
	{
		myfile.get(ch);
		readFile(str, i, ch, myfile);
	}
	//Closes file once readFile() has finished.
	myfile.close();
}

void List::readFile(string str, int i, char ch, ifstream& myfile)
{
	if(myfile.good())
	{
		//if current character is alpha...
		//...and less than 8 characters are present...
		//...append lower case character to str and...
		//increment i by 1.
		if(isalpha(ch) && i < 8)
		{
			str += tolower(ch);
			++i;
		}
		//must have at least 8 characters
		//OR must have reached end of word.
		else
		{
			//checks if a word is present.
			if(str>"")
			{
				UseInsertWord(str);
			}
			//Here it check if ch is alpha
			//Appends lower case char to the string
			//...and increments i.
			if(isalpha(ch))
			{
				str = tolower(ch);
				i = 1;
			}
			//If the character is no alpha
			//Set i to 0 and empty str.
			else
			{
				str="";
				i=0;
			}
		}
	myfile.get(ch); //Get next character
	readFile(str, i, ch, myfile); //Recursive call.
	}
}
//classMenu display.
void List::classMenu()
{ 
	std::cout<<" ___________________________________________________________"<<endl;
	std::cout<<"| Command  |  Command description.                          |"<<endl;
	std::cout<<"|-----------------------------------------------------------|"<<endl;
	std::cout<<"|q         |   quits the program.                           |"<<endl;
	std::cout<<"|m         |   shows this menu again.                       |"<<endl;
	std::cout<<"|p         |   prints the contents of the list.             |"<<endl;
	std::cout<<"|f         |   reads text data from a file.                 |"<<endl;
	std::cout<<"|r         |   removes a specific word from the list.       |"<<endl;
	std::cout<<"|l         |   shows the number of unique words in the list.|"<<endl;
	std::cout<<"|c         |   shows number of time a specific word appears.|"<<endl;
	std::cout<<"|___________________________________________________________|"<<endl;
}
//The next two functions are for overloading the operator
//friend function call the recursive function
ostream& operator << (ostream& out_s, List& l)
{	//Some formatting...
	out_s<<"Count       Word"<<endl;
	out_s<<"_________________"<<endl;
	//recursive call. out_s is call by reference
	l.r_write(out_s, l.first);
	out_s<<"_________________"<<endl;
	return out_s;
}
//r_write is the recursive half of the the output.
void List::r_write(ostream& o_f, node *p)
{
	if(p!=NULL)
	{
		o_f << p->count<<"          "<<p->word<<endl;
		//o_f is changing out_s via call by reference
		//p advances to next node in the list
		r_write(o_f,p->next);
	}
}

//#include "list.h"
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <cstdlib>
//using namespace std;
int main()
{
	List l1; //Create object
	
	//Some variables are needed.
	char choice;
	string str;
	int num1;
	l1.classMenu();
	do
	{
		std::cin>>choice;
		switch(choice)
		{
			case 'q':
				std::cout<<"Bye!";
				break;
			case 'f':
				l1.UseReadFile();
				break;
			case 'p':
				cout<<l1<<endl;
				break;
			case 'r':
				std::cout<<"In lower case, type the word you wish to remove from the list:"<<endl;
				std::cin>>str;
				l1.UseRemoveWord(str);
				break;
			case 'l':
				num1 = l1.UseLength();
				std::cout<<num1<<endl;
				break;
			case 'c':
				std::cout<<"In lower case, type a word you want to see the count of:"<<endl;
				std::cin>>str;
				num1 = l1.UseGetCount(str);
				std::cout<<num1<<endl;
				break;
			case 'm':
				l1.classMenu();
				break;
		}
	}while(choice != 'q');
	return 0;
}
