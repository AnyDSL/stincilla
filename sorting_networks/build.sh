#!/bin/bash

impala ../intrinsics_thorin.impala ../intrinsics_utils.impala ../extern.impala oddeven.impala -emit-llvm
impala ../intrinsics_thorin.impala ../intrinsics_utils.impala ../extern.impala ../intrinsics_cpu.impala mapping_cpu.impala oddeven.impala median.impala -emit-llvm
