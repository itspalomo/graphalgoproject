#ifndef pqueue_h
#define pqueue_h

//////////////////////////-- PQueue Class Interface --////////////////////////

template <typename type>
class PQueue{
protected:
    void heapify(int i);                        // MinHeapify node at i
    void buildHeap();                           // from last non-leaf node to root, heapify
   
    void print() {                              //** print function used to debug
        for (int i = 0; i < size; i++)
            printf("%i\n", array[i]);
    }

public:
    PQueue(int size);                           // constructor to take size of array
    ~PQueue();                                  // destructor to remove allocated memory

    void push(type t);                          // insert item 't' to queue
    type& pop();                                // remove item with highest priority from queue (min)
    void modify(type i, int val);

    bool empty() {return size==0;}

private:
    int size;
    int max_size;
    type *array;
};


//////////////////////////-- Constructor/Destructor Definitions --////////////////////////

template <typename type>
PQueue<type>::PQueue(int size) {
    this->size = 0;                             // initialize current queue size to 0
    max_size = size;                            // keep track of max queue size (in case needed)
    array = new type[size];                     // allocate memory for queue array
}
template <typename type>
PQueue<type>::~PQueue() {                       
    delete[] array;                             // deallocate (delete) queue array once done
}


//////////////////////////-- PQueue Member Function Definitions --////////////////////////

template<typename type>
void PQueue<type>::push(type t) {
    array[size++] = t;                          // insert at end of heap/queue array

    buildHeap();                                // rebuild heap
}
template<typename type>
type& PQueue<type>::pop() {
    if (size==0) {                              // if empty
        printf("Empty Queue!\n");               //  cannot pop from queue, exit with code 0
        exit(0);    
    }
    
    if (size==1)
        return array[--size];                   // only single element, then decrement size and pop

    type temp = array[--size];                  // otherwise
    array[size] = array[0];                     //  swap(array[0], array[size-1])
    array[0] = temp;

    buildHeap();                                //  then rebuild heap with queue array.size-1
    
    return array[size];
}


//////////////////////////-- PQueue/Heap Member Function Definitions --////////////////////////

template<typename type>
void PQueue<type>::heapify(int i){
    int smallest = i;                                   // set smallest index to be i
    int left_child = (i*2)+1;                           // left child index of i
    int right_child = (i*2)+2;                          // right child index of i

    if (left_child < size && array[left_child]<array[i])
        smallest = left_child;                          // get update smallest index if true
                                                        //  do for both left and right child
    if (right_child < size && array[right_child]<array[smallest])
        smallest = right_child;

    if (smallest != i) {                                // recursively heapify to keep MinHeap property
        type temp = array[i];                           // swap
        array[i] = array[smallest];
        array[smallest] = temp;

        heapify(smallest);
    }
}
template<typename type>
void PQueue<type>::buildHeap() {
    int last_non_leaf = (size/2)-1;                     // get last node index that is not a leaf
    for (int i = last_non_leaf; i >= 0; i--)            // iterate and keep MinHeap property
        heapify(i);
}
template<typename type>
void PQueue<type>::modify(type t, int val) {
    for (int i = 0; i < size; i++)
        if (array[i] == t && array[i] > t) {
            array[i] = t;
            return;
        }
}


#endif