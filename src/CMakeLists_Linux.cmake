string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -Wfatal-errors -Winline -Wold-style-cast -Wredundant-decls -Wshadow -Wswitch-default -Wswitch-enum -Wundef -Wunused-variable")
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -O0 -g -fsanitize=address -fstack-protector -ftrapv")
string(APPEND CMAKE_CXX_FLAGS_RELEASE " -O3 -DNDEBUG")

set(HDF5_ROOT_DIR "/usr/local/hdf5-1.12.2")
set(HDF5_INCLUDE_DIR "${HDF5_ROOT_DIR}/include")
set(HDF5_LIB_DIR "${HDF5_ROOT_DIR}/lib")
include_directories(${HDF5_INCLUDE_DIR})

# Specify libraries by full-path to prevent other hdf5 libraries belonging to such as Anaconda from being piked up.
set(HDF5_LIB_LINK_TYPE shared) # `static` or `shared`
if (${HDF5_LIB_LINK_TYPE} STREQUAL "static")
    set(LIB_FILE_NAME_EXT "a")
elseif (${HDF5_LIB_LINK_TYPE} STREQUAL "shared")
    set(LIB_FILE_NAME_EXT "so")
else ()
    message(FATAL_ERROR "Unsupported link type: ${HDF5_LIB_LINK_TYPE}")
endif ()

find_library(LIBHDF5_HL_CPP NAMES "libhdf5_hl_cpp.${LIB_FILE_NAME_EXT}" PATHS ${HDF5_LIB_DIR} NO_DEFAULT_PATH)
find_library(LIBHDF5_HL NAMES "libhdf5_hl.${LIB_FILE_NAME_EXT}" PATHS ${HDF5_LIB_DIR} NO_DEFAULT_PATH)
find_library(LIBHDF5_CPP NAMES "libhdf5_cpp.${LIB_FILE_NAME_EXT}" PATHS ${HDF5_LIB_DIR} NO_DEFAULT_PATH)
find_library(LIBHDF5 NAMES "libhdf5.${LIB_FILE_NAME_EXT}" PATHS ${HDF5_LIB_DIR} NO_DEFAULT_PATH)

find_library(LIBZ NAMES libz.a PATHS ${HDF5_LIB_DIR} NO_DEFAULT_PATH)
find_library(LIBSZAEC NAMES libszaec.a PATHS ${HDF5_LIB_DIR} NO_DEFAULT_PATH)
