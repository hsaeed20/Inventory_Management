#ifndef BST_H
#define BST_H
#include <string>

using namespace std; //you must apply this when calling strings 
class Node
{
	string name;
	string version;
	float price;
	int quantity;
	int subQuantity; 
	//attributes for Node class
public:
	Node();
	Node(string name); //used primarily for insert function 
	Node(string name, string version, float price, int quantity, int subQuantity); //constructor for node and used for readInfo function

	string getName(); //compares name
	void setName(string name); //sets name

	string getVersion(); //compares version
	void setVersion(string version); //sets version

	float getPrice(); //compares price
	void setPrice(float price); //sets price

	int getQuantity(); //compares quantity
	void setQuantity(int quantity); //sets quantity

	int getsubQuantity(); //used to take out quantities of product 
	void setsubQuantity(int subQuantity); //sets sub qunatity 

	void subtractQuantity(int subQuanity); //used to subtract quantities on the quantity removal function

	Node *left, *right; //points left or right of node
	
	void readInfo(); //reads all the provided information behind the product
};

class BST
{
	Node *root; //pointer that is set to the node at the very top 
public:
	BST();
	~BST();

	void insert(string); //inserts a new node into tree
	void insert_for_read_file(string,string,string,string); //TEST used for inserting read files into the BST

	void remove(string); //used for access in the main.cpp
	void remove_helper(string, Node*); //acts as a function that allows the node to traverse through the tree to find the value it matches with
									//it is several directions on where to reach its destination
	void remove_matching_root(); //removes a node from the search tree if the value happens to match the value of the root
	void remove_match(Node*, Node*, bool); //removes a node from the

	void postorderTraversal(); //orders all the numbers from least to greatest
	void postorderTraversal_helper(Node*);

	void postorderTraversal_exit(); //used to remove whatever quantity values are 0 so that the product can be removed from the file. 
	void postorderTraversal_exit_helper(Node*); 

	string Find_Smallest_Value(); //used for access in the main.cpp for testing purposes to see if it finds the smallest value
	string Find_Smallest_Value_helper(Node*); //used to find the smallest value in the search tree

	void remove_quantities(string, int);

	void read_file(); 
};
#endif