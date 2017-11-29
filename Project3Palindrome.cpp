//Sean Conrad
//CSCI 301 Section 1
//Project 3 Palindrome


//program is functioning correctly.
#include <iostream>
#include <string>
using namespace std;

bool palindrome(char*,int,int);

main()
{
	char ch;
	int i = 0;
	int length;
	char str[100];
	
	cout<<"Please enter a phrase."<<endl;
	cin.get(ch); //cin.get() pulls each input character one at a time in order of input
	while(ch >= ' ')
	{
		if(isalpha(ch))  //only proceeds if character in question is a letter
		{
			str[i] = tolower(ch); //changes the letter to lowercase and inserts it into the array.
			++i;
			++length;
		}
		cin.get(ch);
	}
	//its important to set i=0 and length = length -1.
	length -=1;
	i = 0;
	//palindrome() is a bool and its return value will determine the print statement.
	if(palindrome(str, i, length))
	{
		cout<<"Is a palindrome"<<endl;
	}
	else
	{
		cout<<"Is NOT a palindrome"<<endl;
	}
	
	return 0;
}

//to properlly start this recursive function, you need an array[], i = 0, length = number of elements in array -1.
bool palindrome(char str[], int i, int length)
{
	if(length - i == 0) //base case
		return true;
	else if(str[length-i] == str[i-1]) //smaller problem
	{
		return palindrome(str, ++i, length);
	}
	else
		return false; //will end here if its not a palindrome.
}
