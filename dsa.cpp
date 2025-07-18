#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Generate random numbers
void generateRandomNumbers(int arr[], int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }
}

// Display array
void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}
void mergeSort(int arr[], int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Recursive Binary Search
int BinarySearch(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return BinarySearch(arr, l, mid - 1, x);
        return BinarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

// Exponential Search
int exponentialSearch(int arr[], int n, int x) {
    if (arr[0] == x)
        return 0;
    int i = 1;
    while (i < n && arr[i] <= x)
        i *= 2;
    return BinarySearch(arr, i / 2, min(i, n - 1), x);
}

int main() {
    int n;
    cout << "Enter the number of random integers to generate: ";
    cin >> n;
    if (n <= 0) {
        cout << "Please enter a positive number.\n";
        return 1;
    }

    int* arr = new int[n];
    generateRandomNumbers(arr, n);

    cout << "\nGenerated array:\n";
    displayArray(arr, n);

    cout << "\nSelect sorting algorithm:\n";
    cout << "1. Quick Sort\n";
    cout << "2. Merge Sort\n";
    cout << "Enter choice: ";
    int sortChoice;
    cin >> sortChoice;

    auto start = high_resolution_clock::now();
    switch (sortChoice) {
        case 1:
            quickSort(arr, 0, n - 1);
            break;
        case 2:
            mergeSort(arr, 0, n - 1);
            break;
        default:
            cout << "Invalid choice. Exiting.\n";
            delete[] arr;
            return 1;
    }
    auto end = high_resolution_clock::now();
    auto sortDuration = duration_cast<nanoseconds>(end - start);
    cout << "\nTime taken by sorting algorithm: " << sortDuration.count() << " nanoseconds\n";

    cout << "\nSorted array:\n";
    displayArray(arr, n);

    cout << "\nEnter the element to search for: ";
    int target;
    cin >> target;

    cout << "\nSelect searching algorithm:\n";
    cout << "1. Binary Search\n";
    cout << "2. Exponential Search\n";
    cout << "Enter choice: ";
    int searchChoice;
    cin >> searchChoice;

    int result = -1;
    start = high_resolution_clock::now();
    switch (searchChoice) {
        case 1:
            result = BinarySearch(arr, 0, n - 1, target);
            break;
        case 2:
            result = exponentialSearch(arr, n, target);
            break;
        default:
            cout << "Invalid choice.\n";
            delete[] arr;
            return 1;
    }
    end = high_resolution_clock::now();
    auto searchDuration = duration_cast<nanoseconds>(end - start);
    cout << "Time taken by search algorithm: " << searchDuration.count() << " nanoseconds\n";

    if (result == -1)
        cout << "Element is not present in the array.\n";
    else
        cout << "Element is present at index " << result << ".\n";

    delete[] arr;
    return 0;
}
