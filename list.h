#ifndef LIST_H
#define LIST_H
#include <iostream>
#define HEIGHT 4
#define WIDTH 80
using namespace std;

class List
{
	private:
		int used[HEIGHT];
		int array[HEIGHT][WIDTH];
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

#endif
