#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vector structure
typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Vector;

// Internal resize function
static int vector_resize(Vector *vec) {
    size_t new_capacity = vec->capacity * 2;
    int *new_data = (int*)realloc(vec->data, new_capacity * sizeof(int));
    
    if (new_data == NULL) {
        return 0;
    }
    
    vec->data = new_data;
    vec->capacity = new_capacity;
    return 1;
}

// Function implementations
static int vector_push_back(Vector *vec, int value) {
    if (vec == NULL) {
        return 0;
    }
    
    if (vec->size >= vec->capacity) {
        if (!vector_resize(vec)) {
            return 0;
        }
    }
    
    vec->data[vec->size++] = value;
    return 1;
}

static int vector_pop_back(Vector *vec) {
    if (vec == NULL || vec->size == 0) {
        return 0;
    }
    
    vec->size--;
    return 1;
}

static int vector_get(Vector *vec, size_t index, int *value) {
    if (vec == NULL || index >= vec->size) {
        return 0;
    }
    
    *value = vec->data[index];
    return 1;
}

static int vector_set(Vector *vec, size_t index, int value) {
    if (vec == NULL || index >= vec->size) {
        return 0;
    }
    
    vec->data[index] = value;
    return 1;
}

static size_t vector_get_size(Vector *vec) {
    return vec != NULL ? vec->size : 0;
}

static size_t vector_get_capacity(Vector *vec) {
    return vec != NULL ? vec->capacity : 0;
}

static int vector_is_empty(Vector *vec) {
    return vec == NULL || vec->size == 0;
}

static void vector_clear(Vector *vec) {
    if (vec != NULL) {
        vec->size = 0;
    }
}

static void vector_print(Vector *vec) {
    if (vec == NULL) {
        printf("NULL vector\n");
        return;
    }
    
    printf("Vector [size=%zu, capacity=%zu]: [", vec->size, vec->capacity);
    for (size_t i = 0; i < vec->size; i++) {
        printf("%d", vec->data[i]);
        if (i < vec->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Constructor
Vector* vector(size_t initial_capacity) {
    Vector *vec = (Vector*)malloc(sizeof(Vector));
    if (vec == NULL) {
        return NULL;
    }
    
    vec->size = 0;
    vec->capacity = initial_capacity > 0 ? initial_capacity : 10;
    vec->data = (int*)malloc(vec->capacity * sizeof(int));
    
    if (vec->data == NULL) {
        free(vec);
        return NULL;
    }
    
    return vec;
}

// Destructor
void vector_destroy(Vector *vec) {
    if (vec != NULL) {
        free(vec->data);
        free(vec);
    }
}

// ==================== MACROS FOR CLEAN SYNTAX ====================
// These macros hide the "pass vector as parameter" requirement
#define push(vec, value) vector_push_back(vec, value)
#define pop(vec) vector_pop_back(vec)
#define get(vec, index, value_ptr) vector_get(vec, index, value_ptr)
#define set(vec, index, value) vector_set(vec, index, value)
#define size(vec) vector_get_size(vec)
#define capacity(vec) vector_get_capacity(vec)
#define isEmpty(vec) vector_is_empty(vec)
#define clear(vec) vector_clear(vec)
#define print(vec) vector_print(vec)

#endif
