cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

if (UNIX)
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "clang++")
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Set the project name and language.
project(HDF5MyExample C CXX)

if (UNIX)
    include(CMakeLists_Linux.cmake)
elseif (WIN32)
    include(CMakeLists_Windows.cmake)
endif ()

set(EXE_FILE_TITLE hdf5_my_example)
add_executable(${EXE_FILE_TITLE} ${PROJECT_SOURCE_DIR}/${EXE_FILE_TITLE}.cpp)
target_link_libraries(${EXE_FILE_TITLE} ${LIBHDF5_HL_CPP} ${LIBHDF5_HL} ${LIBHDF5_CPP} ${LIBHDF5} ${LIBZ} ${LIBSZ} ${LIBAEC}) # Order sensitive. See [CMake and order dependent linking of shared libraries](https://stackoverflow.com/questions/12204820/cmake-and-order-dependent-linking-of-shared-libraries)
