cmake_minimum_required(VERSION 3.10)
project(GraphOperationsTest)

set(CMAKE_CXX_STANDARD 11)

# Adicione o Catch2
find_package(Catch2 REQUIRED)
include_directories(${CATCH2_INCLUDE_DIR})

# Adicione os arquivos de origem e de teste
add_executable(GraphOperationsTest test/testGraphOperations.cpp source/Graph.cpp source/GraphOperations.cpp)

# Link com o Catch2 e pthread
target_link_libraries(GraphOperationsTest Catch2::Catch2 pthread)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
