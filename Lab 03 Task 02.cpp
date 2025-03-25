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

template <typename Type>
class MyList : public List<Type> {
public:
    // Parameterized constructor with default arguments
    MyList(int size = 10) : List<Type>(size) {}

    // Copy constructor
    MyList(const MyList& other) : List<Type>(other) {}

    // Destructor (already defined in the base class)
    ~MyList() override {}

    bool empty() const {
        return this->currentSize == 0;
    }

    bool full() const {
        return this->currentSize == this->maxSize;
    }

    int size() const {
        return this->currentSize;
    }

    bool insertAt(int index, Type value) {
        if (index < 0 || index > this->currentSize) {
            return false;
        }
        if (this->full()) {
            cout << "List is full. Cannot insert." << endl;
            return false;
        }
        for (int i = this->currentSize; i > index; --i) {
            this->arr[i] = this->arr[i - 1];
        }
        this->arr[index] = value;
        this->currentSize++;
        return true;
    }

    Type last() const {
        if (this->empty()) {
            cout << "List is empty. Cannot get last element." << endl;
            return Type(); // Return default value if empty
        }
        return this->arr[this->currentSize - 1];
    }

    bool search(Type value) const {
        for (int i = 0; i < this->currentSize; ++i) {
            if (this->arr[i] == value) {
                return true;
            }
        }
        return false;
    }

    void addElementAtFirstIndex(Type element) override {
        if (this->full()) {
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
        if (this->full()) {
            cout << "List is full" << endl;
            return;
        }
        this->arr[this->currentSize++] = element;
    }

    Type removeElementFromEnd() override {
        if (this->empty()) {
            cout << "List is empty" << endl;
            return Type(); // Return default value if list is empty
        }
        return this->arr[--this->currentSize];
    }

    void removeElementFromStart() override {
        if (this->empty()) {
            cout << "List is empty" << endl;
            return;
        }
        for (int i = 0; i < this->currentSize - 1; ++i) {
            this->arr[i] = this->arr[i + 1];
        }
        this->currentSize--;
    }

    void display() const {
        if (this->empty()) {
            cout << "List is empty." << endl;
            return;
        }
        cout << "List elements: ";
        for (int i = 0; i < this->currentSize; ++i) {
            cout << this->arr[i] << (i == this->currentSize - 1 ? "" : " ");
        }
        cout << endl;
    }
};

int main() {
    MyList<int> myList;
    int choice;
    int value, index;

    do {
        cout << "\n--- MyList Menu ---" << endl;
        cout << "1. Add element at the beginning" << endl;
        cout << "2. Add element at the end" << endl;
        cout << "3. Insert element at a specific index" << endl;
        cout << "4. Remove element from the beginning" << endl;
        cout << "5. Remove element from the end" << endl;
        cout << "6. Get the last element" << endl;
        cout << "7. Search for an element" << endl;
        cout << "8. Check if the list is empty" << endl;
        cout << "9. Check if the list is full" << endl;
        cout << "10. Get the current size of the list" << endl;
        cout << "11. Display the list" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the value to add at the beginning: ";
            cin >> value;
            myList.addElementAtFirstIndex(value);
            break;
        case 2:
            cout << "Enter the value to add at the end: ";
            cin >> value;
            myList.addElementAtLastIndex(value);
            break;
        case 3:
            cout << "Enter the index to insert at: ";
            cin >> index;
            cout << "Enter the value to insert: ";
            cin >> value;
            if (myList.insertAt(index, value)) {
                cout << "Value inserted successfully." << endl;
            }
            else {
                cout << "Invalid index or list is full." << endl;
            }
            break;
        case 4:
            myList.removeElementFromStart();
            cout << "Element removed from the beginning (if any)." << endl;
            break;
        case 5:
            cout << "Removed from end: " << myList.removeElementFromEnd() << endl;
            break;
        case 6:
            cout << "Last element: " << myList.last() << endl;
            break;
        case 7:
            cout << "Enter the value to search: ";
            cin >> value;
            if (myList.search(value)) {
                cout << value << " found in the list." << endl;
            }
            else {
                cout << value << " not found in the list." << endl;
            }
            break;
        case 8:
            if (myList.empty()) {
                cout << "List is empty." << endl;
            }
            else {
                cout << "List is not empty." << endl;
            }
            break;
        case 9:
            if (myList.full()) {
                cout << "List is full." << endl;
            }
            else {
                cout << "List is not full." << endl;
            }
            break;
        case 10:
            cout << "Current size of the list: " << myList.size() << endl;
            break;
        case 11:
            myList.display();
            break;
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
        // A simple way to clear the input buffer without <limits>
        cin.ignore(1000, '\n');
    } while (choice != 0);

    return 0;
}