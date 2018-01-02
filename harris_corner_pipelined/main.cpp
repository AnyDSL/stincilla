#include <iostream>

#include <anydsl_runtime.hpp>

#include "pnm_image.h"

void displayFrame(float* frame, int stride, const int width, const int height, 
                  const int offset_x=0, const int offset_y=0){
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            printf("%15.2f", frame[(y+offset_y)*stride + offset_x + x]);
        }
        std::cout<<std::endl;
    } 
}

void displayFrame(int* frame, int stride, const int width, const int height, 
                  const int offset_x=0, const int offset_y=0){
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            std::cout<< int(frame[(y+offset_y)*stride + offset_x + x]) << " \t ";
        }
        std::cout<<std::endl;
    }	
}
void displayFrame(unsigned char* frame, int stride, const int width, const int height, 
                  const int offset_x=0, const int offset_y=0){
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            std::cout<< int(frame[(y+offset_y)*stride + offset_x + x]) << " \t ";
        }
        std::cout<<std::endl;
    }	
}

#define din_t  int
#define dout_t int
#define mask_t int
extern "C" void harris_corner_pipelined(din_t*, dout_t*);

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main(int argc, const char **argv) {
    size_t width  = 1024;
    size_t stride = 1024;
    size_t height = 1024;

    // host memory for image of width x height pixels
    // use anydsl::Array from AnyDSL runtime for memory allocation
    anydsl::Array<din_t>  input(width * height);
    anydsl::Array<dout_t> output(width * height);

    // initialize data
    for (size_t j = 0; j < height; ++j) {
        for (size_t i = 0; i < width; ++i) {
            //input[j * stride + i] = static_cast <din_t> (((((i%8)>=4) & ((j%8)<4)) | (((i%8)<4) & ((j%8)>=4))) ==0 ? 255 : 0);
            input[j * stride + i] = static_cast <din_t> ( ((((i%16)>=8) & ((j%16)<8)) | (((i%16)<8) & ((j%16)>=8))) ==0 ? 255.0f : 0.0f);
        }
    }

    harris_corner_pipelined(input.data(), output.data());

    // Print Output 
    int pOfX= 0; //width-20;
    int pOfY= 0; //height-10;
    printf("Input \n"); displayFrame(input.data(),  stride, 16, 16, pOfX, pOfY);
    printf("Output\n"); displayFrame(output.data(), stride, 16, 16, pOfX, pOfY);

    return EXIT_SUCCESS;
}

