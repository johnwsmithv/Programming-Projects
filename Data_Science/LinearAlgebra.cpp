#include "LinearAlgebra.hpp"

LinearAlgebra::LinearAlgebra() {};
LinearAlgebra::~LinearAlgebra() {};

std::vector<std::complex<double>> LinearAlgebra::matrixConjugate(std::vector<std::complex<double>> compleMatrix, const int rows, const int cols) {
    for(int i = 0; i < rows * cols; i++) {
        compleMatrix[i] = std::conj(compleMatrix[i]);
    }
    return compleMatrix;
}


// Say we had: 4, 2, 1, 3
//             2, 4, 1, 3
//             2, 1, 4, 3
//             2, 1, 3, 4
//             1, 2, 3, 4
// We would evaluate each index at once, and it would pull the largest number to the end 
void LinearAlgebra::simpleSort(std::vector<int>& unsortedList) {
    bool listUnordered = true;
    while(listUnordered) {
        bool allElementsOrdered = true;
        for(int index = 0; index < unsortedList.size() - 1; index++) {
            if(unsortedList[index] > unsortedList[index + 1]) {
                std::cout << "Index " << index << ": " << unsortedList[index] << " > " << "Index " << index + 1 << ": " << unsortedList[index + 1] << "\n";
                // Simply just swapping the values of the list
                int tempIndex = unsortedList[index + 1];
                unsortedList[index + 1] = unsortedList[index];
                unsortedList[index] = tempIndex;
                allElementsOrdered &= false;
            } else {
                allElementsOrdered &= true;
            }
        }
        if(allElementsOrdered) {
            listUnordered = false;
        }
    }
}

// Merge Sort is a divide-and-conquer algorithm
// Need to divide the list up into two-halves into two arrays, and then continue to work on them from there
void mergeSort(std::vector<int> unsortedArray) {
    // We first want to check if the size of the incoming array is odd
    int leftArrSize;
    int rightArrSize;
    if(unsortedArray.size() % 2 == 1) {
        leftArrSize = (unsortedArray.size() - 1) / 2;
        rightArrSize = leftArrSize + 1; 
    } else {
        leftArrSize = unsortedArray.size() / 2;
        rightArrSize = leftArrSize;
    }
    std::vector<int> leftHalf(unsortedArray.data(), unsortedArray.data() + leftArrSize);
    std::vector<int> rightHalf(unsortedArray.data() + leftArrSize, unsortedArray.data() + rightArrSize);

    // We are going to split the array up until we have two elements
    // TODO: We are going to want to separate the work by using multiple threads
    bool leftNotSorted = true;
    int iterator = 2;
    int leftPointer = 0;
    int rightPointer = 1;
    while(leftNotSorted) {
        for(int i = 0; i < leftHalf.size(); i+=iterator) {
            // We are doing this because if we were on block size 4:
            // left: 0 | right: 2 => We would then compare the indices and then combine them into a 4 block size
            int tempLeft = leftPointer;
            int tempRight = rightPointer;
            int tempVectorIterator = 0;
            std::vector<int> tempVector(iterator);
            // 5 4 | 3 1
            // 4 5 | 1 3
            // 4 > 1 => 1 (4 5 | 3)
            // 4 > 3 => 1 3 (4 5)
            // Then copy the remaining elements in
            for(int subIdx = 0; subIdx < iterator; subIdx++) {
                if(tempLeft < iterator - 1 && tempRight)
                if(leftHalf[tempLeft] > leftHalf[tempRight]) {
                    int temp = leftHalf[tempLeft];
                    leftHalf[tempLeft] = leftHalf[tempRight];
                    leftHalf[tempRight] = temp;
                }
                tempLeft += subIdx;
                tempRight += subIdx;
            }
            leftPointer += iterator;
            rightPointer += iterator;
        }
        // After one pass through the smallest elements will be sorted.. where we need to then go higher and higher
        iterator *= 2;
        // We are resetting the left/right pointers
        leftPointer = 0;
        rightPointer += (iterator / 2);
    }
    
}