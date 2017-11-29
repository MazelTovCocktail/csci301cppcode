//Sean Conrad
//CSCI 301 Project 8
//Queue simulation

#include <iostream>
#include <random>
using namespace std;

class Queue
{
	public:
		Queue();
		~Queue();
		void enqueue(int entry);
		int dequeue();
		bool empty(){ return count == 0; }
		int size(){ return count; }
		friend ostream& operator<<(ostream& out_s, const Queue& q);
	private:
		struct node
		{
			int data;
			node *next;
		};
		node *front;
		node *rear;
		int count;
};

Queue::Queue()
{
	front = NULL;
	rear = NULL;
	count = 0;
}

Queue::~Queue()
{
	node *temp;
	while(temp != NULL)
	{
		temp = front;
		if(front != NULL)
			front = front->next;
		delete temp;
	}
	rear = front;
	count = 0;
}

void Queue::enqueue(int entry)
{
	node *temp;
	temp = new node;
	temp->data = entry;
	temp->next = NULL;
	if(front == NULL)
		front = temp;
	else
		rear->next=temp;
	rear = temp;
	++count;
}

int Queue::dequeue()
{
	node *temp = front;
	int dequeued = front->data;
	front = front->next;
	delete temp;
	if(front == NULL)
		rear = NULL;
	--count;
	return dequeued;
}
//Friend function for printing a queue object.
ostream& operator<<(ostream& out_s, const Queue& q)
{
	Queue::node *temp = q.front;
	while(temp != NULL)
	{
		out_s<<temp->data<<"  ";
		temp=temp->next;
	}
	return out_s;
}

int main()
{
	int linesOpen;
	Queue line[20];
	int trans_time[20];
	
	int i; //used for for loops
	int count = 0; //# of transactions completed
	int entry_time; //marks time a customer enters a queue.
	int wait_time = 0; //time waited by customer.
	int wait_sum = 0; //total time waited by all served customers
	int max_wait = 0; //logs the longest wait time.
	int trans_sum = 0;
	int seed; //used to randomize the simulation
	int smallest_l = 0; //marks the shortest line
	int DURATION; //duration of the simulation
	int ARV_PROB; //average prob of a customer entering a line.
	int MAX_TRANS_TIME; //maximum transaction time.
	//Inputs...
	cout<<"How many lines are open(20 lines max): ";
	cin>>linesOpen;
	cout<<"Average probability of a customer entering a line (%): ";
	cin>>ARV_PROB;
	cout<<"Duration of the simulation in Ticks: ";
	cin>>DURATION;
	cout<<"Maximum transaction time in Ticks: ";
	cin>>MAX_TRANS_TIME;
	cout<<"Seed value->";
	cin>>seed;
	srand(seed);
	//Initilizes servers to 0.
	for(i = 0; i<linesOpen; i++)
		trans_time[i] = 0;
	//main program structure.
	for(int time = 0; time <= DURATION; ++time)
	{
		//Sets smallest_l to index of the shortest line.
		smallest_l = 0;
		for(i=0; i<linesOpen; i++)
		{
			if(line[i].size() < line[smallest_l].size())
				smallest_l = i;
		}
		//Determines if a customers enters a queue.
		if(rand()%100 < ARV_PROB)
			line[smallest_l].enqueue(time);
		
		//Program output that displays the state of each server and queue at each tick.
		cout<<"Tick: "<<time<<endl;
		for(i = 0; i < linesOpen; i++)
			cout<<"   Transaction Time: "<<trans_time[i]<<"   Line: "<<line[i]<<endl;
		cout<<endl;
		//If a server is finished, dequeue if a customer is waiting.
		for(i = 0; i < linesOpen; i++)
		{
			if(!line[i].empty() && trans_time[i] == 0)
			{
				entry_time = line[i].dequeue();
				wait_time = time-entry_time;
				wait_sum += wait_time;
				if(wait_time > max_wait)
					max_wait=wait_time;
				++count;
				trans_time[i] = (rand()%MAX_TRANS_TIME)+1;
				trans_sum += trans_time[i];
			}
			else
			{
				if(trans_time[i] > 0)
					--trans_time[i];
			}
		}
	}
	cout<<"A total of "<<count<<" customers were served over a period of "<<DURATION<<" ticks."<<endl;
	cout<<"The longest time a customer waited was "<<max_wait<<" ticks."<<endl;
	if(count > 0)
	{
		cout<<"The average transaction lasted "<<trans_sum/count<<" ticks."<<endl;
		cout<<"The average wait time was "<<wait_sum/count<<" ticks."<<endl;
	}
	return 0;
}

