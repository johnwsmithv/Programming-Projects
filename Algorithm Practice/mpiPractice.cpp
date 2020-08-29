#include <omp.h>
#include <chrono>
#include <iostream>
#include <ctime>
#include <sys/timeb.h>
#include <Windows.h>
// #include <boost/chrono.hpp>

// int *singlePointerPractice(){
    
// }

inline long double PerformanceCounter() noexcept
{
    LARGE_INTEGER li;
    ::QueryPerformanceCounter(&li);
    return li.QuadPart;
}

inline long double PerformanceFrequency() noexcept
{
    LARGE_INTEGER li;
    ::QueryPerformanceFrequency(&li);
    return li.QuadPart;
}

int main(int argc, char * argv[]){
    const int rows = atoi(argv[1]);
    const int cols = atoi(argv[2]);
    int counter = 0;
    
    // Alllocating memeory to the two-2D arrays
    long **openMpMatrix = (long **)malloc(rows * sizeof(long *));
    long **regularMatrix = (long **)malloc(rows * sizeof(long *));
    for(long i = 0; i < rows; i++){
        openMpMatrix[i] = (long *)malloc(cols * sizeof(long));
        regularMatrix[i] = (long *)malloc(cols * sizeof(long));
    }

    // Time for the regular loop to fill the Matrix
    // auto start = std::chrono::high_resolution_clock::now();
    long double start = PerformanceCounter();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            regularMatrix[i][j] = counter++;
            // std::cout << regularMatrix[i][j] << " ";
        }
        counter = i + 1;
        // std::cout << "\n";
    }
    long double finish = PerformanceCounter();

    // auto finish = std::chrono::high_resolution_clock::now();

    // auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(finish - start).count();
    long double frequency = PerformanceFrequency();

    long double elapsedTime = ((finish - start)) / frequency;

    std::cout << "The Elasped time for the OpenMP loop was: " << elapsedTime << "\n";
}