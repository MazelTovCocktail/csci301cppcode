//Sean Conrad
//CSCI 301
//Stack class, Project 7
//Prime factoring using a stack.
//stack is array based.
//Array is capped at 500 elements.

#include <iostream>
using namespace std;

class stack
{
	public:
		stack(){ count = 0; }
		void push(int entry);
		int pop();
		int factorPrime();
		void emptyStack();
		friend ostream& operator << (ostream& out_s, const stack& s);
	private:
		int array[500];
		int count;
};

//push will add a new value to the stack.
void stack::push(int entry)
{
	array[count] = entry;
	++count;
}

//pop removes and returns the top value in the stack.
int stack::pop()
{
	--count;
	return array[count];
}

//sets count to 0, effectively emptying the stack;
void stack::emptyStack()
{
	count = 0;
}

//factors any int and places each factors in aa stack.
//factors are pushed in order from least to greatest.
int stack::factorPrime()
{
	int i = 2;
	int num1 = pop();
	bool isFactored = false;
	
	//i is the possible factor.
	//num1 in the value being factored.
	while(num1 > i)
	{
		//If i is a prime factor, push i.
		if(num1 % i == 0)
		{
			num1 = num1 / i;
			push(i);
			i = 2;
		}
		//else ++i and check again...
		else
			++i;
	}
	//push the remaining prime number.
	push(num1);
}


//Overload << operator for output.
//Includes some basic formatting.
ostream& operator <<(ostream& out_s,const stack& s)
{
	int i=s.count;
	out_s<<"  Please prime factors are: ";
	while(i > 0)
	{
		out_s <<s.array[i-1]<<" ";
		--i;
	}
	out_s<<endl;
	return out_s;
}

int main()
{
	stack s1;
	int input;
	bool loop = true;
	
	while(loop)
	{
		cout<<"Enter a numer you wish to factor. (0 to quit)"<<endl;
		cin>>input;
		if(input > 0)
		{
			s1.push(input);
			s1.factorPrime();
			cout<<s1<<endl;
			s1.emptyStack();
		}
		else
			loop = false;
	}
	return 0;
}
