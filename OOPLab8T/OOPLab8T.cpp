#include <iostream>
#include <cstring> // for strcmp
using namespace std;

// Function template for sequential search in an array
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

// Specialization for char* type
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

template <typename T>
void swap1(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Шаблон функції для розбиття масиву для швидкого сортування
template <typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            swap1(arr[i], arr[j]);
        }
    }
    swap1(arr[i + 1], arr[high]);
    return i + 1;
}

// Шаблон функції для швидкого сортування
template <typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Спеціалізація функції для типу char*
template <>
void quickSort<char*>(char* arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Функція для виводу масиву
template <typename T>
void printArray(T arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
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

    cout << "Quick Sort Template\n";

    int intArr1[] = {5, 2, 9, 1, 6};
    int intSize = sizeof(intArr1) / sizeof(intArr1[0]);
    quickSort(intArr1, 0, intSize - 1);
    cout << "Sorted intArr1: ";
    printArray(intArr1, intSize);

    const char* strArr1[] = {"apple", "banana", "orange", "grape"};
    int strSize = sizeof(strArr1) / sizeof(strArr1[0]);
    quickSort(strArr1, 0, strSize - 1);
    cout << "Sorted strArr1: ";
    printArray(strArr1, strSize);
    return 0;
}