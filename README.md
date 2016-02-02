# Stincilla #
A DSL for Stencil Codes

## Prerequisites ##
Stincilla requires a working AnyDSL installation. A script to build the [impala](https://github.com/AnyDSL/impala) frontend and [thorin](https://github.com/AnyDSL/thorin) backend is provided by the [anydsl metaproject](https://github.com/AnyDSL/anydsl) (setup.sh). This script will also Stincilla's sources and configure a build directory.

## Building ##
The setup.sh configures Stincilla and sets all required paths. The backend for code generation will be set to ```cpu```. This can be changed via CMake:
* ```BACKEND``` : defines the backend to generate code for (supported values: ```cpu```, ```avx```, ```nvvm```, ```cuda```, ```opencl```, ```spir```)

Example:
```bash
cd anydsl/stincilla/build
cmake -DBACKEND=nvvm .. # optional: switch to nvvm backend
make
```
