#ifndef UTILS_H
#define UTILS_H

int sum_of_array(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum;
}

int count_even(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] % 2 == 0) count++;
    return count;
}

int count_odd(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] % 2 != 0) count++;
    return count;
}

int is_leap_year(int year) {
    return (year % 400 == 0) ||
           (year % 4 == 0 && year % 100 != 0);
}

int max_in_array(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}

int min_in_array(int arr[], int n) {
    int min = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] < min) min = arr[i];
    return min;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

long long factorial(int n) {
    if (n < 0) return -1; // invalid
    long long f = 1;
    for (int i = 1; i <= n; i++)
        f *= i;
    return f;
}

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

void reverse_array(int arr[], int n) {
    int i = 0, j = n - 1;
    while (i < j)
        swap(&arr[i++], &arr[j--]);
}

float average_array(int arr[], int n) {
    return (float)sum_of_array(arr, n) / n;
}

#endif
