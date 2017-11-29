//Sean Conrad
//CSCI 301 Section 1
//Project 1
//Due 1/19/2017

//This programm will determine if a user entered string is an array.
//it supports space and non alpha character removal
//the program will only support up to 80 characters

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#define SIZE 80
using namespace std;

//class declaration
class Palindrome
{
	private:
		char array[SIZE];
		bool result;
		int length;
	public:
		void setPalindrome(string);//Done.
		bool setResult(); //done.
		bool getResult() const; //done.
};



//the setPalindrome function will check each character, remove non alpha and spaces, and insert characters into an array.
void Palindrome::setPalindrome(string str)
{
	length = 0;
	for(char c : str)
	{
		if(isalpha(c)) 
		{
			array[length] = c;
			++length;
		}
	}
	

}

//the setResult function will create reverse[] and set it to the exact reverse of array[].
//then it will compare each array element by element, stopping only if it doesnt match or it has finished comparing
//then it will set the bool variable accordlingly
bool Palindrome::setResult()
{
	char reverse[SIZE];
	int i = 0;
	bool isTrue = true;
	
	for(int i = 0; i<length;++i)
	{
		reverse[length-1-i]=array[i];
		
	}
	
	i=0;
	for(i = 0; i<length;++i)
	{
		if(reverse[i] == array[i] && i != length) 
		{
			result = true;
		}
		
		else result = false;
		
	}
}

//will return a bool value.
bool Palindrome::getResult() const
{
	return result;
}

//main creates an object and call the appropriate functions from the Palindrome Class.
int main()
{
	Palindrome String;
	string str;
	cout<<"Enter a possible palindrome using only lower case letters."<<endl;
	getline(cin,str);
	
	String.setPalindrome(str);
	String.setResult();
	if( String.getResult() )
	{
		cout<<"It is a Palindrome.";
	}
	else
	{
		cout<<"It's NOT a Palindrome.";
	}
	return 0;
}
