#include "tensor.h"
#include <stdlib.h>

Tensor* tensor_create(const size_t* shape, size_t ndim) {
    Tensor* tensor = malloc(sizeof(Tensor));
    if (!tensor) return NULL;

    tensor->ndim = ndim;
    tensor->shape = malloc(ndim * sizeof(size_t));
    if (!tensor->shape) {
        free(tensor);
        return NULL;
    }

    size_t total_size = 1;
    for (size_t i = 0; i < ndim; i++) {
        tensor->shape[i] = shape[i];
        total_size *= shape[i];
    }
    tensor->size = total_size;

    tensor->data = malloc(total_size * sizeof(double));
    if (!tensor->data) {
        free(tensor->shape);
        free(tensor);
        return NULL;
    }

    return tensor;
}

void tensor_free(Tensor* tensor) {
    if (tensor) {
        free(tensor->data);
        free(tensor->shape);
        free(tensor);
    }
}