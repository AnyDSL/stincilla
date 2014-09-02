CUDA_DIR  ?= $(shell dirname $(shell dirname `which nvcc`))
INC_DIRS   = -I $(CUDA_DIR)/include \
             -I $(CUDA_DIR)/nvvm/include \
             -I $(CUDA_DIR)/nvvm/libnvvm-samples/common/include \
             -I .
CXX_FLAGS := -std=c++11 -Wall -Wunused
OPT_FLAGS := -O3 -fno-vectorize -fno-slp-vectorize -fno-slp-vectorize-aggressive
DBG_FLAGS :=
RPATH_PRE := -Wl,-rpath,
OS        := $(shell uname -s)
CPP        = $(shell echo *.cpp)
IMPALA     = $(shell echo bilateral.impala)
NVVM       = $(IMPALA:%.impala=%.nvvm)
OBJS       = $(CPP:%.cpp=%.o)
OBJS      += $(IMPALA:%.impala=%.o)


ifeq ($(OS),Linux)
	LD_FLAGS = -lcuda -lnvvm -lm
	LIB_DIRS = $(CUDA_DIR)/lib64 $(CUDA_DIR)/nvvm/lib64
	SED_EXT =
endif
ifeq ($(OS),Darwin) # assume Mac OS X
	LD_FLAGS = -lcuda -lnvvm
	LIB_DIRS = $(CUDA_DIR)/lib $(CUDA_DIR)/nvvm/lib
	SED_EXT = ''
endif


all: main.out
	@echo "Running main.out ..."
	@# remove attribute from asm
	@./post-patcher nvvm $(IMPALA:%.impala=%)
	./main.out

%.o: %.cpp
	clang++ $(CXX_FLAGS) -DNVCC_BIN='"$(CUDA_DIR)/bin/nvcc"' -DLIBDEVICE_DIR='"$(CUDA_DIR)/nvvm/libdevice/"' $(DBG_FLAGS) $(OPT_FLAGS) $(INC_DIRS) -c -o $@ $^

%.o: %.ll
	clang++ $(CXX_FLAGS) $(DBG_FLAGS) $(OPT_FLAGS) -c -o $@ $^

main.out: $(OBJS)
	clang++ $^ $(addprefix $(RPATH_PRE),$(LIB_DIRS)) $(addprefix -L ,$(LIB_DIRS)) $(LD_FLAGS) -o $@

clean:
	@rm -f *.ll *.o *.bc *.s *.cu *.nvvm *.ptx *.out

.PHONY: all

