#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main_impala();

void getMicroTime() {
    static long global_time = 0;

    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);

    if (global_time==0) {
        global_time = now.tv_sec*1000000LL + now.tv_nsec / 1000LL;
    } else {
        global_time = (now.tv_sec*1000000LL + now.tv_nsec / 1000LL) - global_time;
        printf("\ttiming: %f(ms)\n", global_time * 1.0e-3);
        global_time = 0;
    }
}

void *thorin_malloc(size_t size) {
    void *mem;
    posix_memalign(&mem, 64, size);
    std::cerr << " * malloc() -> " << mem << std::endl;
    host_mems_[mem] = {1, size, 1};
    return mem;
}

void thorin_free(void *ptr) {
    free(ptr);
}

float random_val(int max) {
    return ((float)random() / RAND_MAX) * max;
}

int main() {
    return main_impala();
}
