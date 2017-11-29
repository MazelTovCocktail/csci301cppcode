
/*    Initialize a list to be empty (the default constructor). - DONE.
    Re-initialize an existing list to be empty. - DONE.
    Insert a value into a list, in the appropriate position. If the value is already present, the list is unchanged. - DONE.
    Remove a value from a list. If the value is not present, the list is unchanged. - DONE.
    Return the length of a list. - DONE.
    Report whether or not a particular value is present in a list. - DONE.
    Return the value of the kth element of a list. - DONE.
    Merge two lists into a third; the third list contains all the values found in the first two lists, in order, with no values duplicated. - DONE.
    Write out the values in a list, in order, to an output stream. - DONE.
*/

#include <iostream>
#define HEIGHT 4
#define WIDTH 80
using namespace std;

typedef int integer;

class List
{
	private:
		int used[HEIGHT];
		integer array[HEIGHT][WIDTH];
	public:
		void initializeLists();//done TESTED!
		void clearList(int);//done parameters(int LIST) TESTED!
		int searchValue(int, int);//done parameters (int VALUE TO FIND, int LIST TO SEARCH) TESTED!
		int returnLength(int);//done parameters (int LIST) TESTED!
		int returnValue(int, int);//done parameters(int ELEMENT, int LIST) TESTED!
		int printList(int);//done parameters(int LIST) TESTED!
		void sortList(int);//done parameters(int LIST) TESTED!
		void removeValue(int, int);//done parameeters(int VALUE, int LIST) TESTED!
		void insertValue(int, int);//done parameters(int VALUE, int LIST) TESTED!
		void mergeLists(int, int, int);//done parameters(int LIST to get values from, int LIST to get values from, int LIST to put values) TESTED!
		void menu();//done menu for main() TESTED!
		
};



void List::initializeLists()
{
    
	//This is the default values that will be stored in the 2D array.
	array[0][0]=0;
	array[1][0]=0;
	array[2][0]=0;
	used[0] = 0;
	used[1] = 0;
	used[2] = 0;
	
	//cout<<array[0][0]<<" "<<array[1][0]<<" "<<array[2][0]<<endl;
	
}

int List::searchValue(int value, int list)
{
	int i = 0;
	bool isFound = false;
	int index;
	int listValue;
	
	if(list<3)
	{
		for(int i = 0; i<used[list]; ++i)
		{
			listValue = array[list][i];
			if(listValue == value)
			{
				isFound = true;
				index = i;
				i = used[list];
			}
		}
	}
	if(isFound == true)
	{
		return index;
	}
	else
	{
		return -1;
	}
}

int List::returnLength(int list)
{
	int usedTemp = used[list];
	if(usedTemp > 0)
	{	
		cout<<"list "<<list<<" has "<<used[list]<<" elements"<<endl;
	}
	else
	{
		cout<<"list "<<list<<" has no values stored within it."<<endl;
	}
}


int List::returnValue(int element, int list)
{
	if(array[list][element] >= 0)
	{
		cout<<"The element "<<element<<" in list "<<list<<" is "<<array[list][element]<<"."<<endl;
	}
	else
	{
		cout<<"No value exists in element "<<element<<"."<<endl;
	}
}

int List::printList(int list)
{
	int i = 0;
	int usedTemp = used[list];
	
	if(usedTemp > 0)
	{
		cout<<"<";
		for(i=0;i<usedTemp;++i)
		{
			cout<<array[list][i]<<",";
		}
		cout<<" >"<<endl;
	}
}

void List::sortList(int list)
{
	int i = 0;
	int j = i+1;
	int temp;
	int usedTemp = used[list];
	int min_pos;
	
	for(i = 0; i<usedTemp-1; ++i)
	{
		for(j= i+1; j<usedTemp; ++j)
		{
			min_pos = i;
			if(array[list][j] < array[list][min_pos] )
			{
				min_pos = j;
			}
		}
		if(min_pos != i)
		{
			temp = array[list][i];
			array[list][i] = array[list][min_pos];
			array[list][min_pos] = temp;
		}
	}
}

