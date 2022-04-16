$TOP_DIR = Split-Path $PSScriptRoot -Parent

cmake -G "Visual Studio 16 2019" -S ${TOP_DIR}/src -B ${TOP_DIR}/build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
