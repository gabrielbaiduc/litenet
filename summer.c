#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

EXPORT int summer(int a, int b) {
    return a + b;
}

// compile with:
// gcc -shared -o my_library.dylib -fPIC my_c_file.c
// then use in Python with:
// import ctypes
// lib = ctypes.CDLL('./my_library.dylib')
// set arg types and return types with
// lib.my_function.argtypes = (ctypes.c_int, ctypes.c_int)
// lib.my_function.restype = ctypes.c_int
// call the function with:
// result = lib.my_function(1, 2)
// or (more Pythonic), wrap it in python code:
// def my_function(a, b):
//     return lib.my_function(a, b)
