#include <iostream>

using namespace std;

/*
    Fibonacci Heap (not complete)
    Required functions for Dijkstra's SP include;
        Insert, ExtractMin, and DecreaseKey
    ExtractMin requires the Consolidate function
    DecreaseKey requires the Cut and Cascading-Cut functions

*/

struct Node{
    int key, d;       // data and degree
    Node* p;        // parent pointer
    Node* c;        // child pointer
    Node* left;     // left pointer
    Node* right;    // right pointer

    int min; // in pseudo code, but not used thus far

    bool mark;      //
};

class FibHeap{
private:
    Node *H;        // Heap used throughout
    int s;          // tracks size

public:

    Node *Make_Heap(){
        Node *np;
        np = NULL;
        //np->key = 0;
        s = 0;

        return np;
    }

    Node *Create_Node(int value){ // can likely incorporate into Insert
        Node *x = new Node;
        x->key = value;

        return x;
    }

    Node *Insert(Node *H, Node* x){
        x->d = 0;            // initial degree is 0
        x->p = NULL;         // initial parent is NIL
        x->c = NULL;         // initial child is NIL
        x->left = x;         // Left and Right children
        x->right = x;        //   point to itself (circular DLL)
        x->mark = false;     // initial mark is false

        // /*
        if (H != NULL){
            // place in root list: Circular DLL
            (H->left)->right = x;
            x->right = H;
            x->left = H->left;
            H->left = x;

            if (x->key < H->key){ // If x value is less than H value
                H = x;            // x becomes new root node
            }
        } else {
            H = x;
        } // */

        /*
        if (H == NULL){
            H = x;          // if H is empty, x becomes root node
        } else {
            // place in root list: Circular DLL
            (H->left)->right = x;
            x->right = H;
            x->left = H->left;
            H->left = x;

            if (x->key < H->key){ // If x value is less than H value
                H = x;            // x becomes new root node
            }
        } // */

        s = s + 1;
        return H;
    }

    Node *Union(Node* H1, Node* H2){
        Node *H = Make_Heap();
        H = H1;

        if( (H1 == NULL) || ( (H2 != NULL) && (H2->key < H1->key) ) ){
            H = H2;
        }

        H->key = H1->key + H2->key;
        return H;
    }

    int Consolidate(Node* H1){
        // WIP
    }

    Node *ExtractMin(Node *H){
        Node *z = H;
        if (z != NULL){
            // WIP

        }
    }




    void Display(Node *H){
        Node *p = H;
        int tempSize = s;

        cout << "Current size: " << tempSize << endl;

        cout << "Top value is: " << p->key << endl;
        cout << "Left node is  " << p->left->key << endl;

        cout << "Roots: ";

        while (tempSize > 0){
            cout << p->key << " ";
            p = p->right;
            tempSize--;
        }
        cout << endl;

    }

};

int main()
{
    FibHeap FH;

    Node *x;
    Node *H;

    H = FH.Make_Heap();

    x = FH.Create_Node(14);
    x = FH.Insert(H, x);
    x = FH.Create_Node(27);
    x = FH.Insert(H, x);

    FH.Display(x);

    cout << endl << "----Fully Executes----" << endl;

    return 0;
}
