# LeanML: Lightweight Machine Learning Framework

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/RogueWarrior34/LeanML)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

## Overview

**LeanML** is a C-based library designed for efficient machine learning operations, focusing on matrix and vector computations. The framework includes robust implementations of linear regression, one-hot encoding, min-max scaling, and more. LeanML aims to provide a lightweight yet powerful toolkit for machine learning tasks with an emphasis on performance and ease of integration.

## Features

### Matrix Operations
- **Creation and Destruction**: Create and destroy matrices.
- **Element Access**: Get and set matrix elements.
- **CSV Handling**: Load matrices from CSV files and write matrices to CSV files.
- **Shuffling**: Shuffle matrix rows for data preprocessing.
- **Scaling**: Min-max scaling with methods to save and apply scaling parameters.
- **Statistical Operations**: Retrieve minimum and maximum values within a matrix.

### Vector Operations
- **Creation and Destruction**: Create and destroy row and column vectors.
- **Element Access**: Get and set vector elements.
- **CSV Handling**: Load vectors from CSV files and write vectors to CSV files.
- **Transpose**: Convert column vectors to row vectors and vice versa.

### Set Operations
- **String Sets**: Create, destroy, add to, and retrieve elements from string sets.

### Operations
- **Matrix-Vector Multiplication**: Multiply matrices by vectors.
- **Vector-Vector Operations**: Perform operations such as vector multiplication and subtraction.

### Linear Regression
- **Training**: Train linear regression models and generate parameters.
- **Testing**: Test models with generated parameters and predict values.
- **Interactive Application**: Predict new values using generated parameters interactively.
- **Performance Metrics**: Calculate R2 score from results.

### Data Transformation Tools
- **Encoding**: One-hot encoding for datasets containing string values.
- **Scaling**: Min-max scaling for training and testing datasets.
- **Dataset Splitting**: Create training and testing datasets from an original dataset.

## Directory Structure

```
LeanML/
├── lml-framework/
│   ├── include/
│   │   ├── encoder/
│   │   │   └── lml_data_encoder.h
│   │   ├── matrix/
│   │   │   ├── lml_mat_double.h
│   │   │   └── lml_mat_string.h
│   │   ├── operations/
│   │   │   └── lml_operations_double.h
│   │   ├── scale/
│   │   │   └── lml_scale_double.h
│   │   ├── set/
│   │   │   └── lml_set_string.h
│   │   ├── vector/
│   │   │   └── lml_vec_double.h
│   │   ├── lml_encoder.h
│   │   ├── lml_matrix.h
│   │   ├── lml_operations.h
│   │   ├── lml_scale.h
│   │   ├── lml_set.h
│   │   └── lml_vector.h
│   ├── lib/
│   │   └── liblml.a
│   ├── o_files/
│   └── testcases/
├── regression/
│   ├── linear/
│   │   ├── build/
│   │   │   ├── train_it (executable)
│   │   │   └── test_it (executable)
│   │   ├── src/
│   │   │   ├── train_it.c
│   │   │   └── test_it.c
│   │   └── datasets/
├── tools/
│   ├── build/
│   │   ├── create_test_train_dataset (executable)
│   │   ├── encode_dataset (executable)
│   │   ├── r2score (executable)
│   │   ├── scale_testing_dataset (executable)
│   │   └── scale_training_dataset (executable)
│   ├── src/
│   │   ├── create_test_train_dataset.c
│   │   ├── encode_dataset.c
│   │   ├── r2score.c
│   │   ├── scale_testing_dataset.c
│   │   └── scale_training_dataset.c
```

## Usage

### Data Transformation Tools

1. **Encode Dataset**:
    ```bash
    ./encode_dataset dataset_file_name encoded_dataset_file_name
    ```

2. **Create Training and Testing Datasets**:
    ```bash
    ./create_test_train_dataset dataset_file_name test_dataset_file_name train_dataset_file_name split_percentage
    ```

3. **Scale Training Dataset**:
    ```bash
    ./scale_training_dataset input_file_name output_file_name from_column to_column min_max_file
    ```

4. **Scale Testing Dataset**:
    ```bash
    ./scale_testing_dataset input_file_name output_file_name from_column to_column min_max_file
    ```

### Linear Regression

1. **Train Model**:
    ```bash
    ./train_it dataset_name learning_rate history_size history_file_name parameter_file_name graph_file_name number_of_iterations (optional)
    ```

2. **Test Model**:
    ```bash
    ./test_it dataset_name parameters_file_name results_file_name
    ```

3. **Calculate R2 Score**:
    ```bash
    ./r2score results_file_name
    ```

4. **Predict New Values**:
    - Use the provided interactive application for the IceCreamSales dataset:
        ```bash
        ./interactiveApp
        ```
    - You can create your own based on your needs by following the provided one as a guide.

## Future Plans

1. **Develop C++ Bindings**: Create C++ bindings for better usability and integration.
2. **Expand Operations**: Add more matrix and vector operations, such as matrix inversion, determinants, and advanced arithmetic functions.
3. **Additional Algorithms**: Implement more machine learning algorithms, including logistic regression, k-means clustering, and more.

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
