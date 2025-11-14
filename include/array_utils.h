#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

// Push an element at the end
void pushBack(int arr[], int *n, int value) {
    arr[*n] = value;
    (*n)++;
}

// Push an element at the front
void pushFront(int arr[], int *n, int value) {
    for (int i = *n; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = value;
    (*n)++;
}

// Push at specific index
void pushAt(int arr[], int *n, int index, int value) {
    for (int i = *n; i > index; i--) {
        arr[i] = arr[i - 1];
    }
    arr[index] = value;
    (*n)++;
}

// Pop last element
int popBack(int arr[], int *n) {
    if (*n <= 0) return -1;
    (*n)--;
    return arr[*n];
}

// Pop first element
int popFront(int arr[], int *n) {
    if (*n <= 0) return -1;
    int removed = arr[0];
    for (int i = 1; i < *n; i++) {
        arr[i - 1] = arr[i];
    }
    (*n)--;
    return removed;
}

// Pop at specific index
int popAt(int arr[], int *n, int index) {
    if (*n <= 0) return -1;
    int removed = arr[index];
    for (int i = index + 1; i < *n; i++) {
        arr[i - 1] = arr[i];
    }
    (*n)--;
    return removed;
}

#endif
