#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// TODO:
// 1. erase(int)
// 2. sortedInsert(int)
// 3. test large datasets, corner/edge cases
// 4. add minSorted and maxSorted bool values to Heap private

class Heap {
    private:
        vector<int> data;       // the heap uses a vector for storage
        int maxValue;
        int minValue;
        bool maxHeaped = false;
        bool minHeaped = false;
        void maxHeapify(int);   // heap sort with root as max element
        void minHeapify(int);   // heap sort with root as min element
        void siftDown(int, int);// shifts element from root to proper index
        void siftDownMin(int, int);
        
    public:
        Heap();                 // constructor
        int size();             // get total number of elements
        int at(int);            // return value at index i
        bool rawInsert(int);    // insert a data item, unsorted
        bool sortedInsert(int); // insert a data item to its proper location
        bool erase(int);        // erase element at index i
        int maxElement();       // returns the value of the largest element
        int minElement();       // returns the value of the smallest element
        int getParent(int);     // int index as param, returns parent's index
        int getLeftChild(int);  // int index as param, returns L child's index
        int getRightChild(int); // int index as param, returns R child's index
        void print();           // print heap
        void buildMaxHeap();
        void buildMinHeap();
        void maxHeapSort();     // heap sort with greatest values to the right
        void minHeapSort();
};

Heap::Heap(){
    // constructor
}

int Heap::size(){
    return data.size();
}

int Heap::at(int i){
    return data.at(i);
}

bool Heap::rawInsert(int x){
    // place x at end of heap
    if (data.size() == 0){
        minValue = x;
        maxValue = x;
    }   else if (x > maxValue)   {
        maxValue = x;
    }   else if (x < minValue)   {
        minValue = x;
    }
    
    data.push_back(x);
    return true;
}

bool Heap::sortedInsert(int x){
    // find proper location for x, then place it there
    if (data.size() == 0){
        minValue = x;
        maxValue = x;
    }   else if (x > maxValue)   {
        maxValue = x;
    }   else if (x < minValue)   {
        minValue = x;
    }
    
    // implement insertion here
    
    return true;
}

bool Heap::erase(int i){
    if (i >= data.size()){
        return false;
    }   else    {
        data.erase(data.begin() + i);
        return true;
    }
}

void Heap::maxHeapify(int i){
    int left = (2*i) + 1;
    int right = (2*i) + 2;
    int largest = i;
    int size = data.size();
    if (left < size && data[left] > data[largest]){
        largest = left;
    }
    if (right < size && data[right] > data[largest]){
        largest = right;
    }
    if (largest != i){
        swap(data[largest], data[i]);
        maxHeapify(largest);
    }
}

void Heap::minHeapify(int i){
    int left = (2*i) + 1;
    int right = (2*i) + 2;
    int smallest = i;
    int size = data.size();
    if (left < size && data[left] < data[smallest]){
        smallest = left;
    }
    if (right < size && data[right] < data[smallest]){
        smallest = right;
    }
    if (smallest != i){
        swap(data[smallest], data[i]);
        minHeapify(smallest);
    }
}

void Heap::buildMinHeap(){
    for (int i = floor(data.size()/2); i >= 0; i--){
        minHeapify(i);
    }
    minHeaped = true;
    maxHeaped = false;
}

void Heap::minHeapSort(){
    if (!minHeaped){
        buildMinHeap();
    }
    
    int i = data.size() - 1;
    while (i > 0){
        swap(data[i], data[0]);
        i--;
        siftDownMin(0, i);
    }
}

void Heap::siftDownMin(int start, int end){
    int root = start;
    while (getLeftChild(root) <= end && getLeftChild(root) != -1){
        int left = getLeftChild(root);
        int iswap = root;
        if (data[iswap] > data[left]){
            iswap = left;
        }
        int right = left + 1;
        if (right <= end && right != 0 && data[iswap] > data[right]){
            iswap = right;
        }
        if (iswap == root){
            break;
        }   else    {
            swap(data[iswap], data[root]);
            root = iswap;
        }
    }
}

void Heap::buildMaxHeap(){
    for (int i = floor(data.size()/2); i >= 0; i--){
        maxHeapify(i);
    }
    minHeaped = false;
    maxHeaped = true;
}

void Heap::maxHeapSort(){
    if (!maxHeaped){
        buildMaxHeap();
    }
    int i = data.size() - 1;
    while (i > 0) {
        swap(data[i], data[0]);
        i--;        
        siftDown(0, i);
    }
}

void Heap::siftDown(int start, int end){
    // after swapping indices in maxHeapSort, move item at root to proper
    // position in the heap/vector
    int root = start;
    while (getLeftChild(root) != -1 && getLeftChild(root) <= end){
        int left = getLeftChild(root);
        int iswap = root;
        if (data[iswap] < data[left]){
            iswap = left;
        }
        int right = left + 1;
        if (right != 0 && right <= end && data[iswap] < data[right]){
            iswap = right;
        }
        if (root == iswap){
            break;
        }   else    {
            swap(data[iswap], data[root]);
            root = iswap;
        }
    }
    
}

int Heap::maxElement(){
    // return the largest element's value
    return maxValue;
}

int Heap::minElement(){
    // return the value of the smallest element
    return minValue;
}

int Heap::getParent(int i){
    // parent lies at floor((i-1)/2)
    int parentIndex;
    if (i == 0){    // root has no parent
        parentIndex = 0;
    }   else    {   // otherwise calculate parent index
        parentIndex = floor( (i-1)/2 );
    }
    
    return parentIndex;
}

int Heap::getLeftChild(int i){
    // left child lies at (2*i + 1)
    int leftChildIndex = (2*i) + 1;
    if (leftChildIndex >= data.size()){
        leftChildIndex = -1;    // set to -1 if it doesn't exist
    }
    
    return leftChildIndex;
}

int Heap::getRightChild(int i){
    // right child is at (2*i + 2)
    int rightChildIndex = (2*i) + 2;
    if (rightChildIndex >= data.size()){
        rightChildIndex = -1;   // set to -1 if doesn't exist
    }
    
    return rightChildIndex;
}

void Heap::print(){
    if (data.size() == 0){
        cout << "Heap is empty.\n";
    }   else    {
        for (int i = 0; i < data.size(); i++){
            cout << data[i] << " ";
        }
        cout << endl;
    }
}

/******************************************************************************/
/***************************** MAIN *******************************************/
/******************************************************************************/

int main(int argc, char *argv[]){
    Heap heap;    
    heap.rawInsert(9);
    heap.rawInsert(3);
    heap.rawInsert(89);
    heap.rawInsert(35);
    heap.rawInsert(42);
    heap.rawInsert(99);
    heap.rawInsert(17);
    heap.rawInsert(37);
    heap.rawInsert(-1);
    heap.rawInsert(0);
    heap.rawInsert(17);
    heap.print();
    
    cout << "Max Heap Sort (greater values to the right)...\n";
    heap.maxHeapSort();
    heap.print();
    
    cout << "Min Heap Sort (lesser values to the right)...\n";
    heap.minHeapSort();
    heap.print();
}