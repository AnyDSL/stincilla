#include <iostream>
#include <vector>

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <typeinfo>

// variables set by Makefile
#define SIZE_X 5 
#define SIZE_Y 5 
#define WIDTH  1024 
#define HEIGHT 1024 
#define BORDER_HANDLING_TYPE BorderPadding::BORDER_UNDEFINED

//#define AVARAGE_FILTER

#include "conf.h"
//typedef int din_t; 
//typedef int dout_t;
//typedef int mask_t;
// Gaussian filter in HIPAcc


/*************************************************************************
 * Hardware Prototype 
 *************************************************************************/
void hardware_top(din_t _133026_142194[1024*1024], dout_t _133027_142195[1024*1024]);

/*************************************************************************
 * Test Functions 
 *************************************************************************/
struct BorderPadding 
{
public:
    enum values {
    	BORDER_UNDEFINED,
    	BORDER_CONST,
    	BORDER_CLAMP,
    	BORDER_MIRROR,
    	BORDER_MIRROR_101
    };

    typedef void isBorderMode;
};

template<typename inT>
inT getPixel(inT* in, int &cx, int &cy, const int width, const int height,
      enum BorderPadding::values borderMode, inT constVar= 32) {
  if(borderMode==BorderPadding::BORDER_CLAMP){                                
    cx = cx < 0 ? 0 : cx;
    cx = cx > width-1 ? width-1 : cx;
    cy = cy < 0 ? 0 : cy;
    cy = cy > height-1 ? height-1 : cy;
  }
  else if(borderMode==BorderPadding::BORDER_MIRROR){                               
    cx = cx < 0 ? -cx-1 : cx;
    cx = cx > width-1 ? (width-1)-(cx-width) : cx;
    cy = cy < 0 ? -cy-1 : cy;
    cy = cy > height-1 ? (height-1)-(cy-height) : cy;
  }
  else if(borderMode==BorderPadding::BORDER_MIRROR_101){                           
    cx = cx < 0 ? -cx : cx;
    cx = cx > width-1 ? (width-1)-(cx-width)-1 : cx;
    cy = cy < 0 ? -cy : cy;
    cy = cy > height-1 ? (height-1)-(cy-height)-1 : cy;
  }
  else if(borderMode==BorderPadding::BORDER_CONST){
    bool boundaryF = (cx < 0 || cx > width-1 || cy<0 || cy>height-1 ) ? 1 : 0;
    inT val = boundaryF ? constVar : in[cy*width + cx];
    return val;
  }
  return in[cy * width + cx];
}

template<typename outT, typename inT, typename filtT>
void local_op(outT *out, const inT *in, const filtT *filter, 
      int size_x, int size_y, int width, int height, 
      enum BorderPadding::values borderMode) {
    inT constVar = 0;
    int anchor_x = 0;
    int anchor_y = 0;
    int upper_x = width  - anchor_x;
    int upper_y = height - anchor_y;

    filtT normalize = 0; 
    for(int i = 0; i < size_y * size_x; i++) normalize += filter[i];
    
    for (int y=anchor_y; y<upper_y; ++y) {
      for (int x=anchor_x; x<upper_x; ++x) {
        outT sum = 0;
        for (int yf = -size_y/2; yf<=size_y/2; ++yf) {
          for (int xf = -size_x/2; xf<=size_x/2; ++xf) {
            int cx = x + xf; int cy = y + yf;
            sum += filter[(yf+size_y/2)*size_x + xf+size_x/2] * getPixel(in, cx, cy, width, height, borderMode);
          }
        }
        //out[y*width + x] = (outT)(sum / normalize);
        out[y*width + x] = (outT)(sum / normalize);
      }
    }
}

void displayFrame(float* frame, const int width, const int height, 
                  const int offset_x=0, const int offset_y=0){
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            printf("%15.2f", frame[(y+offset_y)*WIDTH + offset_x + x]);
        }
        std::cout<<std::endl;
    } 
}

void displayFrame(int* frame, const int width, const int height, 
                  const int offset_x=0, const int offset_y=0){
    for (int y=0; y<height; ++y) {
        for (int x=0; x<width; ++x) {
            std::cout<< int(frame[(y+offset_y)*WIDTH + offset_x + x]) << " \t ";
        }
        std::cout<<std::endl;
    }	
}

// get time in milliseconds
double time_ms () {
    struct timeval tv;
    gettimeofday (&tv, NULL);
    
    return ((double)(tv.tv_sec) * 1e+3 + (double)(tv.tv_usec) * 1e-3);
}

