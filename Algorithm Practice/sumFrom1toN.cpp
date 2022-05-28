#include <iostream>

int main(int argc, char ** argv) {
    if(argc != 2) {
        std::cout << "Enter one number.\n";
        exit(1);
    }
    long long numberN = std::atoll(argv[1]);
    long long finalSum = (numberN * (numberN + 1)) / 2;
    std::cout << "The sum from 1 to " << numberN << " is " << finalSum << "!\n";

    return 1;
}