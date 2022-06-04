cmake_minimum_required(VERSION 3.16)

project(algo4 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -pthread")





add_executable(algo4 main.cpp )

#target_compile_features(thread cxx_std_17)


target_include_directories(algo4 PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
                           	  
install(TARGETS algo4 DESTINATION bin)
