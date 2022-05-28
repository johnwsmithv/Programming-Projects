#include <iostream>
#include <vector>
#include <png.h>

png_infop pngInfoPtr;
png_bytepp rowPointers;
png_structp png_ptr;

void readPng(std::string fileName, uint32_t &width, uint32_t &height, int &bit_depth, int &color_type, int &interlace_type, int &compressionMethod, int &filterMethod) {
    FILE *pngFile = fopen(fileName.c_str(), "rb");
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    pngInfoPtr = png_create_info_struct(png_ptr);  
    png_init_io(png_ptr, pngFile);
    png_read_png(png_ptr, pngInfoPtr, PNG_TRANSFORM_IDENTITY, NULL);
    rowPointers = png_get_rows(png_ptr, pngInfoPtr);
    png_get_IHDR(png_ptr, pngInfoPtr, static_cast<png_uint_32 *>(&width), static_cast<png_uint_32 *>(&height), &bit_depth, &color_type, &interlace_type, &compressionMethod, &filterMethod);
    png_destroy_read_struct(&png_ptr, NULL, NULL); 
    fclose(pngFile);
}

/**
 * @brief A function to print an array out
 * 
 * @param image The image that is going to be printed out
 * @param rows Rows
 * @param cols Cols
 */
void printImage(std::vector<double> image, int rows, int cols) {
    std::cout << "\n";
    for(int i = 0; i < rows * cols; i++) {
        if(i % cols == 0) { // Left Side
            std::cout << "| ";
        } 

        if(image[i] < 10) {
            std::cout << image[i] << "   ";
        } else if(image[i] < 100) {
            std::cout << image[i] << "  ";
        } else {
            std::cout << image[i] << " ";
        }
        
        if(i % cols == (cols - 1)) { // Right Side
            std::cout << " |\n";
        }
    }
}

/**
 * @brief This function is going to add one layer of padding around any size image
 * 
 * @param paddedImage 
 * @param origImage 
 * @param origRows 
 * @param origCols 
 */
void padImage(std::vector<double> &paddedImage, std::vector<double> origImage, int origRows, int origCols) {
    int origImgElemCounter = 0;
    for(int i = 0; i < paddedImage.size(); i++) {
        // This means we are on the last row of the padded image which needs to be all zeros
        if(origImgElemCounter >= origRows * origCols || i < (origCols + 2)) {
            paddedImage[i] = 0;
        } else if(i % (origCols + 2) == 0 || i % (origCols + 2) == origCols + 1){ // This means we are on an edge
            paddedImage[i] = 0;
        } else {
            paddedImage[i] = origImage[origImgElemCounter++];
        }
    }
}

void fillChannelsFromPng(uint32_t width, uint32_t height, std::vector<double> &redChannel, std::vector<double> &greenChannel, std::vector<double> &blueChannel, std::vector<double> &alphaChannel) {
    for(int row = 0; row < height; row++){
        for(int col = 0; col < 3 * width; col += 3) {
            long long index = row * width + col;
            redChannel[index]   = rowPointers[row][col];
            greenChannel[index] = rowPointers[row][col + 1];
            blueChannel[index]  = rowPointers[row][col + 2];
            // alphaChannel[index] = rowPointers[row][col + 3];
        }
    }
}

void fillPngRowPointer(uint32_t width, uint32_t height, std::vector<double> redChannel, std::vector<double> greenChannel, std::vector<double> blueChannel, std::vector<double> alphaChannel) {
     for(int row = 0; row < height; row++){
        for(int col = 0; col < 3 * width; col += 3) {
            long long index = row * width + col;
            rowPointers[row][col]     = redChannel[index];
            rowPointers[row][col + 1] = greenChannel[index];
            rowPointers[row][col + 2] = blueChannel[index];
            // rowPointers[row][col + 3] = alphaChannel[index];
        }
    }   
}

/**
 * @brief This function is going to fill the image elements with values which will be from 0 to 255
 * 
 * @param image A reference to the vector that we are going to be filling
 * @param rows The number of rows in the image
 * @param cols The number of cols in the image
 */
void fillImage(std::vector<double> &image, int rows, int cols) {
    // Since we are modeling essentially going through and making an image, we want values from 0 to 255
    for(int i = 0; i < rows * cols; i++){
        image[i] = rand() % 256;
    }
}

void twoDimConv(std::vector<double> &convImage, std::vector<double> paddedImage, std::vector<double> kernel, int outRows, int outCols, int kernelCols) {
    for(int i = 0; i < outRows * outCols; i++){
        int kernelRow = 0;
        for(int kernelElement = 0; kernelElement < kernel.size(); kernelElement++) {
            if(kernelElement % kernelCols == 0 && kernelElement != 0){
                kernelRow++;
            } 
            int padImgElem = kernelRow * (outCols + 2) + (kernelElement % kernelCols) + i;
            convImage[i] += kernel[kernelElement] * paddedImage[padImgElem];

            // std::cout << "Kernel Elem[" << kernelElement << "] = " << kernel[kernelElement]  << " * padding element[" << padImgElem << "] = " << paddedImage[padImgElem] << " = " << convImage[i] << "\n";
        }
    }
}

