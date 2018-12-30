#include "Project.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std; //you must apply this when calling strings 
BST c; //used to access classes outside of BST globally

BST::BST() {
	root = NULL;
}


BST::~BST() {

}

void BST::insert(string name) {
	Node* n = new Node(name); //0 invokes parameterized (passes values) contstructor
	n->readInfo(); //goes to ask for attributes
	//all attributes will be included in node
	n->getQuantity();
	n->getPrice();
	n->getVersion();
	Node* temp = root; //temp is used to traverse throughout the tree and to act as a pointer for prev to 
//gain access of leaves that contain null pointers on left and right
	Node* prev = NULL; //prev is used to act as a tracker for temp so that once temp hits NULL, 
					//prev can be pointed to where temp was previously to create a new node
	n->left = NULL;
	n->right = NULL;

	if (root == NULL) //if no tree is present
	{
		root = n;
		//cout << "The value " << root->getName() << " has been added" << endl;
	}

	else if (root->getName() == name) //eliminates duplicate node values
	{
		//cout << "The value " << n->getName() << " has already been added." << endl;
	}
	else
	{
		while (temp != NULL) //temp traversing
		{
			prev = temp;
			if (n->getName() > temp->getName()) //if n is greater than temp value
			{
				temp = temp->right; //acts as an acess point for prev to place the n value
			}
			else //if n is less than temp value
			{
				temp = temp->left; //acts as an acess point for prev to place the n value
			}
		}
		if (n->getName() > prev->getName())
		{
			prev->right = n; //the n node will be placed where temp set the right arrow it previously 
			//cout << "The right value " << n->getName() << " has been added" << endl;
		}
		else
		{
			prev->left = n;  //the n node will be placed where temp set the left arrow it previously 
			//cout << "The left value " << n->getName() << " has been added" << endl;
		}
	}
	
	cout << n->getName();
	cout << "\t" << n->getVersion();
	cout << "\t" << n->getQuantity();
	cout << "\t" << n->getPrice();
	cout << "\n\n";
	//product information will be displayed on the prompt after being inputted into the file
}

void BST::insert_for_read_file(string name, string version, string quantity, string price)
{
	Node* n = new Node(name); //0 invokes parameterized (passes values) contstructor

	n->setName(name);
	n->setVersion(version);
	//name and version don't need to be converted as they are strings

	int x = stoi(quantity); //converts string to int for quantity
	n->setQuantity(x); //sets quantity from the file that was read in the beginning 

	float z = atof(price.c_str()); //c_str done since atof takes cstrings
	n->setPrice(z);

	n->getQuantity();
	n->getPrice();
	n->getVersion();
	Node* temp = root; //temp is used to traverse throughout the tree and to act as a pointer for prev to 
//gain access of leaves that contain null pointers on left and right
	Node* prev = NULL; //prev is used to act as a tracker for temp so that once temp hits NULL, 
					//prev can be pointed to where temp was previously to create a new node
	n->left = NULL;
	n->right = NULL;

	if (root == NULL) //if no tree is present
	{
		root = n;
		//cout << "The value " << root->getName() << " has been added" << endl;
	}

	else if (root->getName() == name) //eliminates duplicate node values
	{
		//cout << "The value " << n->getName() << " has already been added." << endl;
	}
	else
	{
		while (temp != NULL) //temp traversing
		{
			prev = temp;
			if (n->getName() > temp->getName()) //if n is greater than temp value
			{
				temp = temp->right; //acts as an acess point for prev to place the n value
			}
			else //if n is less than temp value
			{
				temp = temp->left; //acts as an acess point for prev to place the n value
			}
		}
		if (n->getName() > prev->getName())
		{
			prev->right = n; //the n node will be placed where temp set the right arrow it previously 
			//cout << "The right value " << n->getName() << " has been added" << endl;
		}
		else
		{
			prev->left = n;  //the n node will be placed where temp set the left arrow it previously 
			//cout << "The left value " << n->getName() << " has been added" << endl;
		}
	}
}


