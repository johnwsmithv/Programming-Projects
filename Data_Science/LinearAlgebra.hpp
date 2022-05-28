#include <iostream>
#include <vector>
#include <complex>
#include <chrono>
#include <omp.h>

#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP

class LinearAlgebra {
    public:
        LinearAlgebra();
        ~LinearAlgebra();

        void simpleSort(std::vector<int>& unsortedList);
        std::vector<std::complex<double>> matrixConjugate(std::vector<std::complex<double>> compleMatrix, const int rows, const int cols);
        
        template<class T>
        std::vector<T> transposeMatrix(const std::vector<T>& matrix, const int rows, const int cols, bool parallel) {
            std::vector<T> outputMat(rows * cols);
        #pragma omp parallel for collapse(2) if(parallel)
            for(int i = 0; i < rows; i++) {
                for(int j = 0; j < cols; j++) {
                    // std::cout << "Output " << j * rows + i << " | Input " << i * cols + j << "\n";
                    outputMat[j * rows + i] = matrix[i * cols + j];
                }
            }
            return outputMat;
        }

        template <class T>
        void multiplyMatrixByTransposedMatrix(const std::vector<T>& matrix1, const std::vector<T>& tranposedMatrix, std::vector<T> &output, const int rows, const int cols, const int numOperations, bool parallel) {
        #pragma omp parallel for collapse(3) if(parallel)
            for(int i = 0; i < rows; i++) {
                // std::cout << "Row: " << i << "\n";
                for(int j = 0; j < cols; j++) {
                    for(int k = 0; k < numOperations; k++) {
                        // std::cout << "MatA * transposedA | (" << i * cols + j << "): (" << i * numOperations + k << ", " << j * numOperations + k << ")\n"; 
                        output[i * cols + j] += matrix1[i * numOperations + k] * tranposedMatrix[j * numOperations + k];
                    }
                    // std::cout << "\n";
                }
                // std::cout << "\n";
            }
        }

        /**
         * @brief This is the school-book algorithm for matrix-multiplication
         * 
         * @param matrixA 
         * @param matrixB 
         * @param matrixC 
         * @param matrixARows 
         * @param matrixACols 
         * @param matrixBRows 
         * @param matrixBCols 
         * @param parallel 
         */
        template<class T>
        void schoolBookMatrixMultiply(const std::vector<T>& matrixA, const std::vector<T>& matrixB, std::vector<T>& matrixC, int matrixARows, int matrixACols, int matrixBRows, int matrixBCols, bool parallel) {
            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        #pragma omp parallel for collapse(3) if(parallel)
            for(int i = 0; i < matrixARows; i++) {
                for(int j = 0; j < matrixBCols; j++) {
                    for(int k = 0; k < matrixACols; k++) {
                        matrixC[i * matrixARows + j] += matrixA[i * matrixACols + k] * matrixB[k * matrixBCols + j];
                    }
                }
            }
            
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> finalTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
            if(parallel) {
                std::cout << "Schoolbook Parallel: To multiply (" << matrixARows << ", " << matrixACols << ") * (" << matrixBRows << ", " << matrixBCols << ") it took " << finalTime.count() << " seconds!\n";
            } else {
                std::cout << "Schoolbook Standard: To multiply (" << matrixARows << ", " << matrixACols << ") * (" << matrixBRows << ", " << matrixBCols << ") it took " << finalTime.count() << " seconds!\n";
            }
        }
        
        /**
         * @brief This function will fill in a matrix with random values b/w 0 and 999
         * 
         * @param matrix A Matrix that is going to be filled in
         * @param rows The number of rows in a matrix
         * @param cols The number of cols in a matrix
         */
        template <class T>
        void fillMatrix(std::vector<T> &matrix, const int rows, const int cols, const int maxValue, bool parallel) {
        #pragma omp parallel for if(parallel)
            for(int i = 0; i < rows * cols; i++) {
                matrix[i] = rand() % maxValue;
            }
        }

        /**
         * @brief A function to print an array out
         * 
         * @param image The image that is going to be printed out
         * @param rows Rows
         * @param cols Cols
         */
        template<class T>
        void printImage(std::vector<T> image, const int rows, const int cols) {
            std::cout << "\n";
            for(int i = 0; i < rows * cols; i++) {
                if(i % cols == 0) { // Left Side
                    std::cout << "| ";
                } 

                if(image[i] < 10) {
                    std::cout << image[i] << "   ";
                } else if(image[i] < 100) {
                    std::cout << image[i] << "  ";
                } else {
                    std::cout << image[i] << " ";
                }
                
                if(i % cols == (cols - 1)) { // Right Side
                    std::cout << " |\n";
                }
            }
        }

        // struct Stopwatch {
        //     std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        // } typedef struct Stopwatch;
};

#endif