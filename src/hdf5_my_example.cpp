#include <cstdio>
#include <cstdlib>

//#define H5_BUILT_AS_DYNAMIC_LIB 1 // In Windows, turn on this when using hdf5 as a shared library.
#include <H5Cpp.h>

int main() {
    printf("Hello, World!\n");
    const std::string fileName("test.h5");
    H5::H5File file(fileName, H5F_ACC_TRUNC);
    printf("File creation is done.\n");
    return EXIT_SUCCESS;
}
