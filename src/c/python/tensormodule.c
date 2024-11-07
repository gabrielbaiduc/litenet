#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "../core/tensor/tensor.h"

typedef struct {
    PyObject_HEAD
    Tensor* tensor;
} PyTensorObject;

static void PyTensor_dealloc(PyTensorObject *self) {
    tensor_free(self->tensor);
    Py_TYPE(self)->tp_free((PyObject *) self);
}

static PyObject* PyTensor_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    PyTensorObject *self;
    self = (PyTensorObject *) type->tp_alloc(type, 0);
    if (self != NULL) {
        self->tensor = NULL;
    }
    return (PyObject *) self;
}

static int PyTensor_init(PyTensorObject *self, PyObject *args, PyObject *kwds) {
    PyObject *shape_arg;
    
    if (!PyArg_ParseTuple(args, "O", &shape_arg))
        return -1;
    
    Py_ssize_t ndim = PySequence_Size(shape_arg);
    size_t *shape = malloc(ndim * sizeof(size_t));
    
    for (Py_ssize_t i = 0; i < ndim; i++) {
        PyObject *dim = PySequence_GetItem(shape_arg, i);
        shape[i] = PyLong_AsSize_t(dim);
        Py_DECREF(dim);
    }
    
    self->tensor = tensor_create(shape, ndim);
    free(shape);
    
    if (self->tensor == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Failed to create tensor");
        return -1;
    }
    
    return 0;
}

static PyTypeObject PyTensorType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "litenet.Tensor",
    .tp_basicsize = sizeof(PyTensorObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyTensor_new,
    .tp_init = (initproc) PyTensor_init,
    .tp_dealloc = (destructor) PyTensor_dealloc,
};

static PyModuleDef tensormodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "litenet",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_litenet(void) {
    PyObject *m;
    if (PyType_Ready(&PyTensorType) < 0)
        return NULL;

    m = PyModule_Create(&tensormodule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyTensorType);
    if (PyModule_AddObject(m, "Tensor", (PyObject *) &PyTensorType) < 0) {
        Py_DECREF(&PyTensorType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
