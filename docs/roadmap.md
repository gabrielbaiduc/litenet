# TODO: compress and simplify this roadmap.

# Litenet Project Roadmap

## 1. Core Tensor Operations (C Implementation)
### 1.1 Basic Tensor Structure
- Design memory layout for n-dimensional tensors
- Implement tensor creation and memory management
- Define basic tensor properties (shape, stride, dtype)
- Implement tensor view/reshape operations

### 1.2 Fundamental Operations
- Element-wise operations (add, subtract, multiply, divide)
- Matrix multiplication
- Reduction operations (sum, mean, max, min)
- Broadcasting mechanisms
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

## 2. Python Interface for Tensor Operations
### 2.1 Python Bindings
- Create Python C extensions using Python/C API
- Implement wrapper classes for C tensor structures
- Design Pythonic API for tensor operations
- Error handling and memory management
- Type conversion between Python and C

### 2.2 High-level Tensor API
- NumPy-like interface design
- Method chaining support
- Integration with Python's standard library
- Documentation and type hints
- Unit testing framework

## 3. Machine Learning Framework
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

## 4. Project Infrastructure
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

## Development Phases

1. **Phase 1: Time Series Foundation**
   - Basic tensor operations essential for time series (1.1, 1.2)
   - Time series specific operations (1.4)
   - Python bindings for time series operations
   - Time series data handling and preprocessing

2. **Phase 2: Forecasting Models**
   - Core statistical components
   - Basic forecasting models (Historical Average, Simple Exponential Smoothing)
   - Advanced forecasting models (Holt-Winters, SARIMA)
   - Intermittent demand models (Croston family)

3. **Phase 3: Production Infrastructure**
   - Model validation and testing framework
   - Time series specific metrics
   - Model persistence and versioning
   - Performance optimization for production use
   - Batch prediction capabilities

4. **Phase 4: Framework Extension**
   - Additional tensor operations
   - Support for other ML algorithms
   - Advanced features (GPU support, distributed computing)
   - Integration with other ML frameworks

## Initial Focus Areas
1. Implement core tensor data structure
2. Implement fundamental tensor operations
3. Extend core tensor operations to handle time-series data
4. Develop core forecasting algorithms
5. Build validation and testing infrastructure for time series


### 1. Core Tensor Data Structure for N-Dimensional Tensors (Design Decisions)
- Row-major memory layout exclusively
- Contiguous memory blocks only (no views or discontiguous memory)
- Double precision (float64) as primary data type
- Simple error handling with explicit failure modes
- Direct memory management without pooling or garbage collection
- Explicit shape specification without automatic inference
- Basic arithmetic and reduction operations initially (add, subtract, multiply, divide) (sum, mean, max, min) (no dot product, no transpose or linear algebra operations)
- No automatic broadcasting or type conversion
