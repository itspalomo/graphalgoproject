#ifndef fibheap_h
#define fibheap_h

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <malloc.h>
using namespace std;

// Creating a structure to represent a node in the heap
template<typename type>
class FibHeap{
protected:
    struct node {
        node* parent; // Parent pointer
        node* child; // Child pointer
        node* left; // Pointer to the node on the left
        node* right; // Pointer to the node on the right
        type key; // Value of the node
        int degree; // Degree of the node
        char mark; // Black or white mark of the node
        char c; // Flag for assisting in the Find node function
    };

public:
    FibHeap() : mini(NULL), no_of_nodes(0) {}
	~FibHeap() {while(!empty()) Extract_min();}

    void insert(type val);
    void Fibonnaci_link(struct node* ptr2, struct node* ptr1);
    void Consolidate();
    type Extract_min();
    void Cut(struct node* found, struct node* temp);
    void Cascase_cut(struct node* temp);
    void Decrease_key(struct node* found, type val);
    void Find(struct node* mini, type old_val, type val);
    void Deletion(type val);
    void display();
    node* min_node() {return this->mini;}
    type min() {return this->mini->key; Extract_min();}

    bool empty() {return no_of_nodes == 0;}
	int size() {return no_of_nodes;}
	void dec() {no_of_nodes--;}

private:
    node* mini;                     // Creating min pointer as "mini"
    int no_of_nodes;                // Declare an integer for number of nodes in the heap
};



// Function to insert a node in heap
template<typename type>
void FibHeap<type>::insert(type val)
{
	struct node* new_node = new node();
	new_node->key = val;
	new_node->degree = 0;
	new_node->mark = 'W';
	new_node->c = 'N';
	new_node->parent = NULL;
	new_node->child = NULL;
	new_node->left = new_node;
	new_node->right = new_node;
	if (mini != NULL) {
		(mini->left)->right = new_node;
		new_node->right = mini;
		new_node->left = mini->left;
		mini->left = new_node;
		if (new_node->key < mini->key)
			mini = new_node;
	}
	else {
		mini = new_node;
	}
	no_of_nodes++;
}
// Linking the heap nodes in parent child relationship
template<typename type>
void FibHeap<type>::Fibonnaci_link(struct node* ptr2, struct node* ptr1)
{
	(ptr2->left)->right = ptr2->right;
	(ptr2->right)->left = ptr2->left;
	if (ptr1->right == ptr1)
		mini = ptr1;
	ptr2->left = ptr2;
	ptr2->right = ptr2;
	ptr2->parent = ptr1;
	if (ptr1->child == NULL)
		ptr1->child = ptr2;
	ptr2->right = ptr1->child;
	ptr2->left = (ptr1->child)->left;
	((ptr1->child)->left)->right = ptr2;
	(ptr1->child)->left = ptr2;
	if (ptr2->key < (ptr1->child)->key)
		ptr1->child = ptr2;
	ptr1->degree++;
}
// Consolidating the heap
template<typename type>
void FibHeap<type>::Consolidate()
{
	int temp1;
	float temp2 = (log(no_of_nodes)) / (log(2));
	int temp3 = temp2;
	struct node* arr[temp3+1];
	for (int i = 0; i <= temp3; i++)
		arr[i] = NULL;
	node* ptr1 = mini;
	node* ptr2;
	node* ptr3;
	node* ptr4 = ptr1;
	do {
		ptr4 = ptr4->right;
		temp1 = ptr1->degree;
		while (arr[temp1] != NULL) {
			ptr2 = arr[temp1];
			if (ptr1->key > ptr2->key) {
				ptr3 = ptr1;
				ptr1 = ptr2;
				ptr2 = ptr3;
			}
			if (ptr2 == mini)
				mini = ptr1;
			Fibonnaci_link(ptr2, ptr1);
			if (ptr1->right == ptr1)
				mini = ptr1;
			arr[temp1] = NULL;
			temp1++;
		}
		arr[temp1] = ptr1;
		ptr1 = ptr1->right;
	} while (ptr1 != mini);
	mini = NULL;
	for (int j = 0; j <= temp3; j++) {
		if (arr[j] != NULL) {
			arr[j]->left = arr[j];
			arr[j]->right = arr[j];
			if (mini != NULL) {
				(mini->left)->right = arr[j];
				arr[j]->right = mini;
				arr[j]->left = mini->left;
				mini->left = arr[j];
				if (arr[j]->key < mini->key)
					mini = arr[j];
			}
			else {
				mini = arr[j];
			}
			if (mini == NULL)
				mini = arr[j];
			else if (arr[j]->key < mini->key)
				mini = arr[j];
		}
	}
}

