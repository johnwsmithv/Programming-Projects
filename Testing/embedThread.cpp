#include <iostream>
#include <omp.h>
#include <thread>
#include <vector>
#include <math.h>

void embeddedOmpThread(std::vector<std::vector<double>>& buffer, const int matrix, const int rows, const int cols) {
#pragma omp parallel for num_threads(2)
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            buffer[matrix][i * cols + j] = std::sqrt(std::pow(3, 5));
        }
    }
}

int main() {
    const int rows = 1000;
    const int cols = 500000;
    // Two sub-matrices
    std::vector<std::vector<double>> buffer(4);
    // Allocating memory
    buffer[0] = std::vector<double>(rows * cols);
    buffer[1] = std::vector<double>(rows * cols);
    buffer[2] = std::vector<double>(rows * cols);
    buffer[3] = std::vector<double>(rows * cols);

    // omp_set_nested(1);
    std::vector<std::thread> vectorOfThreads(4);
    for(int i = 0; i < 4; i++) {
        std::thread tempThread(embeddedOmpThread, std::ref(buffer), i, rows, cols);
        vectorOfThreads.push_back(std::move(tempThread));
    }

    for(std::thread &th : vectorOfThreads) {
        if(th.joinable()) {
            th.join();
        }
    }
}