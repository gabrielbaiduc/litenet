#include <stdio.h>

#define LEFT(i) (2 * (i) + 1)
#define RIGHT(i) (2 * (i) + 2)

void max_heapify(int A[], int heap_size, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest;
    
    // Find the largest among node i and its children
    if (l < heap_size && A[l] > A[i])
        largest = l;
    else
        largest = i;
    
    if (r < heap_size && A[r] > A[largest])
        largest = r;
    
    // If one of the children is larger than the node,
    // swap the node with the largest child and recursively heapify
    if (largest != i) {
        // Exchange A[i] with A[largest]
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        
        // Recursively heapify the affected subtree
        max_heapify(A, heap_size, largest);
    }
}

void build_max_heap(int A[], int heap_size) {
    // Start from the last non-leaf node and work up to the root
    for (int i = heap_size / 2 - 1; i >= 0; i--) {
        max_heapify(A, heap_size, i);
    }
}

void heapsort(int A[], int length) {
    // Build a max-heap from the input array
    build_max_heap(A, length);
    
    // Extract elements from the heap one by one
    for (int i = length - 1; i > 0; i--) {
        // Move current root (maximum element) to the end
        int temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        
        // Call max_heapify on the reduced heap
        max_heapify(A, i, 0);
    }
}

// Example usage
int main() {
    int A[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int n = sizeof(A) / sizeof(A[0]);
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    // Build a max-heap
    build_max_heap(A, n);
    
    printf("Max heap: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    // Sort the array using heapsort
    heapsort(A, n);
    
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    return 0;
}