// Function to extract minimum node in the heap
template<typename type>
type FibHeap<type>::Extract_min()
{
	if (mini == NULL)
        printf("The heap is empty\n");
	else {
		node* temp = mini;
		node* pntr;
		type min_key;
		pntr = temp;
		node* x = NULL;
		if (temp->child != NULL) {

			x = temp->child;
			do {
				pntr = x->right;
				(mini->left)->right = x;
				x->right = mini;
				x->left = mini->left;
				mini->left = x;
				if (x->key < mini->key)
					mini = x;
				x->parent = NULL;
				x = pntr;
			} while (pntr != temp->child);
		}
		(temp->left)->right = temp->right;
		(temp->right)->left = temp->left;
		mini = temp->right;
		if (temp == temp->right && temp->child == NULL)
			mini = NULL;
		else {
			mini = temp->right;
			Consolidate();
		}
		no_of_nodes--;
		return min_key;
	}
	return 0;
}

// Cutting a node in the heap to be placed in the root list
template<typename type>
void FibHeap<type>::Cut(struct node* found, struct node* temp)
{
	if (found == found->right)
		temp->child = NULL;

	(found->left)->right = found->right;
	(found->right)->left = found->left;
	if (found == temp->child)
		temp->child = found->right;

	temp->degree = temp->degree - 1;
	found->right = found;
	found->left = found;
	(mini->left)->right = found;
	found->right = mini;
	found->left = mini->left;
	mini->left = found;
	found->parent = NULL;
	found->mark = 'B';
}

// Recursive cascade cutting function
template<typename type>
void FibHeap<type>::Cascase_cut(struct node* temp)
{
	node* ptr5 = temp->parent;
	if (ptr5 != NULL) {
		if (temp->mark == 'W') {
			temp->mark = 'B';
		}
		else {
			Cut(temp, ptr5);
			Cascase_cut(ptr5);
		}
	}
}

// Function to decrease the value of a node in the heap
template<typename type>
void FibHeap<type>::Decrease_key(struct node* found, type val)
{
	if (mini == NULL)
        printf("The Heap is Empty\n");

	if (found == NULL)
        printf("Node not found in the Heap\n");

	found->key = val;

	struct node* temp = found->parent;
	if (temp != NULL && found->key < temp->key) {
		Cut(found, temp);
		Cascase_cut(temp);
	}
	if (found->key < mini->key)
		mini = found;
}

// Function to find the given node
template<typename type>
void FibHeap<type>::Find(struct node* mini, type old_val, type val)
{
	struct node* found = NULL;
	node* temp5 = mini;
	temp5->c = 'Y';
	node* found_ptr = NULL;
	if (temp5->key == old_val) {
		found_ptr = temp5;
		temp5->c = 'N';
		found = found_ptr;
		Decrease_key(found, val);
	}
	if (found_ptr == NULL) {
		if (temp5->child != NULL)
			Find(temp5->child, old_val, val);
		if ((temp5->right)->c != 'Y')
			Find(temp5->right, old_val, val);
	}
	temp5->c = 'N';
	found = found_ptr;
}

// Deleting a node from the heap
template<typename type>
void FibHeap<type>::Deletion(type val)
{
	if (mini == NULL)
        printf("The heap is empty\n");
	else {

		// Decreasing the value of the node to 0
		Find(mini, val, 0);

		// Calling Extract_min function to
		// delete minimum value node, which is 0
		Extract_min();
	}
}

// Function to display the heap
template<typename type>
void FibHeap<type>::display()
{
	node* ptr = mini;
	if (ptr == NULL)
		printf("The Heap is Empty\n");

	else {
		cout << "The root nodes of Heap are: " << endl;
		do {
			cout << ptr->key;
			ptr = ptr->right;
			if (ptr != mini) {
				cout << "-->";
			}
		} while (ptr != mini && ptr->right != NULL);
		cout << endl
			<< "The heap has " << no_of_nodes << " nodes" << endl
			<< endl;
	}
}

#endif
