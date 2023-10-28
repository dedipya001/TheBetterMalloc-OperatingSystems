#include <stdio.h>
#include <stdlib.h>

char* heap = NULL;
int heapIndex = 0;
int maxHeapSize = 0;

void* myMalloc(int size) {
    if (heapIndex + size <= maxHeapSize) {
        void* ptr = &heap[heapIndex];
        heapIndex += size;
        return ptr;
    } else {
        return NULL;
    }
}

void myFree(void* ptr) {
    int deallocatedSize = (int)((char*)ptr - heap);
    for (int i = deallocatedSize; i < heapIndex; i++) {
        heap[i - deallocatedSize] = heap[i];
    }
    heapIndex -= deallocatedSize;
}

void viewHeapStatus() {
    printf("Heap status:\n");

    // Calculate the free size
    int freeSize = maxHeapSize - heapIndex;

    // Print the header line
    printf("+");
    for (int i = 0; i < maxHeapSize; i++) {
        printf("-");
    }
    printf("+\n");

    // Print the used memory section
    printf("|");
    for (int i = 0; i < heapIndex; i++) {
        printf("X");
    }
    printf("|\n");

    // Print the free memory section
    printf("|");
    for (int i = 0; i < freeSize; i++) {
        printf(" ");
    }
    printf("|\n");

    // Print the footer line
    printf("+");
    for (int i = 0; i < maxHeapSize; i++) {
        printf("-");
    }
    printf("+\n");

    // Print the size information
    printf("Total size: %d\n", maxHeapSize);
    printf("Used size : %d\n", heapIndex);
    printf("Free size : %d\n", freeSize);
}



int main() {

    int choice, size;
    void* ptr;

    printf("Enter the maximum heap size: ");
    scanf("%d", &maxHeapSize);
    heap = (char*)malloc(maxHeapSize);

    while (1) {
        printf("\nMenu:\n");
        printf("1. Allocate memory\n");
        printf("2. Deallocate memory\n");
        printf("3. View heap status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the size to allocate: ");
                scanf("%d", &size);
                ptr = myMalloc(size);
                if (ptr == NULL) {
                    printf("Memory allocation failed. Not enough space in the heap.\n");
                } else {
                    printf("Memory allocated at address: %p\n", ptr);
                }
                break;
            case 2:
                printf("Enter the address to deallocate: ");
                scanf("%p", &ptr);
                myFree(ptr);
                printf("Memory deallocated.\n");
                break;
            case 3:
                viewHeapStatus();
                break;
            case 4:
                printf("Exiting program.\n");
                free(heap);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}



