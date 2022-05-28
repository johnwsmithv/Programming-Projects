#include <iostream>
#include <vector>

int main() {
    std::vector<float> kernel = {1/3.0, 1/3.0, 1/3.0};
    std::vector<float> oneDimImage = {10, 50, 60, 10, 20, 30, 40};
    std::vector<float> convolutionResult(oneDimImage.size());

    std::cout << "[";
    for(int i = 0; i < convolutionResult.size(); i++){
        int imagePos = i - 1;
        for(int kernelPos = 0; kernelPos < kernel.size(); kernelPos++) {
            if(imagePos >= 0 && imagePos <= convolutionResult.size()) {
                convolutionResult[i] += kernel[kernelPos] * oneDimImage[imagePos];
            }
            imagePos++;
        }
        i == convolutionResult.size() - 1 ?  std::cout << convolutionResult[i] << "]\n" : std::cout << convolutionResult[i] << ", ";
    }

}