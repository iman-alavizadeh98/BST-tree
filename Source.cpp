//Iman Alavizadeh
#include <iostream>
using namespace std;

//tree node
//------------------------------------------
class node
{
public:
	int data;
	node* parent;
	node* leftChild;
	node* rightChild;
	node(void);
};

node::node(void)
{
	data = 0;
	parent = NULL;
	leftChild = NULL;
	rightChild = NULL;
}
//------------------------------------------
//binary search tree
class bst
{
public:
	node* root;

	bst(void);
	void insert(int);
	void display(node*, int);
	node* minimum();
	node* maximum();
	node* search(int);
	void inorder_tree_walk(node*);
	node* successor(node*);
	node* predecessor(node *);
	void transplant(node*, node*);
	void deletion(node *);
};

bst::bst(void)
{
	root = NULL;
}

void bst::insert(int d)
{
	node* newNode = new node();
	newNode->data = d;

	if (root == NULL)
	{
		root = newNode;
	}
	else
	{
		node* tempNode = new node();
		node* backTempNode = new node();
		tempNode = root;

		while (tempNode != NULL)
		{
			backTempNode = tempNode;
			if (tempNode->data <= newNode->data)
			{
				tempNode = tempNode->rightChild;
			}
			else
			{
				tempNode = tempNode->leftChild;
			}
		}

		newNode->parent = backTempNode;
		if (backTempNode->data <= newNode->data)
		{
			backTempNode->rightChild = newNode;
		}
		else
		{
			backTempNode->leftChild = newNode;
		}
	}
}
//display binary search tree
void bst::display(node *Node, int level)
{
	if (root == NULL)
	{
		cout << "Tree is empty." << endl;
	}
	else
	{
		if (Node->rightChild != NULL)
		{
			display(Node->rightChild, level + 1);
		}

		if (Node != root)
		{
			for (int i = 0; i < level + 1; i++)
			{
				cout << "      ";
			}
		}
		else
		{
			cout << "Root->";
		}

		cout << Node->data << endl;

		if (Node->leftChild != NULL)
		{
			display(Node->leftChild, level + 1);
		}
	}

}
//return minimum node
node* bst::minimum()
{
	node* tempNode = new node();
	node* backTempNode = new node();
	backTempNode = tempNode = root;
	while (tempNode != NULL)
	{
		backTempNode = tempNode;
		tempNode = tempNode->leftChild;
	}
	return backTempNode;
}
//return maximum node
node* bst::maximum()
{
	node* tempNode = new node();
	node* backTempNode = new node();
	backTempNode = tempNode = root;
	while (tempNode != NULL)
	{
		backTempNode = tempNode;
		tempNode = tempNode->rightChild;
	}
	return backTempNode;
}
//Search in BST Tree
node* bst::search(int Data)
{
	node* tempNode = new node();
	tempNode = root;
	while (tempNode != NULL)
	{
		if (tempNode->data == Data)
		{
			return tempNode;
		}
		else
		{
			if (tempNode->data <= Data)
			{
				tempNode = tempNode->rightChild;
			}
			else
			{
				tempNode = tempNode->leftChild;
			}
		}
	}
	return NULL;
}
//inoreder tree walk = show all node in sorted mood
void bst::inorder_tree_walk(node* currentNode)
{
	if (root != NULL)
	{
		if (currentNode->leftChild != NULL)
		{
			inorder_tree_walk(currentNode->leftChild);
		}

		cout << currentNode->data << "  ,";

		if (currentNode->rightChild != NULL)
		{
			inorder_tree_walk(currentNode->rightChild);
		}
	}
	else
	{
		cout << "Tree is empty!" << endl;
	}
}
//successor
node* bst::successor(node* currentNode)
{
	node* tempNode = new node();
	node* backTempNode = new node();
	tempNode = currentNode;

	if (tempNode->rightChild != NULL)
	{
		tempNode = tempNode->rightChild;
		while (tempNode != NULL)
		{
			backTempNode = tempNode;
			tempNode = tempNode->leftChild;
		}
		return backTempNode;
	}
	else
	{
		backTempNode = tempNode;
		tempNode = tempNode->parent;
		while (tempNode != NULL && tempNode->rightChild == backTempNode)
		{
			backTempNode = tempNode;
			tempNode = tempNode->parent;
		}
		return tempNode;
	}
}

