# Stincilla #
A DSL for Stencil Codes

## Prerequisites ##
Stincilla requires a working AnyDSL installation. A script to build the [impala](https://github.com/AnyDSL/impala) frontend and [thorin](https://github.com/AnyDSL/thorin) backend is provided by the [anydsl metaproject](https://github.com/AnyDSL/anydsl) (setup.sh).

## Building ##
CMake files are provided to build Stincilla. When running CMake, the thorin directory needs to be provided and the backend for code generation can be configured:
* BACKEND : defines the backend to generate code for (supported values: cpu, avx, nvvm, cuda, opencl, spir)
* THORIN_DIR : the directory where thorin was built

Example:
```bash
cd stincilla
mkdir build && cd build
cmake -DTHORIN_DIR=<path-to-anydsl/thorin> -DBACKEND=nvvm ..
make
```
