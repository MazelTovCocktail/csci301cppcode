#include <iostream>
#include "list.h"
#define HEIGHT 4
#define WIDTH 80
using namespace std;


main()
{
	List l1;
	char choice;
	int n1, n2, n3;
	int returnValue;
	
	l1.initializeLists();
	cout<<"Welcome to the Ordered List program!"<<endl;
	cout<<"\n";
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
				cout<<"To search, give a value and a list."<<endl;
				cin>>n1>>n2;
				returnValue = l1.searchValue(n1,n2);
				if(returnValue == -1)
				{
					cout<<"The value "<<n1<<" does not exist in list "<<n2<<"."<<endl;
				}
				else
				cout<<"The value "<<n1<<" is element "<<returnValue<<" of list "<<n2<<"."<<endl;
				break;
			case 'l':
				cout<<"Please give a list."<<endl;
				cin>>n1;
				returnValue = l1.returnLength(n1);
				if(returnValue > 0)
					cout<<"The list "<<n1<<" has "<<returnValue<<" different values."<<endl;
				else
					cout<<"The list "<<n1<<" has no value stored within it."<<endl;
				break;
			case 'v':
				cout<<"Please give an element and list. Element count starts at 0."<<endl;
				cin>>n1>>n2;
				returnValue = l1.returnValue(n1,n2);
				if(returnValue == -1)
				{
					cout<<"There are no values in element "<<n1<<" in list "<<n2<<".\nElement index starts at 0. EG: 1st element is in position 0."<<endl;
				}
				else
				{
					cout<<"Element "<<n1<<" in list "<<n2<<" is value "<<returnValue<<"."<<endl;
				}
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

