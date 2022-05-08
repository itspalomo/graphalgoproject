#include <iostream>

using namespace std;

struct Node{
    int key, d;       // data and d
    Node* parent;        // parent pointer
    Node* child;        // child pointer
    Node* left;     // left pointer
    Node* right;    // right pointer

    char mark;      // Black or white mark of the Node
    char c;         // Find Node assist flag
};

class FibHeap{
private:
    Node *H;        // Heap used throughout
    int s;          // tracks size

public:

    FibHeap() {
       H = (struct Node*)malloc(sizeof(struct Node));
       H->key = 0;
       H->d = 0;
       H->mark = 'W';
       H->c = 'N';
       H->parent = NULL;
       H->child = NULL;
       H->left = H;
       H->right = H;
       s = 0;
    }
    ~FibHeap() {

    }

    Node *Make_Heap(){
        struct Node* new_Node = (struct Node*)malloc(sizeof(struct Node));
        new_Node->key = 0;
        new_Node->d = 0;
        new_Node->mark = 'W';
        new_Node->c = 'N';
        new_Node->parent = NULL;
        new_Node->child = NULL;
        new_Node->left = new_Node;
        new_Node->right = new_Node;

        return new_Node;
    }

    Node *Create_Node(int value){ // can likely incorporate into Insert
        Node *x = new Node;
        x->key = value;

        return x;
    }

    Node* Insert(Node* x){
        x->d = 0;            // initial d is 0
        x->parent = NULL;         // initial parent is NIL
        x->child = NULL;         // initial child is NIL
        x->left = x;         // Left and Right children
        x->right = x;        //   point to itself (circular DLL)
        x->mark = 'W';     // initial mark is false
        x->c = 'N';

        if (H == NULL){
            H = x;          // if H is empty, x becomes root Node
        } else {
            // place in root list: Circular DLL
            (H->left)->right = x;
            x->right = H;
            x->left = H->left;
            H->left = x;

            if (x->key < H->key){ // If x value is less than H value
                H = x;            // x becomes new root Node
            }
        } // */

        s++;

        return H;
    }

    void Link(struct Node* H2, struct Node* H1)
    {

        (H2->left)->right = H2->right;
        (H2->right)->left = H2->left;

        if (H1->right == H1)
            H = H1;

        H2->left = H2;
        H2->right = H2;
        H2->parent = H1;

        if (H1->child == NULL)
            H1->child = H2;

        H2->right = H1->child;
        H2->left = (H1->child)->left;
        ((H1->child)->left)->right = H2;
        (H1->child)->left = H2;

        if (H2->key < (H1->child)->key)
            H1->child = H2;

        H1->d++;
    }

    void Cut(Node* x, Node* y)
    {
        if (x == x->right)
            y->child = NULL;

        (x->left)->right = x->right;
        (x->right)->left = x->left;

        if (x == y->child)
            y->child = x->right;

        y->d--;
        x->right = x;
        x->left = x;
        (H->left)->right = x;
        x->right = H;
        x->left = H->left;
        H->left = x;
        x->parent = NULL;
        x->mark = 'B';
    }

    void CascadeCut(Node* y)
    {

        Node* z = y->parent;
        if (z!= NULL)
        {
            if (y->mark == 0)
            {
                y->mark = 1;
            }
            else
            {
                Cut(y, z);
                CascadeCut(z);
            }
        }
    }

    void DecreaseKey(Node* x, int k)
    {
        if (H == NULL){
            cout << "The Heap is Empty" << endl;
            return;
        }

        if (x == NULL){
            cout << "Node not found in the Heap" << endl;
            return;
        }
        if (x->key < k){
            cout << "Entered key greater than current key" << endl;
            return;
        }
        
        Node* y = x->parent;
        x->key = k;
        
        if (y != NULL && x->key < y->key){
            Cut(x, y);
            CascadeCut(y);
        }
        if (x->key < H->key)
            H = x;
        return;
    }
    
    void Consolidate() {
        // WIP
        float lg = ((log(s)) / (log(2)));
        int D = lg;
    }

    void ExtractMin() {
        // Untested - Requires working Consolidate

        Node* z = H;
        if (z != NULL) {

            Node* temp;
            Node* x = NULL;

            if (z->c != NULL) {
                x = z->child;
                do {
                    temp = x->right;
                    (H->left)->right = x;
                    x->right = H;
                    x->left = H->left;
                    H->left = x;

                    if (x->key < H->key) {
                        H = x;
                    }

                    x->parent = NULL;
                    x = temp;

                } while (temp != z->child);
            }

            (temp->left)->right = temp->right;
            (temp->right)->left = temp->left;

            H = temp->right;
            if (temp == temp->right && temp->c == NULL) {
                H = NULL;
            }
            else {
                H = temp->right;
                Consolidate();
            }
            s--; // decrement size
        }
    }

    void Display(){
        Node *p = H;
        int tempSize = s;

        cout << "Current size: " << tempSize << endl;

        cout << "Roots: ";

        while (tempSize > 0){
            cout << p->key << " ";
            p = p->right;
        }
        cout << endl;

    }

};

int main()
{
    FibHeap FH;

    Node *x;
    x = FH.Create_Node(14);
    x = FH.Insert(x);
   // x = FH.Create_Node(27);
   // x = FH.Insert(H, x);

    FH.Display();

    cout << "----Fully Builds----" << endl;

    return 0;
}
