# Stincilla #
A DSL for Stencil Codes

## Prerequisites ##
Stincilla requires a working AnyDSL installation. A script to build the [impala](https://github.com/AnyDSL/impala) frontend and [thorin](https://github.com/AnyDSL/thorin) backend as well as the [runtime](https://github.com/AnyDSL/runtime) component is provided by the [anydsl metaproject](https://github.com/AnyDSL/anydsl) (setup.sh). This script will also checkout Stincilla's sources and configure a build directory.

## Building ##
The setup.sh configures Stincilla and sets all required paths. The backend for code generation will be set to ```cpu```. This can be changed via CMake:
* ```BACKEND``` : defines the backend to generate code for (supported values:```cpu```,```avx``` ```aocl```, ```hls```)
* ```SYNTHESIS```: On HLS backend, turn *SYNTHESIS* ```on``` for HDL generation and logic synthesis, or turn ```off``` for a quick software simulation.( for HLS backend )
* ```FPGA_PART```: On HLS backend, specify FPGA part.
Example:
```bash
cd anydsl/stincilla/build
cmake -DBACKEND=aocl .. # optional: switch to OpenCL backend for Intel FPGAs
make
```
