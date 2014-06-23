CUDA_DIR  ?= /usr/local/cuda
INC_DIRS   = -I $(CUDA_DIR)/include \
             -I $(CUDA_DIR)/nvvm/include \
             -I $(CUDA_DIR)/nvvm/libnvvm-samples/common/include \
             -I .
LIB_DIRS   = $(CUDA_DIR)/lib64 $(CUDA_DIR)/nvvm/lib64
CXX_FLAGS := -Wall -Wunused
OPT_FLAGS := -O3
DBG_FLAGS :=
RPATH_PRE := -Wl,-rpath,

OS:=$(shell uname -s)

ifeq ($(OS),Linux)
    LD_FLAGS = -lcuda -lnvvm -lm
    CXX_FLAGS += -std=c++11
    LD_FLAGS  += -lstdc++
endif
ifeq ($(OS),Darwin) # assume Mac OS X
    LD_FLAGS = -lcuda -lnvvm
    # use libc++ for clang++
    CXX_FLAGS += -std=c++11 -stdlib=libc++ \
                 -I`clang -print-file-name=include` \
                 -I`llvm-config --includedir` \
                 -I`llvm-config --includedir`/c++/v1
    LD_FLAGS  += -L`llvm-config --libdir` -lc++
endif


BINARY = test
SOURCES_CPP := $(shell echo *.cpp)
SOURCES_LL  := $(shell echo *.ll)

OBJS = $(SOURCES_CPP:%.cpp=%.o) $(SOURCES_LL:%.ll=%.o)


all: $(BINARY)

$(BINARY): $(OBJS)
	clang++ $(OBJS) $(addprefix $(RPATH_PRE),$(LIB_DIRS)) $(addprefix -L ,$(LIB_DIRS)) $(LD_FLAGS) -o $@

%.o: %.cpp
	echo $(SOURCES_CPP)
	echo $(SOURCES_LL)
	echo $(OBJS)
	clang++ $(CXX_FLAGS) -DLIBDEVICE_DIR='"$(CUDA_DIR)/nvvm/libdevice/"' $(OPT_FLAGS) $(DBG_FLAGS) $(INC_DIRS) -o $@ -c $<

%.o: %.ll
	clang++ $(CXX_FLAGS) $(OPT_FLAGS) $(DBG_FLAGS) -o $@ -c $<


clean:
	rm -f $(BINARY) $(OBJS) *.nvvm *.cl *.spir *.bc *.cu
	@echo "all cleaned up!"

run: $(BINARY)
	./$(BINARY)

