#include "LinearAlgebra.hpp"

int main(int argc, char *argv[]) {
    int matrixARows = std::stod(argv[1]);
    int matrixACols = std::stod(argv[2]);
    int matrixBRows = std::stod(argv[3]);
    int matrixBCols = std::stod(argv[4]);

    LinearAlgebra * linAlg = new LinearAlgebra;

    std::vector<double> transposeMat(matrixBRows * matrixBCols);
    std::vector<double> matrixA(matrixARows * matrixACols);
    std::vector<double> matrixB(matrixBRows * matrixBCols);

    linAlg->fillMatrix(matrixA, matrixARows, matrixACols, 20, false);
    std::cout << "Matrix A filled in.\n";
    linAlg->fillMatrix(matrixB, matrixBRows, matrixBCols, 20, false);
    std::cout << "Matrix B filled in.\n";

    // linAlg->printImage<double>(matrixA, matrixARows, matrixACols);
    // linAlg->printImage<double>(matrixB, matrixBRows, matrixBCols);
    // linAlg->printImage<double>(transposeMat, matrixBCols, matrixBRows);

    std::vector<double> outputMatrix(matrixARows * matrixBCols);
    
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    transposeMat = linAlg->transposeMatrix<double>(matrixB, matrixBRows, matrixBCols, true);
    linAlg->multiplyMatrixByTransposedMatrix<double>(matrixA, transposeMat, outputMatrix, matrixARows, matrixBCols, matrixACols, true);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> finalTime = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    std::cout << "Tranposed Matrix Multiplication (" << matrixARows << ", " << matrixACols << ") * (" << matrixBRows << ", " << matrixBCols << ") it took " << finalTime.count() << " seconds!\n";

    linAlg->schoolBookMatrixMultiply(matrixA, matrixB, outputMatrix, matrixARows, matrixACols, matrixBRows, matrixBCols, true);
    // linAlg->printImage<double>(outputMatrix, matrixARows, matrixBCols);

    delete linAlg;
    exit(0);
}