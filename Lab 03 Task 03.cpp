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

    bool insertAt(int index, Type value)  {
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

protected:
    bool isPrime(Type n) const {
        if (n <= 1) return false;
        for (Type i = 2; i * i <= n; ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }
};

template <typename Type>
class CustomList : public MyList<Type> {
public:
    // Parameterized constructor with default arguments
    CustomList(int size = 10) : MyList<Type>(size) {}

    // Copy constructor
    CustomList(const CustomList& other) : MyList<Type>(other) {}

    // Destructor (already defined in the base class)
    ~CustomList() override {}

    Type sum_ofPrime() const {
        Type sum = 0;
        for (int i = 0; i < this->currentSize; ++i) {
            if (this->isPrime(this->arr[i])) {
                sum += this->arr[i];
            }
        }
        return sum;
    }

    Type secondMaxEven() const {
        if (this->currentSize < 2) return Type();
        Type max1 = Type();
        Type max2 = Type();
        for (int i = 0; i < this->currentSize; ++i) {
            if (this->arr[i] % 2 == 0) {
                if (this->arr[i] > max1) {
                    max2 = max1;
                    max1 = this->arr[i];
                }
                else if (this->arr[i] > max2 && this->arr[i] < max1) {
                    max2 = this->arr[i];
                }
                else if (max1 == max2 && this->arr[i] % 2 == 0 && this->arr[i] < max1) {
                    max2 = this->arr[i];
                }
            }
        }
        if (max2 % 2 == 0) return max2;
        cout << "Less than two distinct even numbers in the list." << endl;
        return Type();
    }

    Type secondMinOdd() const {
        if (this->currentSize < 2) return Type();
        Type min1 = -1; // Initialize with a value that won't likely be in the list
        Type min2 = -1;

        for (int i = 0; i < this->currentSize; ++i) {
            if (this->arr[i] % 2 != 0) {
                if (min1 == -1 || this->arr[i] < min1) {
                    min2 = min1;
                    min1 = this->arr[i];
                }
                else if ((min2 == -1 || this->arr[i] < min2) && this->arr[i] > min1) {
                    min2 = this->arr[i];
                }
                else if (min1 == min2 && min1 != -1 && this->arr[i] % 2 != 0 && this->arr[i] > min1) {
                    min2 = this->arr[i];
                }
                else if (min1 == -1 && min2 == -1) {
                    min1 = this->arr[i];
                }
                else if (min1 != -1 && min2 == -1 && this->arr[i] % 2 != 0 && this->arr[i] > min1) {
                    min2 = this->arr[i];
                }
            }
        }

        if (min2 != -1 && min2 % 2 != 0) return min2;
        cout << "Less than two distinct odd numbers in the list." << endl;
        return Type();
    }

    void printDuplicates() const {
        if (this->currentSize <= 1) {
            cout << "No duplicates possible with less than 2 elements." << endl;
            return;
        }
        cout << "Duplicate numbers: ";
        bool foundDuplicate = false;
        for (int i = 0; i < this->currentSize; ++i) {
            for (int j = i + 1; j < this->currentSize; ++j) {
                if (this->arr[i] == this->arr[j]) {
                    bool alreadyPrinted = false;
                    for (int k = 0; k < i; ++k) {
                        if (this->arr[k] == this->arr[i]) {
                            alreadyPrinted = true;
                            break;
                        }
                    }
                    if (!alreadyPrinted) {
                        cout << this->arr[i] << " ";
                        foundDuplicate = true;
                    }
                    break; // Move to the next element after finding a duplicate
                }
            }
        }
        if (!foundDuplicate) {
            cout << "No duplicates found.";
        }
        cout << endl;
    }

    void rotateClockwaise(int r) {
        if (this->empty()) return;
        int halfSize = this->currentSize / 2;
        if (halfSize == 0) return; // Cannot rotate if only one element or empty

        // Rotate the first half
        for (int i = 0; i < r; ++i) {
            Type temp = this->arr[halfSize - 1];
            for (int j = halfSize - 1; j > 0; --j) {
                this->arr[j] = this->arr[j - 1];
            }
            this->arr[0] = temp;
        }

        // Rotate the second half
        for (int i = 0; i < r; ++i) {
            Type temp = this->arr[this->currentSize - 1];
            for (int j = this->currentSize - 1; j > halfSize; --j) {
                this->arr[j] = this->arr[j - 1];
            }
            this->arr[halfSize] = temp;
        }
    }

    void rotateanitclockwaise(int rt) {
        if (this->empty()) return;
        int halfSize = this->currentSize / 2;
        if (halfSize == 0) return; // Cannot rotate if only one element or empty

        // Rotate the first half
        for (int i = 0; i < rt; ++i) {
            Type temp = this->arr[0];
            for (int j = 0; j < halfSize - 1; ++j) {
                this->arr[j] = this->arr[j + 1];
            }
            this->arr[halfSize - 1] = temp;
        }

        // Rotate the second half
        for (int i = 0; i < rt; ++i) {
            Type temp = this->arr[halfSize];
            for (int j = halfSize; j < this->currentSize - 1; ++j) {
                this->arr[j] = this->arr[j + 1];
            }
            this->arr[this->currentSize - 1] = temp;
        }
    }
};

int main() {
    CustomList<int> myList;
    int choice;
    int value, index, rotations;

    do {
        cout << "\n--- CustomList Menu ---" << endl;
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
        cout << "12. Calculate sum of prime numbers" << endl;
        cout << "13. Find second maximum even number" << endl;
        cout << "14. Find second minimum odd number" << endl;
        cout << "15. Print duplicate numbers" << endl;
        cout << "16. Rotate clockwise" << endl;
        cout << "17. Rotate anticlockwise" << endl;
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
        case 12:
            cout << "Sum of prime numbers: " << myList.sum_ofPrime() << endl;
            break;
        case 13:
            cout << "Second maximum even number: " << myList.secondMaxEven() << endl;
            break;
        case 14:
            cout << "Second minimum odd number: " << myList.secondMinOdd() << endl;
            break;
        case 15:
            myList.printDuplicates();
            break;
        case 16:
            cout << "Enter the number of clockwise rotations: ";
            cin >> rotations;
            myList.rotateClockwaise(rotations);
            break;
        case 17:
            cout << "Enter the number of anticlockwise rotations: ";
            cin >> rotations;
            myList.rotateanitclockwaise(rotations);
            break;
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
        cin.ignore(1000, '\n');
    } while (choice != 0);

    return 0;
}