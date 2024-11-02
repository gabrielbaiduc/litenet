#ifndef LITENET_TENSOR_H
#define LITENET_TENSOR_H

#include <stddef.h>

typedef struct {
    double* data;        // Contiguous data array
    size_t* shape;       // Array of dimension sizes [d1, d2, ..., dn]
    size_t* strides;     // Array of strides for each dimension
    size_t ndim;         // Number of dimensions
    size_t size;         // Total number of elements
} Tensor;

// Creation and destruction
Tensor* tensor_create(const size_t* shape, size_t ndim);
void tensor_free(Tensor* tensor);

// Core operations
int tensor_fill(Tensor* tensor, double value);
int tensor_get(const Tensor* tensor, const size_t* indices, double* value);
int tensor_set(Tensor* tensor, const size_t* indices, double value);

// Helper functions
size_t tensor_calculate_index(const Tensor* tensor, const size_t* indices);
void tensor_calculate_strides(Tensor* tensor);
int tensor_validate_indices(const Tensor* tensor, const size_t* indices);

#endif // LITENET_TENSOR_H 