#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <structmember.h>
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
    printf("PyTensor_new: Starting\n");
    PyTensorObject *self;
    self = (PyTensorObject *)type->tp_alloc(type, 0);
    if (self != NULL) {
        printf("PyTensor_new: Allocated object\n");
        self->tensor = NULL;
    } else {
        printf("PyTensor_new: Failed to allocate\n");
    }
    printf("PyTensor_new: Completed\n");
    return (PyObject *)self;
}

static int PyTensor_init(PyTensorObject *self, PyObject *args, PyObject *kwds) {
    printf("PyTensor_init: Starting\n");
    PyObject *shape_arg;
    
    if (!PyArg_ParseTuple(args, "O", &shape_arg)) {
        printf("PyTensor_init: Failed to parse arguments\n");
        return -1;
    }
    
    if (!PySequence_Check(shape_arg)) {
        printf("PyTensor_init: shape_arg is not a sequence\n");
        PyErr_SetString(PyExc_TypeError, "Shape must be a sequence");
        return -1;
    }
    
    Py_ssize_t ndim = PySequence_Size(shape_arg);
    printf("PyTensor_init: ndim = %zd\n", ndim);
    
    size_t *shape = malloc(ndim * sizeof(size_t));
    if (!shape) {
        printf("PyTensor_init: Failed to allocate shape array\n");
        PyErr_NoMemory();
        return -1;
    }
    
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
Eg.: when we use the `class` keyword in Python, this type object is created 
under the hood.
There are numerous, so-called tp-slots, that define the behavior of the type.
See: https://docs.python.org/3/c-api/typeobj.html for more info.
*/
static PyTypeObject PyTensorType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "litenet._litenet_core.Tensor",
    .tp_doc = "Tensor objects",
    .tp_basicsize = sizeof(PyTensorObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PyTensor_new,
    .tp_init = (initproc)PyTensor_init,
    .tp_dealloc = (destructor)PyTensor_dealloc,
    .tp_getset = PyTensor_getsetters,
    .tp_str = NULL,
    .tp_repr = NULL,
    
    // Add these required fields
    .tp_alloc = PyType_GenericAlloc,
    .tp_free = PyObject_Del,
    .tp_methods = NULL,
    .tp_members = NULL,
    .tp_base = NULL,
    .tp_dict = NULL,
    .tp_descr_get = NULL,
    .tp_descr_set = NULL,
    .tp_dictoffset = 0,
    .tp_clear = NULL,
    .tp_richcompare = NULL,
    .tp_weaklistoffset = 0,
    .tp_iter = NULL,
    .tp_iternext = NULL,
    .tp_traverse = NULL
};

/*
We create the Python module with these definitions. This allows our C code to be
imported into Python as if it were a Python module. This code is compiled
and when we import the module in Python, the PyInit__litenet_core function is
called which initializes the module returning a module object.
*/
static PyModuleDef tensormodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "_litenet_core",
    .m_doc = "Litenet core module",
    .m_size = -1,
    .m_methods = NULL
};

PyMODINIT_FUNC PyInit__litenet_core(void) {
    printf("Starting module initialization\n");  // Debug print
    
    PyObject *m;
    printf("Preparing type\n");  // Debug print
    if (PyType_Ready(&PyTensorType) < 0) {
        printf("Type preparation failed\n");  // Debug print
        return NULL;
    }

    printf("Creating module\n");  // Debug print
    m = PyModule_Create(&tensormodule);
    if (m == NULL) {
        printf("Module creation failed\n");  // Debug print
        return NULL;
    }

    printf("Adding type to module\n");  // Debug print
    Py_INCREF(&PyTensorType);
    if (PyModule_AddObject(m, "Tensor", (PyObject *) &PyTensorType) < 0) {
        printf("Adding type failed\n");  // Debug print
        Py_DECREF(&PyTensorType);
        Py_DECREF(m);
        return NULL;
    }

    printf("Module initialization complete\n");  // Debug print
    return m;
}
