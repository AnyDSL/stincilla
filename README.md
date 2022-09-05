# Stincilla #
A DSL for Stencil Codes

## Prerequisites ##
Stincilla requires a working AnyDSL installation. A script to build the [artic](https://github.com/AnyDSL/artic) frontend and [thorin](https://github.com/AnyDSL/thorin) backend as well as the [runtime](https://github.com/AnyDSL/runtime) component is provided by the [anydsl metaproject](https://github.com/AnyDSL/anydsl) (setup.sh). This script will also checkout Stincilla's sources and configure a build directory.

If you checked out Stincilla separately, use the following command to download submodules:
```bash
git submodule update --init --recursive
```

## Building ##
The setup.sh configures Stincilla and sets all required paths. The backend for code generation will be set to ```cpu```. This can be changed via CMake:
* ```BACKEND``` : defines the backend to generate code for (supported values: ```cpu```, ```avx```, ```nvvm```, ```cuda```, ```opencl```, ```amdgpu```)

Example:
```bash
cd anydsl/stincilla/build
cmake -DBACKEND=nvvm .. # optional: switch to nvvm backend
make
```
