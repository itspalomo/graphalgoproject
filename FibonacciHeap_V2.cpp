#include <iostream>
#include <cmath>

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

    bool mark;      // boolean for marked
};

class FibHeap{
private:
    Node *H;        // points to min
    int s;          // tracks size

public:

    FibHeap(){              // Default Constructor
        s = 0;              // initialize size to 0
        H = Make_Heap();    // Not thoroughly tested
    }

    Node *Make_Heap(){ // This make_heap not initialize H properly
        Node *np;
        np = NULL;

        return np;
    }

    Node *Create_Node(int value){ // can likely incorporate into Insert
        Node *x = new Node;
        x->key = value;

        return x;
    }

    void Insert(Node *H, Node* x){

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

        s = s + 1;  // Increment size
    }

    Node *Union(Node* H1, Node* H2){
        // Untested - Followed Textbook pseudo-code

        Node *H = Make_Heap();
        H = H1;

        if( (H1 == NULL) || ( (H2 != NULL) && (H2->key < H1->key) ) ){
            H = H2;
        }

        H->key = H1->key + H2->key;
        return H;
    }

    void Link(Node* H, Node* x, Node* y){
        // WIP
    }

    void Consolidate(){
        // WIP
        float lg = ( (log(s)) / (log(2)) );
        int D = lg;

        Node *A[D];

    }

    void ExtractMin(){
        // Untested - Requires working Consolidate
        Node *z = H;

        if (z != NULL){

            Node* temp;
            Node* x = NULL;

            if (z->c != NULL){
                x = z->c;
                do {
                    temp = x->right;
                    (H->left)->right = x;
                    x->right = H;
                    x->left = H->left;
                    H->left = x;

                    if (x->key < H->key){
                        H = x;
                    }

                    x->p = NULL;
                    x = temp;

                } while (temp != z->c);
            }

            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;

            H = temp->right;
            if (temp == temp->right && temp->c == NULL){
                H = NULL;
            } else {
                H = temp->right;
                Consolidate();
            }
            s--; // decrement size
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
    FH.Insert(H, x);
    x = FH.Create_Node(27);
    FH.Insert(H, x);

    FH.Display(x);

    cout << endl << "----Fully Executes----" << endl;

    return 0;
}
