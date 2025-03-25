#include <iostream>

using namespace std;

template <typename Type>
class List {
protected:
    Type* arr;
    int maxSize;
    int currentSize;

public:
    // Listing constructor
    List(int size = 10) : maxSize(size), currentSize(0), arr(new Type[maxSize]) {}

    // copy constructor
    List(const List& other) : maxSize(other.maxSize), currentSize(other.currentSize), arr(new Type[other.maxSize]) {
        for (int i = 0; i < currentSize; i++) {
            arr[i] = other.arr[i];
        }
    }

    //virtual destructor
    virtual ~List() {
        delete[] arr;
    }

    // Abstract functions
    virtual void addElementAtFirstIndex(Type element) = 0;
    virtual void addElementAtLastIndex(Type element) = 0;
    virtual Type removeElementFromEnd() = 0;
    virtual void removeElementFromStart() = 0;

    // Getter Functions
    int getCurrentSize() const {
        return currentSize;
    }
    int getMaxSize() const {
        return maxSize;
    }

    Type getElementAtIndex(int index) const {
        if (index < 0 || index >= currentSize) {
            return Type(); // Return default value of Type if out of bounds.
        }
        return arr[index];
    }
};

// Dummy class 
template <typename Type>
class DummyList : public List<Type> {
public:
    DummyList(int size = 10) : List<Type>(size) {}

    void addElementAtFirstIndex(Type element) override {
        if (this->currentSize >= this->maxSize) {
            cout << "List is full" << endl;
            return;
        }
        for (int i = this->currentSize; i > 0; --i) {
            this->arr[i] = this->arr[i - 1];
        }
        this->arr[0] = element;
        this->currentSize++;
    }

    void addElementAtLastIndex(Type element) override {
        if (this->currentSize >= this->maxSize) {
            cout << "List is full" << endl;
            return;
        }
        this->arr[this->currentSize++] = element;
    }

    Type removeElementFromEnd() override {
        if (this->currentSize == 0) {
            cout << "List is empty" << endl;
            return Type(); // Return default value if list is empty
        }
        return this->arr[--this->currentSize];
    }

    void removeElementFromStart() override {
        if (this->currentSize == 0) {
            cout << "List is empty" << endl;
            return;
        }
        for (int i = 0; i < this->currentSize - 1; ++i) {
            this->arr[i] = this->arr[i + 1];
        }
        this->currentSize--;
    }
};

int main() {
    DummyList<int> myList(5);

    myList.addElementAtLastIndex(10);
    myList.addElementAtLastIndex(20);
    myList.addElementAtFirstIndex(5);
    myList.addElementAtLastIndex(30);

    for (int i = 0; i < myList.getCurrentSize(); i++) {
        cout << myList.getElementAtIndex(i) << " ";
    }
    cout << endl;

    cout << "Removed from end: " << myList.removeElementFromEnd() << endl;
    myList.removeElementFromStart();

    for (int i = 0; i < myList.getCurrentSize(); i++) {
        cout << myList.getElementAtIndex(i) << " ";
    }
    cout << endl;

    DummyList<int> myList2 = myList;

    for (int i = 0; i < myList2.getCurrentSize(); i++) {
        cout << myList2.getElementAtIndex(i) << " ";
    }
    cout << endl;

    return 0;
}