void BST::remove(string name)
{
	remove_helper(name, root);
}

void BST::remove_helper(string name, Node* curr)
{
	if (root == NULL)
	{
		//cout << "Tree is empty" << endl;
		cout << "No Products are present." << endl;
	}

	else
	{
		if (root->getName() == name)
		{
			remove_matching_root(); //goes to function where the value that wants to be deleted matches the value of the root
		}

		else
		{
			if (name < curr->getName() && curr->left != NULL) //if value is less than the current pointers value 
															  //and if the current left pointer is not NULL
			{
				curr->left->getName() == name ? //if the left of current pointer is less than the value
					remove_match(curr, curr->left, true) : //will go to remove matching function if the current pointer info is the same as value
					remove_helper(name, curr->left); //current pointer will recursively traverse again until it finds the value
			}

			else if (name > curr->getName() && curr->right != NULL) //if value is greater than the current pointers value
																	//and if the current right pointer is not NULL
			{
				curr->right->getName() == name ? //if the right of current pointer is less than the value
					remove_match(curr, curr->right, false) : //will go to remove matching function if the current pointer info is the same as value
					remove_helper(name, curr->right); //current pointer will recursively traverse again until it finds the value
			}

			else
			{
				cout << "The product " << curr->getName() << " was not located" << endl;
			}
		}
	}
}

void BST::remove_matching_root()
{
	if (root == NULL)
	{
		//cout << "Cannot remove root. The tree is empty" << endl;
		cout << "No Products are present" << endl;
	}

	else
	{
		Node* delPtr = root;
		string rootValue = root->getName(); //CHECK THIS
		string smallestInRightSubtree; //used to find smallest value in right subtree
								   //to obtain new value for root after removal

		//if there is no children
		if (root->left == NULL && root->right == NULL)
		{
			root = NULL; //done to place root at null before deletion
			delete delPtr; //deletes node on the root
		}

		//if there is one child
		else if (root->left == NULL && root->right != NULL) //if root is pointing right
		{
			root = root->right; //disconnects old root value from tree
			delPtr->right = NULL; //not necessary but good to understand for the sake of logic
			delete delPtr;
			//cout << "Root node value " << rootValue << " was deleted." << endl;
			//cout << "New root is " << root->getName() << endl;
			postorderTraversal(); //Updates results
		}

		else if (root->left != NULL && root->right == NULL) //if root is pointing left
		{
			root = root->left; //disconnects old root value from tree
			delPtr->left = NULL; //not necessary but good to understand for the sake of logic
			delete delPtr;
			//cout << "Root node value " << rootValue << " was deleted" << endl;
			//cout << "New root is " << root->getName() << endl;
			postorderTraversal();//Updates results
		}

		//if there are two children
		else
		{
			smallestInRightSubtree = Find_Smallest_Value_helper(root->right);
			//recursively goes to find smallest value in the right subtree
			remove_helper(smallestInRightSubtree, root); //deletes smallest node in right subtree
			root->setName(smallestInRightSubtree); //setInfo is implemented because it acts a mutator which thus, allows the root to be overwritten from the smallest node in the right subtree
			//root->getInfo() == smallestInRightSubtree; //overwrites old node with value of new small node
			//cout << "The root value containing " << rootValue <<
				//" was replaced with the value " << root->getName() << endl;
			postorderTraversal(); //Updates results
		}
	}
}

