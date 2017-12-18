#define HIPACC_MAX_WIDTH     1024
#define HIPACC_MAX_HEIGHT    1024


#define getWindowAt(ARRAY, __x) ARRAY[__x]
float clGaussianBlurFiltergaussKernelKernel(float input0[5], 
                                            float input1[5], 
                                            float input2[5], 
                                            float input3[5], 
                                            float input4[5]) {
      float sum = 0; 
      sum += 0.005008f * getWindowAt(input0, 0);
      sum += 0.017300f * getWindowAt(input0, 1);
      sum += 0.026151f * getWindowAt(input0, 2);
      sum += 0.017300f * getWindowAt(input0, 3);
      sum += 0.005008f * getWindowAt(input0, 4);
      sum += 0.017300f * getWindowAt(input1, 0);
      sum += 0.059761f * getWindowAt(input1, 1);
      sum += 0.090339f * getWindowAt(input1, 2);
      sum += 0.059761f * getWindowAt(input1, 3);
      sum += 0.017300f * getWindowAt(input1, 4);
      sum += 0.026151f * getWindowAt(input2, 0);
      sum += 0.090339f * getWindowAt(input2, 1);
      sum += 0.136565f * getWindowAt(input2, 2);
      sum += 0.090339f * getWindowAt(input2, 3);
      sum += 0.026151f * getWindowAt(input2, 4);
      sum += 0.017300f * getWindowAt(input3, 0);
      sum += 0.059761f * getWindowAt(input3, 1);
      sum += 0.090339f * getWindowAt(input3, 2);
      sum += 0.059761f * getWindowAt(input3, 3);
      sum += 0.017300f * getWindowAt(input3, 4);
      sum += 0.005008f * getWindowAt(input4, 0);
      sum += 0.017300f * getWindowAt(input4, 1);
      sum += 0.026151f * getWindowAt(input4, 2);
      sum += 0.017300f * getWindowAt(input4, 3);
      sum += 0.005008f * getWindowAt(input4, 4);

      return sum; 
}

/* *************** Kernel **************** */
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
#define _rawBsize_5_5 ((_sizeY_5_5-1)*imWIDTH)
 
#define _DELAY ((imWIDTH*_halfsizeY_5_5) + (((_halfsizeX_5_5-1)/VECT_SIZE)+1))

