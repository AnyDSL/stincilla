#define VECT_SIZE 1
#define imWIDTH (1024/VECT_SIZE)
#define imHEIGHT 1024
#define _imSIZE (imWIDTH*imHEIGHT)

#define _sizeX_5_5 5
#define _sizeY_5_5 5
#define _halfsizeX_5_5 (_sizeX_5_5 >> 1)
#define _halfsizeY_5_5 (_sizeY_5_5 >> 1)
#define _numVecInSW_5_5 (((_halfsizeX_5_5-1)/VECT_SIZE)+1)
#define _slidingWsize_5_5 (_halfsizeX_5_5+((_numVecInSW_5_5+1)*VECT_SIZE))
#define _rawBsize_5_5 ((_sizeY_5_5-1)*imWIDTH + _sizeX_5_5)
 
#define _DELAY ((imWIDTH*_halfsizeY_5_5) + (((_halfsizeX_5_5-1)/VECT_SIZE)+1))

#define getWindowAt(ARRAY, __y, __x) ARRAY[__y * imWIDTH + __x]


/* *************** Kernel **************** */

__kernel __attribute__((reqd_work_group_size(1, 1, 1))) 
void lambda_141290(__global float* gauss_img, __global float* input_img) {
  size_t _count = 0;
  size_t _x = 0;
  size_t _yNext_5_5 = 0;
  bool _rselect_5_5 = 0;
  uchar _rselectCntr_5_5 = 0;
  float _rows_input_img[_rawBsize_5_5];
  
  while(_count != _imSIZE+_DELAY){
    {
      // Read New Pixels
      float _newPixel_input_img_4;
      if( _count<_imSIZE ){
        _newPixel_input_img_4 = ((__global float*)input_img)[_count];
      }
      {
        // Shift Raw Buffer
        for(int _i=0; _i<_rawBsize_5_5-1; ++_i){
          _rows_input_img[_i] = _rows_input_img[_i+1];
        }
        _rows_input_img[_rawBsize_5_5-1] = _newPixel_input_img_4;
      }
    }
    {
      // Execute Kernel
      float _pixelOut = 0; 
      _pixelOut += 0.005008f * getWindowAt(_rows_input_img, 0, 0);
      _pixelOut += 0.017300f * getWindowAt(_rows_input_img, 0, 1);
      _pixelOut += 0.026151f * getWindowAt(_rows_input_img, 0, 2);
      _pixelOut += 0.017300f * getWindowAt(_rows_input_img, 0, 3);
      _pixelOut += 0.005008f * getWindowAt(_rows_input_img, 0, 4);
      _pixelOut += 0.017300f * getWindowAt(_rows_input_img, 1, 0);
      _pixelOut += 0.059761f * getWindowAt(_rows_input_img, 1, 1);
      _pixelOut += 0.090339f * getWindowAt(_rows_input_img, 1, 2);
      _pixelOut += 0.059761f * getWindowAt(_rows_input_img, 1, 3);
      _pixelOut += 0.017300f * getWindowAt(_rows_input_img, 1, 4);
      _pixelOut += 0.026151f * getWindowAt(_rows_input_img, 2, 0);
      _pixelOut += 0.090339f * getWindowAt(_rows_input_img, 2, 1);
      _pixelOut += 0.136565f * getWindowAt(_rows_input_img, 2, 2);
      _pixelOut += 0.090339f * getWindowAt(_rows_input_img, 2, 3);
      _pixelOut += 0.026151f * getWindowAt(_rows_input_img, 2, 4);
      _pixelOut += 0.017300f * getWindowAt(_rows_input_img, 3, 0);
      _pixelOut += 0.059761f * getWindowAt(_rows_input_img, 3, 1);
      _pixelOut += 0.090339f * getWindowAt(_rows_input_img, 3, 2);
      _pixelOut += 0.059761f * getWindowAt(_rows_input_img, 3, 3);
      _pixelOut += 0.017300f * getWindowAt(_rows_input_img, 3, 4);
      _pixelOut += 0.005008f * getWindowAt(_rows_input_img, 4, 0);
      _pixelOut += 0.017300f * getWindowAt(_rows_input_img, 4, 1);
      _pixelOut += 0.026151f * getWindowAt(_rows_input_img, 4, 2);
      _pixelOut += 0.017300f * getWindowAt(_rows_input_img, 4, 3);
      _pixelOut += 0.005008f * getWindowAt(_rows_input_img, 4, 4);
      // Write Output
      if( _count>=_DELAY ){
        ((__global float*)gauss_img)[_count-_DELAY] = _pixelOut;
        _x ++;
      }
    }
    if( _x==(imWIDTH-(_numVecInSW_5_5)) ){
      _rselect_5_5 = 1;
      _yNext_5_5++;
    }
    else if( _x==imWIDTH){
      _x = 0;
      _rselect_5_5 = 0;
    }
    if( _rselect_5_5==1 ){
      _rselectCntr_5_5++;
    }
    else{
      _rselectCntr_5_5 = 0;
    }
    _count++;
  }
}


//float clGaussianBlurFiltergaussKernelKernel( __local float input[_rawBsize_5_5]){ 
//      float sum = 0; 
//      sum += 0.005008f * getWindowAt(input, 0, 0);
//      sum += 0.017300f * getWindowAt(input, 0, 1);
//      sum += 0.026151f * getWindowAt(input, 0, 2);
//      sum += 0.017300f * getWindowAt(input, 0, 3);
//      sum += 0.005008f * getWindowAt(input, 0, 4);
//      sum += 0.017300f * getWindowAt(input, 1, 0);
//      sum += 0.059761f * getWindowAt(input, 1, 1);
//      sum += 0.090339f * getWindowAt(input, 1, 2);
//      sum += 0.059761f * getWindowAt(input, 1, 3);
//      sum += 0.017300f * getWindowAt(input, 1, 4);
//      sum += 0.026151f * getWindowAt(input, 2, 0);
//      sum += 0.090339f * getWindowAt(input, 2, 1);
//      sum += 0.136565f * getWindowAt(input, 2, 2);
//      sum += 0.090339f * getWindowAt(input, 2, 3);
//      sum += 0.026151f * getWindowAt(input, 2, 4);
//      sum += 0.017300f * getWindowAt(input, 3, 0);
//      sum += 0.059761f * getWindowAt(input, 3, 1);
//      sum += 0.090339f * getWindowAt(input, 3, 2);
//      sum += 0.059761f * getWindowAt(input, 3, 3);
//      sum += 0.017300f * getWindowAt(input, 3, 4);
//      sum += 0.005008f * getWindowAt(input, 4, 0);
//      sum += 0.017300f * getWindowAt(input, 4, 1);
//      sum += 0.026151f * getWindowAt(input, 4, 2);
//      sum += 0.017300f * getWindowAt(input, 4, 3);
//      sum += 0.005008f * getWindowAt(input, 4, 4);
//
//      return sum; 
//}
