#include <iostream>
#include <omp.h>
using namespace std;

// Merge Function
void merge(int arr[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = 0;

    int temp[right - left + 1];

    // Merge two sorted halves
    while (i <= mid && j <= right) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Copy remaining elements of left half
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy remaining elements of right half
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy back to original array
    for (i = left, k = 0; i <= right; i++, k++) {
        arr[i] = temp[k];
    }
}

// Parallel Merge Sort Function
void parallelMergeSort(int arr[], int left, int right) {

    if (left < right) {

        int mid = (left + right) / 2;

        // Parallel Sections
        #pragma omp parallel sections
        {

            // Left half sorting
            #pragma omp section
            {
                parallelMergeSort(arr, left, mid);
            }

            // Right half sorting
            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, right);
            }
        }

        // Merge sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {

    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Start Parallel Merge Sort
    parallelMergeSort(arr, 0, n - 1);

    cout << "\nSorted Array:\n";

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}