__kernel __attribute__((reqd_work_group_size(1, 1, 1))) 
void lambda_141290(__global float* restrict gauss_img, __global float* restrict input_img) {
  size_t _count = 0;
  size_t _x = 0;
  size_t _cols = 0;
  size_t _yNext_5_5 = 0;
  bool _rselect_5_5 = 0;
  uchar _rselectCntr_5_5 = 0;
  float _rows_input_img_0[imWIDTH];
  float _rows_input_img_1[imWIDTH];
  float _rows_input_img_2[imWIDTH];
  float _rows_input_img_3[imWIDTH];
  float _wndSliding_input_img_0[_slidingWsize_5_5];
  float _wndSliding_input_img_1[_slidingWsize_5_5];
  float _wndSliding_input_img_2[_slidingWsize_5_5];
  float _wndSliding_input_img_3[_slidingWsize_5_5];
  float _wndSliding_input_img_4[_slidingWsize_5_5];
  while(_count != _imSIZE+_DELAY){
    {
      // Read New Pixels
      float _newPixel_input_img_4;
      if( _count<_imSIZE ){
        _newPixel_input_img_4 = ((__global float*)input_img)[_count];
      }
      //#pragma ivdep array(_rows_input_img)
      #pragma ivdep
      {
        // Read from Raw Buffer input_img
        float _newPixel_input_img_0 = _rows_input_img_0[_cols];
        float _newPixel_input_img_1 = _rows_input_img_1[_cols];
        float _newPixel_input_img_2 = _rows_input_img_2[_cols];
        float _newPixel_input_img_3 = _rows_input_img_3[_cols];
        // Shift Raw Buffer
        _rows_input_img_0[_cols] = _newPixel_input_img_1;
        _rows_input_img_1[_cols] = _newPixel_input_img_2;
        _rows_input_img_2[_cols] = _newPixel_input_img_3;
        _rows_input_img_3[_cols] = _newPixel_input_img_4;
        // Shift Sliding Window
        {
          // Shift Old Pixels
          #pragma unroll
          for(int _i=0; _i<_slidingWsize_5_5-VECT_SIZE; ++_i){
            _wndSliding_input_img_0[_i] = _wndSliding_input_img_0[_i +VECT_SIZE];
          }
          // Store New Pixels
          #pragma unroll
          for(int _i=0; _i<VECT_SIZE; ++_i){
            _wndSliding_input_img_0[_slidingWsize_5_5-VECT_SIZE+_i] = ((float*)&_newPixel_input_img_0)[_i];
          }
          // Shift Old Pixels
          #pragma unroll
          for(int _i=0; _i<_slidingWsize_5_5-VECT_SIZE; ++_i){
            _wndSliding_input_img_1[_i] = _wndSliding_input_img_1[_i +VECT_SIZE];
          }
          // Store New Pixels
          #pragma unroll
          for(int _i=0; _i<VECT_SIZE; ++_i){
            _wndSliding_input_img_1[_slidingWsize_5_5-VECT_SIZE+_i] = ((float*)&_newPixel_input_img_1)[_i];
          }
          // Shift Old Pixels
          #pragma unroll
          for(int _i=0; _i<_slidingWsize_5_5-VECT_SIZE; ++_i){
            _wndSliding_input_img_2[_i] = _wndSliding_input_img_2[_i +VECT_SIZE];
          }
          // Store New Pixels
          #pragma unroll
          for(int _i=0; _i<VECT_SIZE; ++_i){
            _wndSliding_input_img_2[_slidingWsize_5_5-VECT_SIZE+_i] = ((float*)&_newPixel_input_img_2)[_i];
          }
          // Shift Old Pixels
          #pragma unroll
          for(int _i=0; _i<_slidingWsize_5_5-VECT_SIZE; ++_i){
            _wndSliding_input_img_3[_i] = _wndSliding_input_img_3[_i +VECT_SIZE];
          }
          // Store New Pixels
          #pragma unroll
          for(int _i=0; _i<VECT_SIZE; ++_i){
            _wndSliding_input_img_3[_slidingWsize_5_5-VECT_SIZE+_i] = ((float*)&_newPixel_input_img_3)[_i];
          }
          // Shift Old Pixels
          #pragma unroll
          for(int _i=0; _i<_slidingWsize_5_5-VECT_SIZE; ++_i){
            _wndSliding_input_img_4[_i] = _wndSliding_input_img_4[_i +VECT_SIZE];
          }
          // Store New Pixels
          #pragma unroll
          for(int _i=0; _i<VECT_SIZE; ++_i){
            _wndSliding_input_img_4[_slidingWsize_5_5-VECT_SIZE+_i] = ((float*)&_newPixel_input_img_4)[_i];
          }
        }
      }
    }
    // Write Output and Execute Kernel
    if( _count>=_DELAY ){
      float _pixelOut = clGaussianBlurFiltergaussKernelKernel(_wndSliding_input_img_0, _wndSliding_input_img_1, _wndSliding_input_img_2,         
                                                              _wndSliding_input_img_3, _wndSliding_input_img_4);
      gauss_img[_count-_DELAY] = _pixelOut;
      _x ++;
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
    _cols++;
    if(_cols == imWIDTH){ _cols = 0;}
    _count++;
  }
}


//uchar clGaussianBlurFiltergaussKernelKernel(float input0[vectFactor+4], 
//                                            float input1[vectFactor+4], 
//                                            float input2[vectFactor+4], 
//                                            float input3[vectFactor+4], 
//                                            float input4[vectFactor+4], 
//                                            const int vi) {
//
//    {
//
//      float _tmp[5]; 
//
//      _tmp[0] = 0.005008f * getWindowAt(input0, 0, vi) 
//              + 0.017300f * getWindowAt(input0, 1, vi) 
//              + 0.026151f * getWindowAt(input0, 2, vi) 
//              + 0.017300f * getWindowAt(input0, 3, vi) 
//              + 0.005008f * getWindowAt(input0, 4, vi);
//
//      _tmp[1] = 0.017300f * getWindowAt(input1, 0, vi) 
//              + 0.059761f * getWindowAt(input1, 1, vi) 
//              + 0.090339f * getWindowAt(input1, 2, vi) 
//              + 0.059761f * getWindowAt(input1, 3, vi) 
//              + 0.017300f * getWindowAt(input1, 4, vi);
//
//      _tmp[2] = 0.026151f * getWindowAt(input2, 0, vi) 
//              + 0.090339f * getWindowAt(input2, 1, vi) 
//              + 0.136565f * getWindowAt(input2, 2, vi) 
//              + 0.090339f * getWindowAt(input2, 3, vi) 
//              + 0.026151f * getWindowAt(input2, 4, vi);
//
//      _tmp[3] = 0.017300f * getWindowAt(input3, 0, vi) 
//              + 0.059761f * getWindowAt(input3, 1, vi) 
//              + 0.090339f * getWindowAt(input3, 2, vi) 
//              + 0.059761f * getWindowAt(input3, 3, vi) 
//              + 0.017300f * getWindowAt(input3, 4, vi);
//
//      _tmp[4] = 0.005008f * getWindowAt(input4, 0, vi) 
//              + 0.017300f * getWindowAt(input4, 1, vi) 
//              + 0.026151f * getWindowAt(input4, 2, vi) 
//              + 0.017300f * getWindowAt(input4, 3, vi) 
//              + 0.005008f * getWindowAt(input4, 4, vi);
//
//
//      return (_tmp[0] + _tmp[1] + _tmp[2] + _tmp[3] + _tmp[4]);
//    }
//
//}