// 1.	Includes and Definitions: Environment setup.
// 2.	Object Structure: Defines PyTensorObject.
// 3.	Lifecycle Management: Handles new, init, and dealloc.
// 4.	Methods/Properties: Exposes functionality like shape.
// 5.	Type Definition: Registers your custom Python type (litenet.Tensor).
// 6.	Module Setup: Initializes the _litenet_core module.

#define PY_SSIZE_T_CLEAN 
#include <Python.h> 
#include "../tensor/tensor.h"

/* 
PyObject component: defines the memory layout of the Tensor type. 
The PyObject_HEAD macro is a placeholder for a PyObject 
The PyObject gives us the header struct.
The header holds a reference count (ob_refcnt) and a type pointer (ob_type). 
*/
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

static PyObject* PyTensor_get_shape(PyTensorObject *self, void *closure) {
    PyObject *shape_tuple = PyTuple_New(self->tensor->ndim);
    for (size_t i = 0; i < self->tensor->ndim; i++) {
        PyTuple_SET_ITEM(shape_tuple, i, PyLong_FromSize_t(self->tensor->shape[i]));
    }
    return shape_tuple;
}

static PyGetSetDef PyTensor_getsetters[] = {
    {"shape", (getter)PyTensor_get_shape, NULL, "Get tensor shape", NULL},
    {NULL}
};

/*
Type Object component: defines the Tensor type as a Python object, ie.: a class.
There are numerous, so-called tp-slots.
See: https://docs.python.org/3/c-api/typeobj.html for more info.
*/
static PyTypeObject PyTensorType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "litenet.Tensor",
    .tp_basicsize = sizeof(PyTensorObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyTensor_new,
    .tp_init = (initproc) PyTensor_init,
    .tp_dealloc = (destructor) PyTensor_dealloc,
    .tp_getset = PyTensor_getsetters,
};

static PyModuleDef tensormodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "_litenet_core",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit__litenet_core(void) {
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
