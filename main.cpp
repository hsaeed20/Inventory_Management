#include <iostream>
#include <cstdlib>
#include "Project.h"
#include <fstream>

using namespace std;
int main() {
	BST Haroon;
	Node info;

	int choice;
	string identity;
	int quantity;


	string line;
	string name;
	string version;
	string quantities; 
	string price; 
	ifstream myfile("software.txt");
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			name = "";
			version = "";
			quantities = "";
			price = "";
			int i;
			if (line.length() > 0) 
			{
				for (i=0; line[i] != '\t'; i++) { //for the use of making an inivdual variable for name
					name += line[i];
				}

				for (i+=1; line[i] != '\t'; i++) { //for the use of making an inivdual variable for version
					version += line[i];
				}

				for (i+=1; line[i] != '\t'; i++) { //for the use of making an inivdual variable for quantity
					quantities += line[i];
				}

				for (i+=1; i < line.length(); i++) { //for the use of making an inivdual variable for price 
					price += line[i];
				}

				cout << name << "\t";
				cout << version << "\t";
				cout << quantities << "\t";
				cout << price << "\t";
				cout << "\n";
				//displays the contents of the file if there is information that has already been inputted
				Haroon.insert_for_read_file(name, version, quantities, price);
			}
			
			
		}
		myfile.close();
	}

	else
		cout << "Unable to open file"; //if there is no file named that software.txt 


	cout << "Welcome to your Inventory Management System!\n\n" << endl;

	do
	{
		cout << "1. Add A New Product " << "\n\n" << "2. Quantity Removal " << "\n\n" <<
			 "3. Read Contents " << "\n\n" << "4. Exit\n " << endl;

		cout << "Please select an option (1-4): " << endl;
		cin >> choice;
		cin.ignore(); //used to prevent newline from skipping the naming of a product

		switch (choice)
		{
		case 1:
			cout << "Product Details" << endl;
			cout << "\n";

			cout << "Name: ";
			getline(cin, identity); //gets the name of the product. used getline to get the name of the whole product if there is two words
			cout << "\n";
			Haroon.insert(identity); //goes through insert function along with getting the attributes of the product
			Haroon.postorderTraversal(); //all file I/O is in Project.cpp of this function
			cout << "Inventory Management has been updated!\n" << endl;
			break;

		case 2:
			cout << "What product would you like to select: ";
			getline(cin, identity); 
			cout << "\n";
			cout << "How many quantites would you like to take: ";
			cin >> quantity;
			cout << "\n";
			Haroon.remove_quantities(identity, quantity); //goes to remove quantites function and updates the inventory
			cout << "Inventory Management has been updated!\n" << endl;
			break;

		case 3:
			Haroon.read_file(); //reads the contents of the file
			break;

		case 4:
			Haroon.postorderTraversal_exit(); //a special postorder Traversal that deletes an item that has 0 quantites
			cout << "You have successfully exited the management system.\nHave a great day!" << endl;
			break;
		}
	} while (choice != 4);
	
	system("pause");

}