void BST::remove_match(Node* curr, Node* match, bool left)
{
	if (root == NULL)
	{
		//cout << "Cannot remove matching node. The tree is empty" << endl;
		cout << "No Products are present" << endl;
	}

	else
	{
		Node* delPtr;
		string matchValue = match->getName(); //equal to value of root
		string smallestRightSubtree; //used to find smallest value in right subtree

		//if there are no children
		if (match->left == NULL && match->right == NULL)
		{
			delPtr = match;
			left == true ? curr->left = NULL : curr->right = NULL;
			//question mark represents if case is true and colon represents otherwise
			//done to replace value of old node with a new one if its on left or right
			delete delPtr;
			//cout << "The node value containing " << matchValue <<
				//" has been removed" << endl;
			postorderTraversal(); //Updates results
		}

		//if there is one child
		else if (match->left == NULL && match->right != NULL) //if theres a right child but not left
		{
			left == true ? curr->left = match->right : curr->right = match->right;
			//done to check if we are dealing with a left child. 
			match->right = NULL; //disconnects matching node from tree
			delPtr = match;
			delete delPtr; //not necessary but makes sense logically
			//cout << "The node value containing " << matchValue <<
				//" has been removed" << endl;
			postorderTraversal(); //Updates results
		}

		else if (match->left != NULL && match->right == NULL) //if theres a left child but not right
		{
			left == true ? curr->left = match->left : curr->right = match->left;
			//done to check if we are dealing with a right child
			match->left = NULL; //disconnects matching node from tree
			delPtr = match;
			delete delPtr; //not necessary but makes sense logically
			//cout << "The node value containing " << matchValue <<
				//" has been removed" << endl;
			postorderTraversal(); //Updates results
		}

		//if there are two children
		else
		{
			smallestRightSubtree = Find_Smallest_Value_helper(match->right);
			//recursively goes to find smallest value in the right subtree
			remove_helper(smallestRightSubtree, match); //deletes smallest node in right subtree
			match->getName() == smallestRightSubtree; //overwrites old node with value of new small node
		}
	}
}

string BST::Find_Smallest_Value()
{
	return Find_Smallest_Value_helper(root);
}

string BST::Find_Smallest_Value_helper(Node* curr)
{

	if (root == NULL)
	{
		//cout << "The tree is empty" << endl;
		cout << "No Products are present" << endl;
		return NULL; //returns value that cannot be implemented in the tree
	}

	else
	{
		if (curr->left != NULL) //no need to go right since we are looking for the
								//minimum value on the left side of tree
		{
			return Find_Smallest_Value_helper(curr->left); //recursively goes left
		}

		else //when smallest value is found
		{
			return curr->getName();
		}
	}
}

void BST::remove_quantities(string name, int subQuantity) {
	Node* temp = root; //temp is used to traverse throughout the tree
	if (root == NULL)
	{
		//cout << "The tree is empty" << endl;
		cout << "No Products are present" << endl;
	}

	else if (root->getName() == name) { //if the value is equal to the info of the root
		//cout << "The name " << root->getName() << " is located at the root" << endl;

		if (temp->getQuantity() == 0) //if there are zero quantities of the product
		{
			cout << temp->getName() << " is currently out of stock." << endl; 
		}
		else
		{
			temp->subtractQuantity(subQuantity);
			
			cout << "Here are the updated results: " << endl;
			cout << temp->getName();
			cout << "\t" << temp->getVersion();
			cout << "\t" << temp->getQuantity();
			cout << "\t" << temp->getPrice();
			cout << "\n";
			//displays updated information after removing quantites

			postorderTraversal(); //updates results

		}
	}
	else
	{
		if (name < root->getName()) { //if value is less than the root node value
			temp = temp->left;
		}


		else //if value is greater than the root node value
			temp = temp->right;

		while (temp != NULL && temp->getName() != name) //iterates throughout the tree until temp has located all nodes
		{
			if (name < temp->getName())  //if value is less than the temp node value
			{
				temp = temp->left;
			}

			//if value is greater than the temp node value
			else
			{
				temp = temp->right;
			}

		}
		if (temp != NULL && temp->getName() == name)
		{

			if (temp->getQuantity() == 0)
			{
				cout << temp->getName() << " is currently out of stock." << endl; 
			}
			else
			{
				temp->subtractQuantity(subQuantity);

				cout << "Here are the updated results: " << endl;
				cout << temp->getName();
				cout << "\t" << temp->getVersion();
				cout << "\t" << temp->getQuantity();
				cout << "\t" << temp->getPrice();
				cout << "\n";

				postorderTraversal(); //updates results 
			}
		}
		else
		{
			cout << "The product " << name << " has NOT been located\n" << endl;
		}
	}
}