// initialize mask
void init_mask(int* mask, int width, int height) {
    const int gaussian5by5[5][5] = {
     { 1,  4,  6,  4, 1 },
     { 4, 16, 24, 16, 4 },
     { 6, 24, 36, 24, 6 },
     { 4, 16, 24, 16, 4 },
     { 1,  4,  6,  4, 1 }};

    if (width == 5 && height == 5){
        for(int j = 0; j < height; j++)
            for(int i = 0; i < width; i++)
                mask[j * width + i] = gaussian5by5[j][i];
    }
}
void init_mask(float *mask, int width, int height) {
    const float gaussian5by5[5][5] = {
     { 0.005008f, 0.017300f, 0.026151f, 0.017300f, 0.005008f },
     { 0.017300f, 0.059761f, 0.090339f, 0.059761f, 0.017300f },
     { 0.026151f, 0.090339f, 0.136565f, 0.090339f, 0.026151f },
     { 0.017300f, 0.059761f, 0.090339f, 0.059761f, 0.017300f },
     { 0.005008f, 0.017300f, 0.026151f, 0.017300f, 0.005008f }};

    if (width == 5 && height == 5){
        for(int j = 0; j < height; j++)
            for(int i = 0; i < width; i++)
                mask[j * width + i] = gaussian5by5[j][i];
    }
}

/*************************************************************************
 * Arrays: globally defined to avoid stack overflow                      *
 *************************************************************************/
    // host memory for image of width x height pixels
    din_t   host_in  [WIDTH * HEIGHT];
    dout_t  host_out [WIDTH * HEIGHT];
    // Reference
    din_t  reference_in  [WIDTH * HEIGHT];
    dout_t reference_out [WIDTH * HEIGHT];

/*************************************************************************
 * Main function                                                         *
 *************************************************************************/
int main() {

    double time0, time1, dt, min_dt;
    std::vector<float> timings;
    float timing = 0.0f;

    // convolution filter mask
    mask_t mask[SIZE_X * SIZE_X];
    init_mask(mask, 5, 5);

/*************************************************************************
 * Test Data                                                         *
 *************************************************************************/

    // initialize data
    for (int y=0; y<HEIGHT; ++y) {
        for (int x=0; x<WIDTH; ++x) {
            din_t indata = static_cast <din_t>(rand() % 256);
            host_in[y*WIDTH + x] = indata;
            reference_in[y*WIDTH + x] = indata;
            reference_out[y*WIDTH + x] = 0;
        }
    }


/*************************************************************************
 * RUN HARDWARE                                                   *
 *************************************************************************/

    // run hardware kernel
    hardware_top(host_in, host_out);

/*************************************************************************
 * Compare Output with reference functions                               *
 *************************************************************************/
   std::cerr << "Calculating reference ..." << std::endl;
   
   double start = time_ms();
   local_op(reference_out, reference_in, mask, SIZE_X, SIZE_Y, WIDTH, HEIGHT, BORDER_HANDLING_TYPE);
   double end = time_ms();
   float time = end - start;
   std::cerr << "Reference: " << time << " ms, " << (WIDTH*HEIGHT/time)/1000 << " Mpixel/s" << std::endl;
   
   std::cerr << "Comparing results ..." << std::endl;
   int pOfX= 0; //WIDTH-20;
   int pOfY= 0; //HEIGHT-10;
   printf("Reference Input \n"); displayFrame(reference_in,  10, 10, pOfX, pOfY);
   printf("Reference Output\n"); displayFrame(reference_out, 10, 10, pOfX, pOfY);
   printf("Hardware  Output\n"); displayFrame(     host_out, 10, 10, pOfX, pOfY);
   // Test Gauss (!Be careful about offset)
   int offset_x = 0; //(SIZE_X >> 1);
   int offset_y = 0; //(SIZE_Y >> 1);
   if(BORDER_HANDLING_TYPE == BorderPadding::BORDER_UNDEFINED){
     offset_x = (SIZE_X >> 1);
     offset_y = (SIZE_Y >> 1);
   }
   int offset_lx = offset_x; //(SIZE_X >> 1); 
   int offset_rx = offset_x; //(SIZE_X >> 1); 
   int offset_ly = offset_y;
   int offset_ry = offset_y; // (SIZE_Y >> 1); // offset_y;
   for (int y=offset_ly; y<HEIGHT-offset_ry; ++y) {
       for (int x=offset_lx; x<WIDTH-offset_rx; ++x) {
           if (abs(reference_out[y*WIDTH + x] - host_out[y*WIDTH + x]) > 1.0f) {
               std::cerr << "Gaussian Test FAILED, at (" << x << "," << y << "): "
               << reference_out[y*WIDTH + x] << " vs. "
               << host_out[y*WIDTH + x] << std::endl;
               // Print Output
               //printf("Hipacc Output \n"); displayFrame(host_out, 20, 10);
               exit(EXIT_FAILURE);
           }
       }
   }
   std::cerr << "Test PASSED" << std::endl;

  return EXIT_SUCCESS;
}

