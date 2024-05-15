#include <iostream>
#include <cstring> 
#include <stack>
using namespace std;

//функція-шаблон послідовного пошуку в масиві по ключу
template <typename T>
int sequentialSearch(T arr[], int size, T key) {
    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            index = i;
        }
    }
    return index;
}

//специфікація функції-шаблон для типу char*
template <>
int sequentialSearch<char*>(char* arr[], int size, char* key) {
    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (strcmp(arr[i], key) == 0) {
            index = i;
        }
    }
    return index;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

//функція для обміну двох значень
template<typename T>
void mySwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

//функція для розділення масиву та повернення позиції опорного елемента
template<typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (strcmp(arr[j], pivot) <= 0) {  
            i++;
            mySwap(arr[i], arr[j]);  
        }
    }
    mySwap(arr[i + 1], arr[high]);  
    return (i + 1);
}

//функція швидкого сортування
template<typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Параметризований клас-шаблон для масиву
template <typename T, int size>
class MyArray {
private:
    T arr[size]; // Масив елементів
public:
    // Конструктор за замовчуванням
    MyArray() {}

    // Конструктор зі списком ініціалізації
    MyArray(const T(&initArr)[size]) {
        for (int i = 0; i < size; ++i) {
            arr[i] = initArr[i];
        }
    }

    // Перевантаження оператора []
    T& operator[](int index) {
        if (index >= 0 && index < size) {
            return arr[index];
        }
        // Якщо індекс недійсний, генеруємо виняток
        throw std::out_of_range("Index out of range");
    }

    // Перевантаження оператора =
    MyArray& operator=(const MyArray& other) {
        for (int i = 0; i < size; ++i) {
            arr[i] = other.arr[i];
        }
        return *this;
    }

    // Перевантаження оператора +=
    MyArray& operator+=(const MyArray& other) {
        for (int i = 0; i < size; ++i) {
            arr[i] += other.arr[i];
        }
        return *this;
    }

    // Перевантаження оператора +
    MyArray operator+(const MyArray& other) const {
        MyArray result;
        for (int i = 0; i < size; ++i) {
            result.arr[i] = arr[i] + other.arr[i];
        }
        return result;
    }

    // Перевантаження оператора -=
    MyArray& operator-=(const MyArray& other) {
        for (int i = 0; i < size; ++i) {
            arr[i] -= other.arr[i];
        }
        return *this;
    }

    // Перевантаження оператора -
    MyArray operator-(const MyArray& other) const {
        MyArray result;
        for (int i = 0; i < size; ++i) {
            result.arr[i] = arr[i] - other.arr[i];
        }
        return result;
    }

    // Деструктор
    ~MyArray() {}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Клас, що описує вузол бінарного дерева
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Клас бінарного дерева
class BinaryTree {
private:
    TreeNode* root;

    // Рекурсивна функція для вставки вузла в бінарне дерево
    TreeNode* insert(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }

        if (val < node->data) {
            node->left = insert(node->left, val);
        }
        else {
            node->right = insert(node->right, val);
        }

        return node;
    }

public:
    BinaryTree() : root(nullptr) {}

    // Метод для вставки значення в бінарне дерево
    void insert(int val) {
        root = insert(root, val);
    }

    // Клас ітератора для обходу бінарного дерева
    class Iterator {
    private:
        TreeNode* current;
        std::stack<TreeNode*> stack;

    public:
        Iterator(TreeNode* root) : current(root) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
        }

        bool hasNext() const {
            return current != nullptr || !stack.empty();
        }

        int next() {
            while (current != nullptr || !stack.empty()) {
                if (current != nullptr) {
                    stack.push(current);
                    current = current->left;
                }
                else {
                    current = stack.top();
                    stack.pop();
                    int val = current->data;
                    current = current->right;
                    return val;
                }
            }
            return -1; // Повертаємо -1 як помилку
        }
    };

    // Метод для отримання ітератора початкового вузла дерева
    Iterator getIterator() const {
        return Iterator(root);
    }
};

int main() {
    cout << "\nTask 1 \n";
    cout << "Sequential Search Template\n";

    int intArr[] = { 1, 2, 3, 4, 5 };
    int intKey = 3;
    int intIndex = sequentialSearch(intArr, 5, intKey);
    cout << "Index of " << intKey << " in intArr: " << intIndex << endl;

    const char* strArr[] = { "apple", "banana", "orange", "grape" };
    const char* strKey = "orange";
    int strIndex = sequentialSearch(strArr, 4, strKey);
    cout << "Index of \"" << strKey << "\" in strArr: " << strIndex << endl;
    
    /////////////////////////////////////////////////////////////////////

    cout << "\nTask 2 \n";

    const char* arrq[] = { "1", "4", "3", "2" };
    int nq = sizeof(arrq) / sizeof(arrq[0]);

    quickSort(arrq, 0, nq - 1);

    std::cout << "Sorted array: ";
    for (int i = 0; i < nq; i++) {
        std::cout << arrq[i] << " ";
    }
    std::cout << std::endl;
    

    const char* arr[] = { "apple", "orange", "banana", "grape" };
    int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n - 1);

    std::cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;



    //////////////////////////////////////////////////////
    
    cout << "\nTask 3 \n";
    // Приклад використання класу MyArray
    int init1[] = { 1, 2, 3 };
    int init2[] = { 4, 5, 6 };

    MyArray<int, 3> arr1(init1);
    MyArray<int, 3> arr2(init2);

    // Перевірка роботи операторів
    MyArray<int, 3> result = arr1 + arr2;
    std::cout << "arr1 + arr2: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    MyArray<int, 3> result1 = arr1 - arr2;
    std::cout << "arr1 - arr2: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << result1[i] << " ";
    }
    std::cout << std::endl;

    arr1 += arr2;
    std::cout << "arr1 += arr2: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;

    arr1 -= arr2;
    std::cout << "arr1 -= arr2: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << arr1[i] << " ";
    }
    std::cout << std::endl;


    
    //////////////////////////////////////////////////////////
    
    cout << "\nTask 4 \n";
    BinaryTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    BinaryTree::Iterator it = tree.getIterator();
    while (it.hasNext()) {
        std::cout << it.next() << " ";
    }
    std::cout << std::endl;

   
    
    return 0;
}