int main() {
    // The Gauss filter is going to be laid out in 1D, but it is actually a three by three
    int origRows = 128;
    int origCols = 128;
    //                                 0.0625    0.125      0.0625   0.125    0.250     0.125      0.0625    0.125    0.0625
    std::vector<double> gaussFilter = {1 / 16.0, 2 / 16.0, 1 / 16.0, 2 / 16.0, 4 / 16.0, 2 / 16.0, 1 / 16.0, 2 / 16.0, 1 / 16.0};
    std::vector<double> image(origRows * origCols);
    std::vector<double> convImage(origRows * origCols);
    // We are defining the padded image as (N + 1) * (N + 1)
    std::vector<double> paddedImage((origRows + 2) * (origCols + 2));
    fillImage(image, origRows, origCols);
    // printImage(image, origRows, origCols);
    
    padImage(paddedImage, image, origRows, origCols);
    // printImage(paddedImage, origRows + 2, origCols + 2);
    // The goal here is to make sure that if we are going to convolve a gaussian filter across an image, we want to ensure 
    // that the image is the same size; since the kernel is 3 x 3, we want to add padding around
    twoDimConv(convImage, paddedImage, gaussFilter, origRows, origCols, 3);
    // printImage(convImage, origRows, origCols);

    uint32_t width;
    uint32_t height; 
    int bitDepth, colorType, interlaceType, compressionMethod, filterMethod; 
    readPng("Images/woman_original.png", width, height, bitDepth, colorType, interlaceType, compressionMethod, filterMethod);
    // Since the color type is RGBA, we need four buffer
    // int pngWidth = static_cast<int>(*width);
    // int pngHeight = static_cast<int>(*height);
    std::cout << "The image has been read in!\n";

    // The Vectors which are going to contain the original image data
    std::vector<double> redChannel(width * height);
    std::vector<double> greenChannel(width * height);
    std::vector<double> blueChannel(width * height);
    std::vector<double> alphaChannel(width * height);
    fillChannelsFromPng(width, height, redChannel, greenChannel, blueChannel, alphaChannel);
    std::cout << "All of the channels have been formatted into their own separate arrays.\n";

    // The vectors which are going to be padded
    std::vector<double> redChannelPadded((width + 2) * (height + 2));
    std::vector<double> greenChannelPadded((width + 2) * (height + 2));
    std::vector<double> blueChannelPadded((width + 2) * (height + 2));
    // std::vector<double> alphaChannelPadded((width + 2) * (height + 2));
    padImage(redChannelPadded, redChannel, height, width);
    padImage(greenChannelPadded, greenChannel, height, width);
    padImage(blueChannelPadded, blueChannel, height, width);
    // padImage(alphaChannelPadded, alphaChannel, height, width);
    std::cout << "All of the channels have been padded.\n";

    // These are the output vectors which are going to contain the convolved data
    std::vector<double> redChannelConv(width * height);
    std::vector<double> greenChannelConv(width * height);
    std::vector<double> blueChannelConv(width * height);
    std::vector<double> alphaChannelConv(width * height);
    
    twoDimConv(redChannelConv, redChannelPadded, gaussFilter, height, width, 3);
    std::cout << "The Red Channel has been convolved!\n";

    twoDimConv(greenChannelConv, greenChannelPadded, gaussFilter, height, width, 3);
    std::cout << "The Green Channel has been convolved!\n";

    twoDimConv(blueChannelConv, blueChannelPadded, gaussFilter, height, width, 3);
    std::cout << "The Blue Channel has been convolved!\n";
    
    // twoDimConv(alphaChannelConv, alphaChannelPadded, gaussFilter, height, width, 3);
    // std::cout << "The Alpha Channel has been convolved!\n";

    // We want to re-write the convolved data into the row pointers
    fillPngRowPointer(width, height, redChannelConv, greenChannelConv, blueChannelConv, alphaChannel);

    FILE *pngFileConv = fopen("woman_convoloved_3.png", "wb");
    png_structp png_ptr_write = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop pngInfoPtrConv = png_create_info_struct(png_ptr_write);  
    png_init_io(png_ptr_write, pngFileConv);
    png_set_IHDR(png_ptr_write, pngInfoPtrConv, static_cast<png_uint_32>(width), static_cast<png_uint_32>(height), bitDepth, colorType, interlaceType, compressionMethod, filterMethod);
    png_set_rows(png_ptr_write, pngInfoPtrConv, rowPointers);

    // png_write_image(png_ptr_write, rowPointers);
    png_write_png(png_ptr_write, pngInfoPtrConv, 0, NULL);

    fclose(pngFileConv);

    free(rowPointers);
    free(pngInfoPtr);
}