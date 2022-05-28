#include <vector>
#include <stdlib.h>
#include <chrono>
#include <omp.h>
#include <iostream>
#include <string>
#include <vector>

void transposeMatrix(std::vector<int> in, std::vector<int> &out, int rows, int cols) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            // out[]
        }
    }
}

void printMatrix(std::vector<int> matrix, int rows, int cols) {
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++) {
            std::cout << matrix[i * cols + j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

/**
 * @brief This function will fill in a matrix with random values b/w 0 and 999
 * 
 * @param matrix A Matrix that is going to be filled in
 * @param rows The number of rows in a matrix
 * @param cols The number of cols in a matrix
 */
void fillMatrix(std::vector<int> &matrix, int rows, int cols) {
    for(int i = 0; i < rows * cols; i++) {
        matrix[i] = rand() % 1000;
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
void schoolBookMatrixMultiply(std::vector<int> matrixA, std::vector<int> matrixB, std::vector<int>& matrixC, int matrixARows, int matrixACols, int matrixBRows, int matrixBCols, bool parallel) {
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
 * @brief This function will multiply two matrices as fast as possible
 * 
 * @param matrixA The vector which contains all of the elements in Matrix A
 * @param matrixB The vector which contains all of the elements in Matrix B
 * @param matrixC The vector whill will be the result of the multiplication of Matrix A and B
 * @param matrixARows The # of Rows in Matrix A
 * @param matrixACols The # of Cols in Matrix A
 * @param matrixBRows The # of Rows in Matrix B
 * @param matrixBCols The # of Cols in Matrix B
 * @param parallel Are we going to be running OpenMP or not?
 * 
 * TODO: Attempt to simplify... right now, it is slower than the school book algo threaded. We want to see if we can simplify the checks, reducing branch prediciton; right now it crashes when it is running in parallel for some reason
 * https://stackoverflow.com/questions/11227809/why-is-processing-a-sorted-array-faster-than-processing-an-unsorted-array
 */
void matrixMultiply(std::vector<int> matrixA, std::vector<int> matrixB, std::vector<int>& matrixC, int matrixARows, int matrixACols, int matrixBRows, int matrixBCols, bool parallel) {
    int numOperations = 0;
    int aIterator = 0;
    int bIterator = 0;
    int currentARow = 0;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for if(parallel)    
    for(int outVector = 0; outVector < matrixARows * matrixBCols; outVector++) {
        bIterator = outVector % matrixBCols;
        for(int multiplications = 0; multiplications < matrixACols; multiplications++){
            matrixC[outVector] += matrixA[aIterator++] * matrixB[bIterator];
            bIterator += matrixBCols;
            numOperations++;
        }
        // This if-statement means that we finished one single row of matrix multiplications
        if(numOperations % (matrixARows * matrixBCols) == 0){
            currentARow++;
            bIterator = 0;
        }
        // If we have gone through all of the columns, then we want to make sure we are on the right "row", even though these values are sequentially allocated
        if(aIterator % matrixACols == 0){
            aIterator = currentARow * matrixACols;
        }
    }
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> finalTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    if(parallel) {
        std::cout << "Parallel: To multiply (" << matrixARows << ", " << matrixACols << ") * (" << matrixBRows << ", " << matrixBCols << ") it took " << finalTime.count() << " seconds!\n";
    } else {
        std::cout << "Standard: To multiply (" << matrixARows << ", " << matrixACols << ") * (" << matrixBRows << ", " << matrixBCols << ") it took " << finalTime.count() << " seconds!\n";
    }
}

int main(int argc, char *argv[]) {
    // We need to have the user 
    if(argc != 5) {
        exit(1);
    }
    int matrixARows = std::stod(argv[1]);
    int matrixACols = std::stod(argv[2]);
    int matrixBRows = std::stod(argv[3]);
    int matrixBCols = std::stod(argv[4]);

    // We now need to ensure the inner values are the same or else matrix multiplication will not be possible
    if(matrixACols != matrixBRows) {
        std::cout << "Matrix A Columns and Matrix B Rows need to be the same value for matrix multiplication to work!\n";
    }
    
    std::vector<int> matrixA(matrixARows * matrixACols);
    fillMatrix(matrixA, matrixARows, matrixACols);
    std::vector<int> matrixB(matrixBRows * matrixBCols);
    fillMatrix(matrixB, matrixBRows, matrixBCols);
    // std::vector<int> matrixC(matrixARows * matrixBCols);

    // Standard non-threaded matrix multiplication
    // matrixMultiply(matrixA, matrixB, matrixC, matrixARows, matrixACols, matrixBRows, matrixBCols, false);
    
    // std::vector<int> matrixCSchoolbook(matrixARows * matrixBCols);
    std::vector<int> matrixCSchoolbookThreaded(matrixARows * matrixBCols);
    std::cout << "Done allocating memory! Matrix Multiplication time!\n";
    
    // schoolBookMatrixMultiply(matrixA, matrixB, matrixCSchoolbook, matrixARows, matrixACols, matrixBRows, matrixBCols, false);
    schoolBookMatrixMultiply(matrixA, matrixB, matrixCSchoolbookThreaded, matrixARows, matrixACols, matrixBRows, matrixBCols, true);

    // printMatrix(matrixA, matrixARows, matrixACols);
    // std::cout << "x\n";
    // printMatrix(matrixB, matrixBRows, matrixBCols);
    // printMatrix(matrixCSchoolbook, matrixARows, matrixBCols);
    // printMatrix(matrixCSchoolbookThreaded, matrixARows, matrixBCols);

    std::cout << "Thanks for running this program!\n";
}
