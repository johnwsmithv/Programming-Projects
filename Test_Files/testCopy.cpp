#include <vector>
#include <iostream>

int main () {
    // int blah[4] = {1, 2, 3, 4};
    std::vector<int> blah = {1, 2, 3, 4, 5};
    std::vector<int> twoElem = {7, 8};
    std::vector<int> leftBlah(blah.data(), blah.data() + 3);
    std::vector<int> rightBlah(blah.data() + 3, blah.data() + 5);

    std::cout << "Left Blah:\n";
    for(int i = 0; i < 3; i++) {
        std::cout << leftBlah[i] << " ";
    }
    std::cout << "\nRight Blah:\n";
    for(int i = 0; i < 2; i++) {
        std::cout << rightBlah[i] << " ";
    }
    std::cout << "\n";
}