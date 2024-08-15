cmake_minimum_required(VERSION 3.10)
project(GraphOperationsTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adiciona os arquivos de origem
add_executable(MainExec source/Graph.cpp source/GraphOperations.cpp main.cpp)

# Condicionalmente adiciona Catch2 se encontrado
find_package(Catch2 REQUIRED) # Tornar a busca pelo Catch2 obrigatória
include(CTest)
include(Catch)

if(CATCH2_FOUND)
    include_directories(${CATCH2_INCLUDE_DIRS})
    
    # Adiciona os testes
    add_executable(GraphOperationsTest 
        test/testDirected.cpp 
        test/testUndirected.cpp 
        test/testGraph.cpp 
        source/Graph.cpp 
        source/GraphOperations.cpp
    )
    
    target_link_libraries(GraphOperationsTest Catch2::Catch2WithMain pthread) # Linkar Catch2 com Main
    catch_discover_tests(GraphOperationsTest)
endif()

# Compila o executável principal
target_link_libraries(MainExec pthread)

# Configura a biblioteca Catch2 manualmente para o Windows
if(WIN32)
    target_link_libraries(GraphOperationsTest ${CATCH2_LIBRARIES})
endif()
