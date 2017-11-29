//Sean Conrad
//CSCI 301 Section 1
//Project 3
//GCD recursive program

#include <iostream>
using namespace std;

int GCD(int,int);

main()
{
	int num1, num2, result;
	
	//all that happens in main() is ask user for input and pring final result.
	cout<<"Welcome to the GCD program."<<endl;
	cout<<"Please type the first integer and press ENTER"<<endl;
	cin>>num1;
	cout<<"Please type the second integer and press ENTER"<<endl;
	cin>>num2;
	
	result = GCD(num1,num2);
	cout<<"The GCD of "<<num1<<" and "<<num2<<" is:"<<endl;
	cout<<result;
}

int GCD(int n1, int n2)
{
	if(n1 == n2) //base case. see if both values equal.
	{
		return n1;
	}
	else if(n1 > n2)//smaller problem, determine which value is bigger
	{
		return GCD(n1-n2, n1);
	}
	else
	{
		return GCD(n1, n2-n1);
	}
}
