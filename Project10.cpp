#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

/* Binary Search Tree - BST
THIS PROGRAM HAS RECURSIVE FUNCTIONS
Tree structure where each node and the root have no more than 2 pointers.
Good for effecient searching.
O(log(n)) - Best Case
O(n) - Worst Case
*/

using namespace std;

class BST
{
	public:
		//Change the datatype of the tree
		typedef string item;
		
		//default constructor
		BST(){ root = NULL; }
		BST(const BST &source) { root = r_copy(source.root); }
		~BST() { r_destroy(root); }
		
		//Recursive helper functions - Recursion is private
		void destroy() { r_destroy(root); } //destroys the tree.
		void print() { r_print(root); } //displays the contents of the tree
		int length() { r_length(root); } //length of the tree
		void Insert(item entry) { r_insert(root, entry); } //insert an item into the tree
		void remove(item target) { r_remove(root, target); } //finds and removes target item
		
		//non recursive functions
		bool present(item target); //returns bool if target exists in the tree
		bool isEmpty() { return root == NULL; } //Inline, returns true if tree is empty
		
		//copy assignment operator...
		void operator = (BST source);
		
	private:
		
		struct node
		{
			item data;
			int count; //number of nodes
			node* left; //pointers left and right
			node* right;
		};
		
		node* root;
		node* get_node(item entry,int count, node* left, node* right);
		
		//Recursive functions
		//Each recursive function has a public helper function
		node* r_copy(node* p);
		void r_print(node* p);
		int r_length(node* p);
		void r_insert(node* &p, item entry);
		void r_remove(node* &p, item target);
		void remove_node(node* &p);
		void r_destroy(node* p);
};

//Returns a pointer to a new node
BST::node* BST::get_node(item entry, int count, node* l, node* r)
{
	node* temp = new node;
	temp->data = entry;
	temp->count = count;
	temp->left = l;
	temp->right = r;
	return temp;
	
}

//overload = operator
//used for copying objects in client  program
void BST::operator =(BST source)
{
	r_destroy(root);
	root = r_copy(source.root);
}

//recursivly copies a node and its children
BST::node* BST::r_copy(node* p)
{
	if(p == NULL)
		return NULL;
	else
		return(get_node(p->data, p->count, r_copy(p->left), r_copy(p->right)));//recursive call
}

//destroys left and right nodes recursively
void BST::r_destroy(node* p)
{
	if(p != NULL)
	{
		r_destroy(p->left);
		r_destroy(p->right);
		delete p;
	}
}


void BST::r_print(node* p)
{
	if(p!=NULL)
	{
		r_print(p->left);
		cout<<p->count<<"      "<<p->data<<endl;
		r_print(p->right);
	}
}

int BST::r_length(node* p)
{
	if(p==NULL)
		return 0;
	else
		return r_length(p->left) + 1 + r_length(p->right);
}

void BST::r_insert(node* &p, item entry)
{
	if(p==NULL)
		p = get_node(entry, 1, NULL, NULL);
	else if( entry < p->data)
		r_insert(p->left, entry);
	else if( entry == p->data)
		p->count += 1;
	else //entry > p->data
		r_insert(p->right, entry);
}

void BST::r_remove(node* &p, item target)
{
	if(p->data == target)
		remove_node(p); //removes node that p points to
	else if(target < p->data)
		r_remove(p->left, target);
	else //target > p->data
		r_remove(p->right, target);
}

void BST::remove_node(node* &p)
{
	node* ptr;
	node* back;
	if(p->left == NULL && p->right == NULL)
	{
		delete p;
		p = NULL;
	}
	else if(p->left == NULL)
	{
		ptr = p;
		p = p->right;
		delete ptr;
	}
	else if(p->right == NULL)
	{
		ptr = p;
		p = p->right;
		delete ptr;
	}
	else
	{
		back = p;
		ptr = p->right;
		while(ptr->left != NULL)
		{
			back = ptr;
			ptr = ptr->left;
		}
		p->data = ptr->data;
		if(back==p)
			remove_node(back->right);
		else
			remove_node(back->left);
	}
}

bool BST::present(item target)
{
	node *p = root;
	while(true)
	{
		if(p==NULL)
			return false;
		else if(target < p->data)
			p = p->left;
		else if(target == p->data)
			return true;
		else // target > p->data
			p = p->right;
	}
}

void readFile(BST& tree)
{
	char ch;
	string fileName;
	string str;
	ifstream myfile;
	
	cin.ignore();
	cout<<"Please give a file you wish to open including file extension. : ";
	cin>>fileName;
	myfile.open(fileName);
	
	while(myfile.fail() && fileName != "quit")
	{
		cout<<"File can not be opened!\nPlease try again or type 'quit': ";
		cin>>fileName;
		myfile.open(fileName);
	}
	cout<<fileName<<endl;
	if(fileName != "quit")
	{
		int i = 0;
		myfile.get(ch);
		while(myfile.good())
		{
			if(isalpha(ch) && i < 8)
			{
				str += ch;
				++i;
			}
			else if(!isalpha(ch))
			{
				if(str > "")
					tree.Insert(str);
				str = "";
				i = 0;
			}
			else //i == 8
			{
				if(str > "")
					tree.Insert(str);
				str = ch;
				i = 0;
			}
			myfile.get(ch);
		}
	}
}

void printMenu()
{
	cout<<"Concordance Menu of Commands"<<endl;
	cout<<"q  quit the concordance program"<<endl;
	cout<<"m  show this menu again"<<endl;
	cout<<"p  print the concordance"<<endl;
	cout<<"f  select a file to open"<<endl;
	cout<<"i  insert a word manually"<<endl;
	cout<<"r  remove a specific word"<<endl;
	cout<<"d  delete the entire concordance"<<endl;
	cout<<"l  shows length of the entire concordance list"<<endl;	
}

int main()
{
	BST tree;
	char choice;
	string str;
	int num1;
	printMenu();
	do
	{
		cin>>choice;
		switch(choice)
		{
			case 'q':
				break;
			case 'f':
				readFile(tree);
				break;
			case 'p':
				cout<<"Count - Word"<<endl;
				cout<<"--------------"<<endl;
				tree.print();
				break;
			case 'i':
				cout<<"Please type a word to insert in lower case: ";
				cin>>str;
				tree.Insert(str);
				break;
			case 'r':
				cout<<"Please give a word to remove (case sensative): ";
				cin>>str;
				if(!tree.isEmpty() && tree.present(str))
					tree.remove(str);
				break;
			case 'l':
				cout<<"The length of the list is: "<<tree.length()<<endl;
				break;
			case 'd':
				tree.destroy();
				break;
			case 'm':
				printMenu();
				break;
		}
	}while(choice != 'q');
	return 0;
}












