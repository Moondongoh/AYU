#include <stdio.h>

void swap(int* a, int* b);
int partition(int arr[], int low, int high);
void quicksort(int arr[], int low, int high);
void printArray(int arr[], int size);
int main() {
    int arr[] = { 3,6,4,8,9,1,2,7 };
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("array: ");
    printArray(arr, size);
    quicksort(arr, 0, size - 1);
    printf("sorted array: ");
    printArray(arr, size);
    return 0;
}
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int tmp = partition(arr, low, high);
        quicksort(arr, low, tmp - 1);
        quicksort(arr, tmp + 1, high);
    }
}
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("\n");
}