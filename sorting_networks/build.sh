#!/bin/bash

impala ../intrinsics_utils.impala ../extern.impala oddeven.impala -emit-llvm
