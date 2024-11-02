#include "tensor.h"
#include <stdlib.h>

/**
 * Converts n-dimensional indices to a linear index in memory.
 * 
 * For a 2x3 matrix stored in row-major order:
 * [1 2 3]
 * [4 5 6]
 * 
 * Memory layout: [1 2 3 4 5 6]
 * Strides: [3, 1] (skip 3 to move down a row, skip 1 to move right)
 * 
 * Example: To access position [1,1] (value 5):
 * 
 * index = indices[0] * strides[0] + indices[1] * strides[1]
 *       = 1 * 3 + 1 * 1
 *       = 4
 * 
 * Therefore, data[4] gives us the value 5
 * 
 * We can then use the index like this: `tensor->data[tensor_calculate_index(tensor, indices)]`
 * 
 * @param tensor Pointer to the tensor structure
 * @param indices Array of indices, one for each dimension
 * @return Linear index into the data array
 */
size_t tensor_calculate_index(const Tensor* tensor, const size_t* indices) {
    size_t index = 0;
    for (size_t i = 0; i < tensor->ndim; i++) {
        index += indices[i] * tensor->strides[i];
    }
    return index;
}

// Calculate strides for each dimension
void tensor_calculate_strides(Tensor* tensor) {
    tensor->strides = malloc(tensor->ndim * sizeof(size_t));
    size_t stride = 1;
    
    // For row-major order, we calculate strides from right to left
    for (size_t i = tensor->ndim; i > 0; i--) {
        tensor->strides[i-1] = stride;
        stride *= tensor->shape[i-1];
    }
}

// Create tensor with specified shape
Tensor* tensor_create(const size_t* shape, size_t ndim) {
    Tensor* tensor = malloc(sizeof(Tensor));
    if (!tensor) return NULL;

    tensor->ndim = ndim;
    tensor->shape = malloc(ndim * sizeof(size_t));
    if (!tensor->shape) {
        free(tensor);
        return NULL;
    }

    // Copy shape and calculate total size
    size_t total_size = 1;
    for (size_t i = 0; i < ndim; i++) {
        tensor->shape[i] = shape[i];
        total_size *= shape[i];
    }
    tensor->size = total_size;

    // Allocate data array
    tensor->data = malloc(total_size * sizeof(double));
    if (!tensor->data) {
        free(tensor->shape);
        free(tensor);
        return NULL;
    }

    // Calculate strides for n-dimensional access
    tensor_calculate_strides(tensor);
    if (!tensor->strides) {
        free(tensor->data);
        free(tensor->shape);
        free(tensor);
        return NULL;
    }

    return tensor;
}