void List::removeValue(int value, int list)
{
	int i = 0;
	int index;
	
	for(i=0; i<used[list]; ++i)
	{
		if(array[list][i] == value)
		{
			index = i;
			i = used[list];
		}
	}
	
	if(index >= 0)
	{
		array[list][index] = array[list][used[list]-1];
		used[list] -= 1;
		sortList(list);
	}
}

void List::insertValue(int value, int list)
{
	int temp = used[list];
	int found;
	found = searchValue(value,list);
	if(found == -1)
	{
		array[list][temp] = value;
		used[list] = temp + 1;
		sortList(list);
	}
}

void List::clearList(int list)
{
	used[list]=0;
}

void List::mergeLists(int list, int list2, int list3)
{
	int i = 0;
	int searchList;
	int usedTemp;
	
	for(i=0; i < used[list]; ++i)
	{
		searchList = searchValue(array[list][i],list3);
		if(searchList == -1)
		{
			usedTemp = used[list3];
			array[list3][usedTemp] = array[list][i];
			used[list3] += 1;
		}
	}
	
	for(i=0; i < used[list2]; ++i)
	{
		searchList = searchValue(array[list2][i],list3);
		if(searchList == -1)
		{
			usedTemp = used[list3];
			array[list3][usedTemp] = array[list2][i];
			used[list3] += 1;
		}
	}
	//call sortList() function to sort the third list after all non duplicate values have been added.
	sortList(list3);
}

void List::menu()
{
	cout<<"Use the menu to for available options. You must seperate inputs by a space. Ex: m 0 1 2"<<endl;
	cout<<"c LIST              :clear a list of values. ex: c 0"<<endl;
	cout<<"s VALUE LIST        :search a list for a value. ex: s 27 2"<<endl;
	cout<<"l LIST              :find the number of elements in a list. ex: l 0"<<endl;
	cout<<"v ELEMENT LIST      :return the value of a specific element of a list. ex: v 8 0"<<endl;
	cout<<"p LIST              :print an entire list. ex: p 2"<<endl;
	cout<<"d VALUE LIST        :removes a value from the list. ex: d 19 0"<<endl;
	cout<<"a VALUE LIST        :adds a value to a list. ex: a 19 0"<<endl;
	cout<<"m LIST1 LIST2 LIST3 :merges LIST1 and LIST2 into LIST3. ex: m 0 1 2"<<endl;
	cout<<"h                   :shows this menu."<<endl;
	cout<<"q                   :quit and close the program."<<endl;
}

main()
{
	List l1;
	char choice;
	int n1, n2, n3;
	int returnValue;
	
	l1.initializeLists();
	l1.menu();
	
	do
	{
		cin>>choice;
		switch(choice)
		{
			case 'c':
				cout<<"Please give a list to clear."<<endl;
				cin>>n1;
				l1.clearList(n1);
				break;
			case 's':
				cout<<"Please give a value and a list."<<endl;
				cin>>n1>>n2;
				returnValue = l1.searchValue(n1,n2);
				cout<<"The value "<<n1<<" is element "<<returnValue<<" of list "<<n2<<"."<<endl;
				break;
			case 'l':
				cout<<"Please give a list."<<endl;
				cin>>n1;
				returnValue = l1.returnLength(n1);
				cout<<returnValue;
				break;
			case 'v':
				cout<<"Please give an element and list."<<endl;
				cin>>n1>>n2;
				returnValue = l1.returnValue(n1,n2);
				cout<<returnValue;
				break;
			case 'p':
				cout<<"Please enter a list to print."<<endl;
				cin>>n1;
				l1.printList(n1);
				break;
			case 'd':
				cout<<"Please enter a value and list."<<endl;
				cin>>n1>>n2;
				l1.removeValue(n1,n2);
				break;
			case 'a':
				cout<<"Please give the value and list."<<endl;
				cin>>n1>>n2;
				l1.insertValue(n1,n2);
				break;
			case 'm':
				cout<<"Please enter 3 lists."<<endl;
				cin>>n1>>n2>>n3;
				l1.mergeLists(n1,n2,n3);
				break;
			case 'h':
				l1.menu();
				break;
			case 'q':
				cout<<"Bye!"<<endl;
				break;
			default:
				cout<<"Incorrect input. Use h for help."<<endl;
		}
	}while(choice != 'q');
	return 0;
}











