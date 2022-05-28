#include "LinearAlgebra.hpp"

void printList(std::vector<int> list) {
    std::cout << "| ";
    for(int i = 0; i < list.size(); i++) {
        if(i == list.size() - 1) {
            std::cout << list[i] << "|\n";
        } else {
            std::cout << list[i] << ", ";
        }
    }
}

int main() {
    LinearAlgebra * linAlg = new LinearAlgebra;

    // std::vector<int> unorderedList = {4, 4, 2, 3, 1};
    std::vector<int> unorderedList(100);
    linAlg->fillMatrix(unorderedList, 20, 5, 100, false);

    printList(unorderedList);

    linAlg->simpleSort(unorderedList);
    printList(unorderedList);

    delete linAlg;
}