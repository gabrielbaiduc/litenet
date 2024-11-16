This file serves as a prompt for you to understand the project and give you an entrypoint to quickly get up to speed whenever I start a new conversation with you.

This project is called "Litenet". It's a minimalistic machine learning library built with Python and C.

Here's a high level overview of what I want 'Linetnet' to be able to do. First, it must be able to handle data. This means that we must implement 'ndarrays' like NumPy or 'tensors' like TensorFlow and PyTorch. Second, 'Litenet' needs a framework to perform machine learning operations leveraging the 'tensor' objects and operations on them. 

I envisioned the overall structure to look like this; performance critical applications are written in C while the library structure and the high-level API is written in Python. 

The first step is to create the basic functionalities; tensor data structure and basic operations on them (addition, subtraction, multiplication and division), Python bindings for it, a simple Python API and testing. This includes the ability to import the library in Python and use it to perform the operations on Tensors.

In general, I want your answers to be concise but not terse. Avoid bulletpoints. Write your answers out in a conversational, human-like manner. Generally, keep your answers simple and high-level, easy to understand. If I need more detail or a more technical explanation about a subject, I'll prompt you for more details or a more technical explanation.

To build the project, we use CMake. We have a CMakeLists.txt file that is configured to use the appropriate Python installation and related files. 

We have a rudimentary project structure with a `src` directory skeleton with a basic implementation of the tensor data structure and a create function that allocates memory for it with other skeleton files to allow for importing the library in a Python interpreter.

