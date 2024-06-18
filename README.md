

---

# LeanML: Machine Learning Framework

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/RogueWarrior34/LeanML)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Overview

**LeanML (Machine Learning Framework)** is a C-based library designed to facilitate the implementation of machine learning algorithms. It provides core functionalities for matrix and vector operations, essential for numerical computing and linear algebra tasks in machine learning.

This project is **heavily a work in progress**, and is currently focused on developing linear regression capabilities. Future plans include creating C++ bindings to leverage C++ features and simplify integration with modern applications.

## Features

- **Matrix Operations**: Creation, manipulation, and destruction of matrices.
- **Vector Operations**: Support for row and column vectors.
- **Data Loading**: Load matrices from CSV files.
- **Matrix Shuffling**: Shuffle matrix rows for preprocessing.
- **Basic Linear Regression**: Initial implementation of linear regression.

## Getting Started

### Prerequisites

- A C compiler (GCC recommended)
- CMake (for build automation)
- Git (for source code management)

### Building the Project

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/yourusername/mlfw.git
    cd mlfw
    ```

2. **Build with CMake**:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

3. **Run the Example**:
    ```bash
    ./mlfw_example
    ```

## Usage

### Matrix Operations

```c
#include <mlfw_matrix.h>

int main() {
    dimension_t rows = 3, columns = 3;
    mlfw_mat_double *matrix = mlfw_mat_double_create_new(rows, columns);
    if (matrix == NULL) {
        printf("Matrix creation failed.\n");
        return 1;
    }

    mlfw_mat_double_set(matrix, 0, 0, 1.0);
    printf("Element at (0,0): %lf\n", mlfw_mat_double_get(matrix, 0, 0));

    mlfw_mat_double_destroy(matrix);
    return 0;
}
```

### Vector Operations

```c
#include <mlfw_vector.h>

int main() {
    dimension_t size = 3;
    mlfw_column_vec_double *vector = mlfw_column_vec_double_create_new(size);
    if (vector == NULL) {
        printf("Vector creation failed.\n");
        return 1;
    }

    mlfw_column_vec_double_set(vector, 0, 1.0);
    printf("Element at 0: %lf\n", mlfw_column_vec_double_get(vector, 0));

    mlfw_column_vec_double_destroy(vector);
    return 0;
}
```

### Linear Regression Example

```c
#include <mlfw_matrix.h>
#include <mlfw_vector.h>
#include <mlfw_operations.h>

void train_it() {
    // Load dataset
    mlfw_mat_double *dataset = mlfw_mat_double_from_csv("dataset.csv");
    if (dataset == NULL) {
        printf("Unable to load dataset from CSV.\n");
        return;
    }

    // Further operations...
    mlfw_mat_double_destroy(dataset);
}

int main() {
    train_it();
    return 0;
}
```

## Future Plans

1. **Complete Linear Regression**: Finalize the linear regression module, including training and error evaluation.
2. **C++ Bindings**: Develop C++ bindings to provide a more intuitive and object-oriented interface for the framework.
3. **Additional Features**: Expand the framework to support more machine learning algorithms and numerical methods.

## Contributing

We welcome contributions to the MLFW project. Please check the [issues](https://github.com/RogueWarrior34/LeanML/issues) for existing tasks or submit your own feature requests.

### How to Contribute

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-xyz`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-xyz`).
5. Create a new Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE]([LICENSE](https://github.com/RogueWarrior34/Java-NetFramework-Library-/blob/main/LICENSE)) file for details.

## Acknowledgments

- Inspired by various numerical and machine learning libraries.

---
