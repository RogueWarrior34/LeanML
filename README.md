Sure, I can expand the `README.md` to include detailed descriptions and examples of various matrix and vector functions. This will help users understand how to utilize the full range of capabilities provided by your framework.

Here’s the updated `README.md` with enhanced documentation:

---

# LeanML: Lightweight Machine Learning Framework

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/RogueWarrior34/LeanML)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Overview

**LeanML** is a C-based library designed for efficient machine learning operations, focusing on matrix and vector computations. This framework is in active development, with initial implementations targeting linear regression. Future updates will include C++ bindings for improved usability and integration.

## Features

- **Matrix Operations**: Create, manipulate, and manage matrices.
- **Vector Operations**: Support row and column vectors with various operations.
- **Data Loading**: Load data from CSV files into matrices.
- **Shuffling**: Shuffle matrix rows for data preprocessing.
- **Basic Linear Regression**: Implementation of core linear regression components.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC)
- CMake (for build automation)
- Git (for source code management)

### Building the Project

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/RogueWarrior34/LeanML
    cd leanml
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
    ./leanml_example
    ```

## Usage

### Matrix Operations

#### Creation and Destruction

- **Create a Matrix**:
    ```c
    #include <mlfw_matrix.h>

    mlfw_mat_double *matrix = mlfw_mat_double_create_new(3, 3);
    if (matrix == NULL) {
        printf("Matrix creation failed.\n");
    }
    ```

- **Destroy a Matrix**:
    ```c
    mlfw_mat_double_destroy(matrix);
    ```

#### Accessing Elements

- **Get and Set Matrix Elements**:
    ```c
    mlfw_mat_double_set(matrix, 0, 0, 1.0);
    double value = mlfw_mat_double_get(matrix, 0, 0);
    printf("Element at (0,0): %lf\n", value);
    ```

#### Matrix from CSV

- **Load a Matrix from a CSV File**:
    ```c
    mlfw_mat_double *matrix = mlfw_mat_double_from_csv("data.csv");
    if (matrix == NULL) {
        printf("Failed to load matrix from CSV.\n");
    }
    ```

#### Shuffling

- **Shuffle Rows of a Matrix**:
    ```c
    mlfw_mat_double *shuffled = mlfw_mat_double_shuffle(matrix, 3);
    ```

#### Matrix to CSV

- **Write Matrix to a CSV File**:
    ```c
    mlfw_mat_double_to_csv(matrix, "output.csv");
    ```

### Vector Operations

#### Creation and Destruction

- **Create a Column Vector**:
    ```c
    #include <mlfw_vector.h>

    mlfw_column_vec_double *vector = mlfw_column_vec_double_create_new(3);
    ```

- **Destroy a Column Vector**:
    ```c
    mlfw_column_vec_double_destroy(vector);
    ```

#### Accessing Elements

- **Get and Set Vector Elements**:
    ```c
    mlfw_column_vec_double_set(vector, 0, 2.0);
    double value = mlfw_column_vec_double_get(vector, 0);
    printf("Element at index 0: %lf\n", value);
    ```

#### Vector Transpose

- **Transpose Column Vector to Row Vector**:
    ```c
    mlfw_row_vec_double *row_vector = mlfw_column_vec_double_transpose(vector);
    ```

### Operations

#### Matrix-Vector Multiplication

- **Multiply Matrix by Column Vector**:
    ```c
    mlfw_column_vec_double *result = mlfw_mult_double_mat_cvec(matrix, vector);
    ```

#### Vector-Vector Operations

- **Multiply Row Vector by Column Vector**:
    ```c
    mlfw_column_vec_double *product = mlfw_mult_double_rvec_cvec(row_vector, vector);
    ```

- **Subtract Column Vectors**:
    ```c
    mlfw_column_vec_double *difference = mlfw_subtract_double_column_vec(vector1, vector2);
    ```

### Linear Regression Example

Here’s an example of using LeanML for linear regression:

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

    // Prepare matrices and vectors
    dimension_t datasetRows, datasetColumns;
    mlfw_mat_double_get_dimensions(dataset, &datasetRows, &datasetColumns);

    mlfw_mat_double *I = mlfw_mat_double_create_new(datasetRows, datasetColumns);
    mlfw_mat_double_copy(I, dataset, 0, 1, 0, 0, datasetRows - 1, datasetColumns - 1);
    mlfw_mat_double_fill(I, 0, 0, datasetRows - 1, 0, 1.0);

    mlfw_column_vec_double *A = mlfw_mat_double_create_column_vec(dataset, 1);
    mlfw_column_vec_double *M = mlfw_column_vec_double_create_new_filled(datasetColumns, 0.0);

    // Perform operations
    mlfw_column_vec_double *P = mlfw_mult_double_mat_cvec(I, M);
    mlfw_column_vec_double *E = mlfw_subtract_double_column_vec(P, A);

    mlfw_row_vec_double *ET = mlfw_column_vec_double_transpose(E);
    mlfw_column_vec_double *sum = mlfw_mult_double_rvec_cvec(ET, E);

    double squared_sum = mlfw_column_vec_double_get(sum, 0);
    double finalErrorValue = squared_sum / datasetRows;
    printf("Final Error Value: %20.10lf\n", finalErrorValue);

    // Release resources
    mlfw_column_vec_double_destroy(A);
    mlfw_column_vec_double_destroy(M);
    mlfw_column_vec_double_destroy(P);
    mlfw_column_vec_double_destroy(E);
    mlfw_row_vec_double_destroy(ET);
    mlfw_column_vec_double_destroy(sum);
    mlfw_mat_double_destroy(I);
    mlfw_mat_double_destroy(dataset);
}

int main() {
    train_it();
    return 0;
}
```

## Future Plans

1. **Complete Linear Regression**: Enhance linear regression with training loops and optimization techniques like gradient descent.
2. **Develop C++ Bindings**: Create C++ bindings for a more user-friendly interface and integration with C++ projects.
3. **Expand Operations**: Add more matrix and vector operations, such as matrix inversion, determinants, and advanced arithmetic functions.
4. **Additional Algorithms**: Implement more machine learning algorithms, including logistic regression, k-means clustering, and more.

## Contributing

Contributions are welcome! If you have suggestions, bug fixes, or new features, please open an issue or submit a pull request.

### How to Contribute

1. **Fork the Repository**:
    ```bash
    git fork https://github.com/RogueWarrior34/LeanML.git
    ```

2. **Create a Branch**:
    ```bash
    git checkout -b feature-name
    ```

3. **Commit Your Changes**:
    ```bash
    git commit -m 'Add new feature'
    ```

4. **Push to the Branch**:
    ```bash
    git push origin feature-name
    ```

5. **Open a Pull Request**:
    - Navigate to the repository on GitHub and create a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by various numerical and machine learning libraries.

---

This `README.md` should now provide comprehensive guidance on the current features and usage of your LeanML framework, while also setting the stage for future development, including C++ bindings and additional machine learning capabilities.
