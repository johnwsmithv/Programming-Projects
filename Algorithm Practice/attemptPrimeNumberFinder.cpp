#include <vector>
#include <iostream>
#include <Windows.h>
#include <omp.h>

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

/**
 * The point of this function is to find the prime numbers from 2 to n
 * 
 */ 
std::vector<long long> primeNumberFinder(int primeSearchMax){
    std::vector<long long> primeNumbers;
    for(int i = 2; i < primeSearchMax; i++){
        for(int j = 1; j <= i / 2; j++){
            if((i % j == 0) && j != 1){
                break;
            }
            else if(j == i / 2){
                primeNumbers.insert(primeNumbers.end(), i);
            }
        }
    }
    return primeNumbers;
}

std::vector<long long> primeNumberFinderOMP(int primeSearchMax){
    int i;
    int j;
    std::vector<long long> primeNumbers;
#pragma omp parallel for default(none) shared(primeSearchMax, primeNumbers) private(i, j)
    for(i = 2; i < primeSearchMax; i++){
        for(j = 1; j <= i / 2; j++){
            if((i % j == 0) && j != 1){
                break;
            }
            else if(j == i / 2){
                primeNumbers.insert(primeNumbers.end(), i);
            }
        }
    }
    return primeNumbers;
}

int main(){
    int primeNumberMax;
    std::cout << "Enter a number that you want to find prime numbers up to: ";
    std::cin >> primeNumberMax;
    long double start = PerformanceCounter();
    // std::vector<long long> primes = primeNumberFinder(primeNumberMax);
    std::vector<long long> primes = primeNumberFinderOMP(primeNumberMax);
    long double finish = PerformanceCounter();
    long double frequency = PerformanceFrequency();

    long double elapsedTime = ((finish - start)) / frequency;
    for(int i = 0; i < primes.size(); i++){
        std::cout << primes[i] << " ";
        if(i % 10 == 0){
            std::cout << "\n";
        }
    }
    std::cout << "\nFinding the number of prime numbers took: " << elapsedTime << " seconds.\n";
}