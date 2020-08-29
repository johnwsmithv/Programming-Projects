#include <iostream>
#include <ostream>
#include <vector>
#include <cstdint>
#include "../library/uint256_t/uint256_t.h"

using namespace std;

// struct uint256_t{
//     std::uint64_t bits[4];
// };

int fibonacciSequenceRecursion(int n){
    if(n == 1){
        return 1;
    } else{
        return fibonacciSequenceRecursion(n - 1) + fibonacciSequenceRecursion(n - 2);
    }
}

unsigned long long memoizedFibonaci(uint256_t n){
    vector<uint256_t> fibSeq = {0, 1};
    for(int i = 2; i < n; i++){
        fibSeq.push_back(fibSeq[i - 1] + fibSeq[i - 2]);
        std::cout << fibSeq[i] << " ";
    }
    std::cout << "\n";
    return fibSeq[n - 1];
}

int main(){
    int userInput;
    std::cout << "Here is the fibonacci sequence using memoization\n";
    std::cin >> userInput;
    unsigned long long fibNum = memoizedFibonaci(userInput);
    cout << "Here is Fib #" << userInput << ": " << fibNum << "\n";
}