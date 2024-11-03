# Litenet Project Roadmap

## 1. Core: The Tensor
### 1.1 Basic Tensor Data Structure
- Design memory layout for N-dimensional tensors
   - Row-Major layout exclusively
   - float64 as primary data type
- Tensor creation/removal and associated memory management
   - Direct memory management without pooling or garbage collection
- Define basic tensor properties (shape, stride, dtype)
   - Explicit shape specification without automatic inference
- Implement tensor view/reshape operations
- Simple error handling with explicit failure modes

### 1.2 Fundamental Operations
- Element-wise operations (add, subtract, multiply, divide)
- Matrix multiplication
- Reduction operations (sum, mean, max, min)
- Broadcasting mechanisms
   - We might skip.
- Basic linear algebra operations (transpose, dot product)
- Memory-efficient operations (in-place operations)

### 1.3 Advanced Tensor Operations
- Tensor contraction
- Slicing and indexing
- Concatenation and splitting
- Random number generation
- Data type conversions
- GPU support considerations (optional future extension)

### 1.4 Time Series Specific Operations
- Sliding window operations
- Lag operations
- Seasonal decomposition
- Moving averages and exponential smoothing
- Frequency domain transformations
- Time-based indexing and resampling
- Missing value handling for temporal data

## 2. Python API
### 2.1 Python Bindings
- Create Python C extensions using Python/C API
- Implement wrapper classes for C tensor structures
- Design Pythonic API for tensor operations
- Type conversion between Python and C

### 2.2 High-level Tensor API
- NumPy-like interface design
- Method chaining support
- Integration with Python's standard library
- Documentation and type hints
- Unit testing framework

## 3. Statistical & ML Framework
### 3.1 Core Components
- Automatic differentiation engine
- Optimization algorithms (SGD, Adam, etc.)
- Loss functions
- Activation functions
- Parameter management
- Computational graph implementation

### 3.2 ML Algorithms Implementation
- Linear regression
- Logistic regression
- Neural network layers
    - Dense/Fully connected
    - Activation layers
    - Dropout
- Basic CNN components (future extension)
- Basic RNN components (future extension)
- Time Series Models
    - Exponential Smoothing family (Simple, Seasonal, Holt, Holt-Winters)
    - ARIMA family (ARIMA, SARIMA)
    - Intermittent Demand Models (Croston, ADIDA, CrostonSBA, IMAPA)
    - Statistical Models (TSB, Theta)
    - Historical Average and Baseline models
- Feature Engineering
    - Temporal feature extraction
    - Seasonality indicators
    - Trend indicators

### 3.3 Training Infrastructure
- Data loading and batching
- Training loop implementation
- Validation mechanisms
- Model saving/loading
- Performance metrics
- Early stopping
- Time series specific cross-validation
- Temporal data splitting strategies
- Time series specific metrics (MAE, MAPE, RMSE, etc.)
- Seasonal performance analysis
- Forecast horizon management

## 4. Infrastructure
### 4.1 Build System
- CMake configuration
- Python package setup
- Continuous Integration setup
- Development environment setup

### 4.2 Documentation
- API documentation
- Usage examples
- Installation guide
- Contributing guidelines

### 4.3 Testing
- Unit tests for C components
- Unit tests for Python interface
- Integration tests
- Performance benchmarks
- Memory leak detection

