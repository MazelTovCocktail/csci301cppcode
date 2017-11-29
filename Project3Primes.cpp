//Sean Conrad
//CSCI 301 Section 2
//Project 3, Prime Factorization Program

#include <iostream>
using namespace std;

int primeFactor(int,int);

int main()
{
	int value;
	int n = 2;
	
	cout<<"Please give a positive integer: ";
	cin>>value;
	cout<<"The prime factors are: ";
	primeFactor(value,n);
	return 0;
}

//This function uses recursion to list the prime factors of int value in ascending order.
//It does so by counting up from n=2 until n>value/2 or value%n == 0.
int primeFactor(int value, int n)
{
	//base case. Eventually int Value will be reduced to a prime number, or int n will be greater than int value/2
	if(value <= 2 || n > value/2)
	{
		cout<<value;
	}
	//This will divide int value by int n, eventually reducing int value to a prime number
	else if(n <= value/2 && value % n == 0)
	{
		cout<<n<<" ";
		return primeFactor(value/n, 2);
	}
	//if int n is not a prime factor of int value, increase int n by 1
	//if value is prime, eventually n > value/2
	else
	{
		return primeFactor(value,n+1);
	}
}