void Node::subtractQuantity(int subQuantity)
{
	this->quantity -= subQuantity;
}


void BST::postorderTraversal()
{
	ofstream fout;
	fout.open("software.txt", std::ios_base::trunc); //removes all the information in the file 
	fout.close();
	postorderTraversal_helper(root); //used as intial pointer value
}

void BST::postorderTraversal_helper(Node* node)
{
	ofstream fout; 

	fout.open("software.txt", std::ios_base::app); //updates the information in the file including all the information from the BST
	if (node == NULL)
	{
		return;
	}

	else
	{
		postorderTraversal_helper(node->left);

		postorderTraversal_helper(node->right);

		fout << node->getName();
		fout << "\t" << node->getVersion();
		fout << "\t" << node->getQuantity();
		fout << "\t" << node->getPrice();
		fout << "\n";
	}
	fout.close();
}


void BST::postorderTraversal_exit()
{
	ofstream fout;
	fout.open("software.txt", std::ios_base::trunc);
	fout.close();
	postorderTraversal_exit_helper(root); //used as intial pointer value
}

void BST::postorderTraversal_exit_helper(Node* node)
{
	ofstream fout;

	fout.open("software.txt", std::ios_base::app);
	if (node == NULL)
	{
		return;
	}

	else
	{
		postorderTraversal_exit_helper(node->left);

		postorderTraversal_exit_helper(node->right);

		if (node->getQuantity() == 0) //if there are zero quantites, that product will be removed from the file and the tree
		{
			cout << "The product " << node->getName() << " has successfully been removed from the system\n" << endl; 
			string x = node->getName(); //created as a string so that it will be able to traverse through the tree
			remove(x);
		}
		else
		{
			postorderTraversal(); //used to overwrite information so it avoids being lost after exiting the program
		}
	}
	fout.close();
}


void BST::read_file()
{
	string line;
	ifstream myfile("software.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line)) //reads everything line by line in a general sense of reading a file (nothing BST related)
		{
			cout << line << '\n';
		}
		myfile.close();
	}

	else
		cout << "Unable to open file";
}


void Node::readInfo() //allows user to input information concerning their product
{
	cout << "Version: ";
	getline(cin, version);
	cout << "\n";

	cout << "Quantity: ";
	cin >> quantity;
	cout << "\n";

	cout << "Price: ";
	cin >> price;
	cout << "\n";
}

Node::Node() //constructor for Node
{
	name = "";
	version = "";
	price = 0.0;
	quantity = 0;

}

Node::Node(string name)  //node containing attribute for name
{
	this->name = name;
}

Node::Node(string name, string version, float price, int quantity, int subQuantity)  //node containing attributes
{
	this->name = name;
	this->version = version;
	this->quantity = quantity;
	this->price = price;
	this->subQuantity = subQuantity;
	
}

string Node::getName() {
	return name;
}

void Node::setName(string name) {
	this->name = name;
}

string Node::getVersion() {
	return version;
}

void Node::setVersion(string version) {
	this->version = version;
}

float Node::getPrice() {
	return price;
}

void Node::setPrice(float price) {
	this->price = price;
}


int Node::getQuantity() {
	return quantity;
}

void Node::setQuantity(int quantity) {
	this->quantity = quantity;
}

int Node::getsubQuantity() { 
	return subQuantity;
}

void Node::setsubQuantity(int subQuantity) { 
	this->subQuantity = subQuantity;
}