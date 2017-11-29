#include <iostream>
#include "list.h"
#define HEIGHT 4
#define WIDTH 80
using namespace std;

//InitializeLists function will set the run on start. It will set each list length to 0
//Personal note: This is the newest version of the function.
void List::initializeLists()
{
    
	//This is the default values that will be stored in the 2D array.
	array[0][0]=0;
	array[1][0]=0;
	array[2][0]=0;
	array[3][0]=0;
	used[0] = 0;
	used[1] = 0;
	used[2] = 0;
	used[3] = 0;
	
	//prints a statement to confirm list lengths at program start.
	cout<<"Lists lengths set to: "<<used[0]<<" "<<used[1]<<" "<<used[2]<<" "<<used[3]<<endl;
	
}

//search function return index value or -1. Uses linear search.
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
		return -1;   //return -1 allows for if statements that controls cout<< statements if value isnt found.
	}
}

//returnLength() just returns the value of used[]. It will give number of elements. Highest used index is used[] - 1.
int List::returnLength(int list)
{
	int usedTemp = used[list];
	return usedTemp;
}

//returnValue will check if the element exists by checking used[].
//It will return an int value from the list or -1.
//cout/print statements are in main().
int List::returnValue(int element, int list)
{
	int exists = used[list] - 1;
	if( exists >= element)
	{
		return array[list][element];
	}
	else
	{
		return -1;
	}
}

//printList() will print its own statements using a for() loop.
//if list is empty, it will print '< >'.
int List::printList(int list)
{
	int i = 0;
	int usedTemp = used[list];
	
	cout<<"List "<<list<<":\n"<<"<";
	if(usedTemp > 0)
	{
		for(i=0;i<usedTemp;++i)
		{
			cout<<array[list][i]<<",";
		}
	}
	cout<<" >"<<endl;
}

//sortList() cannot be directly called by the user via menu commands
//instead, sortList() is called in various other class functions to reduce complexity.
//to call sortList() from menu, use the mergeLists command and set all three lists to the list...
//...you want sorted. eg: command 'm' Lists: 0 0 0  ---> this will sort array[0].
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

//removeValue() searches and removes a user given value from a list if its found.
//removeValue() does not return anything to main().
//This function calls the sortList() function only if the value has been found.
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

//insertValue() may call up to 2 other class functions.
//It uses searchValue() to identify duplicates, and only inserts the value if no duplicate has been found.
//If no duplicate has been found it will insert the value to the end of array[LIST], add 1 to used[LIST], and call sortList().
//If duplicate is found nothing will happen.
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

//Sets used[LIST] to 0, effectivly clearing array[LIST] of values.
void List::clearList(int list)
{
	used[list]=0;
}

//mergeLists() merges the first two given lists into the third given list.
void List::mergeLists(int list, int list2, int list3)
{
	int i = 0;
	int searchList;
	int usedTemp;
	
	//here it will compare LIST to LIST3 using searchValue().
	//it will only insert non duplicate values at the end of array[list3].
	//it will also adjust used[LIST3] accordingly.
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
	
	//here it will compare LIST2 to LIST3 using searchValue()
	//because LIST values have already been inserted to LIST3...
	//...there is no risk of duplicates being added to LIST3.
	//it will only insert non duplicate values to the end of array[list3].
	//it will also adjust used[LIST3] accordingly.
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

//Menu function. Command Guide to be displayed to user.
//can be called using command 'h'
void List::menu()
{
	cout<<"Type the command letter then press ENTER and then submit parameters. eg: m 'ENTER' 0 1 2"<<endl;
	cout<<"Use the menu to for available options. You must seperate inputs by a space. Ex:0 1 2"<<endl;
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