//predecessor
node* bst::predecessor(node* currentNode)
{
	node* tempNode = new node();
	node* backTempNode = new node();
	tempNode = currentNode;

	if (tempNode->leftChild != NULL)
	{
		tempNode = tempNode->leftChild;
		while (tempNode != NULL)
		{
			backTempNode = tempNode;
			tempNode = tempNode->rightChild;
		}
		return backTempNode;
	}
	else
	{
		backTempNode = tempNode;
		tempNode = tempNode->parent;
		while (tempNode != NULL && tempNode->leftChild == backTempNode)
		{
			backTempNode = tempNode;
			tempNode = tempNode->parent;
		}
		return tempNode;
	}
}
//transplant
void bst::transplant(node* u, node* v)
{
	if (u->parent == NULL)
	{
		root = v;
	}
	else
	{
		if (u == u->parent->leftChild)
		{
			u->parent->leftChild = v;
		}
		else
		{
			u->parent->rightChild = v;
		}
	}
	if (v != NULL)
	{
		v->parent = u->parent;
	}
}
//remove node from tree
void bst::deletion(node *z)
{
	if (z->leftChild == NULL)
	{
		transplant(z, z->rightChild);
	}
	else
	{
		if (z->rightChild == NULL)
		{
			transplant(z, z->leftChild);
		}
		else
		{
			node* succesor = new node();
			succesor = successor(z);
			if (succesor->parent != z)
			{
				transplant(succesor, succesor->rightChild);
				succesor->rightChild = z->rightChild;
				succesor->rightChild->parent = succesor;
			}
			transplant(z, succesor);
			succesor->leftChild = z->leftChild;
			succesor->leftChild->parent = succesor;
		}
	}
	delete z;
}
//------------------------------------------
//menu
void menu()
{
	char ch;
	int inttemp;
	node *temp = new node();
	bst myTree;
	int select;
	do
	{
		system("CLS");
		cout << "0. Exit" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Display" << endl;
		cout << "3. Minimum" << endl;
		cout << "4. Maximum" << endl;
		cout << "5. Search" << endl;
		cout << "6. Inorder walk(sort)" << endl;
		cout << "7. Successor" << endl;
		cout << "8. Predecessor" << endl;
		cout << "9. Delete" << endl;
		cout << endl << "Enter your selection:" << endl;
		cin >> select;
		system("CLS");

		switch (select)
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			do
			{
				int data;
				cout << "Enter Data: ";
				cin >> data;
				myTree.insert(data);
				cout << endl << "Do you want another node?[y/n]" << endl;
				cin >> ch;
			} while (ch != 'n');
			break;
		}
		case 2:
		{
			myTree.display(myTree.root, 0);
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 3:
		{
			temp = myTree.minimum();
			if (temp != NULL)
			{
				cout << "Minimum:" << temp->data << endl;
			}
			else
			{
				cout << "Tree is empty!" << endl;
			}
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 4:
		{
			temp = myTree.maximum();
			if (temp != NULL)
			{
				cout << "Maximum:" << temp->data << endl;
			}
			else
			{
				cout << "Tree is empty!" << endl;
			}
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 5:
		{

			cout << "Enter key of node:";
			cin >> inttemp;
			temp = myTree.search(inttemp);
			if (temp != NULL)
			{
				cout << "Node with key (" << temp->data << ") exist in tree." << endl;
			}
			else
			{
				cout << "It isn't in tree!" << endl;
			}

			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 6:
		{
			cout << "Sorted order:" << endl;
			myTree.inorder_tree_walk(myTree.root);
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 7:
		{
			cout << "Enter key of node , for finding it's successor: ";
			cin >> inttemp;
			temp = myTree.search(inttemp);
			if (temp == NULL)
			{
				cout << "Node with key (" << inttemp << ") isn't in tree." << endl;
			}
			else
			{
				temp = myTree.successor(temp);
				if (temp == NULL)
				{
					cout << "It hasn't successor" << endl;
				}
				else
				{
					cout << "Successor: " << temp->data << endl;
				}
			}
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 8:
		{
			cout << "Enter key of node , for finding it's predecessor: ";
			cin >> inttemp;
			temp = myTree.search(inttemp);
			if (temp == NULL)
			{
				cout << "Node with key (" << inttemp << ") isn't in tree." << endl;
			}
			else
			{
				temp = myTree.predecessor(temp);
				if (temp == NULL)
				{
					cout << "It hasn't predecessor" << endl;
				}
				else
				{
					cout << "Predecessor: " << temp->data << endl;
				}
			}
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		case 9:
		{
			cout << "Enter key(Data) of node that you want delete: ";
			cin >> inttemp;
			temp = myTree.search(inttemp);
			if (temp == NULL)
			{
				cout << "Node with key (" << inttemp << ") isn't in tree." << endl;
			}
			else
			{
				myTree.deletion(temp);
				cout << "Node with key (" << inttemp << ") removed from tree." << endl;
			}
			cout << endl << "Press 0 to continue!" << endl;
			cin >> ch;
			break;
		}
		default:
			break;
		}

	} while (select != 0);
}
//------------------------------------------
int main()
{
	menu();
	return 0;
}