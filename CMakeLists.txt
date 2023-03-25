CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

PROJECT(cpp-countdown LANGUAGES CXX VERSION 0.1.0)

SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_STANDARD 20)

ADD_EXECUTABLE(${PROJECT_NAME} src/main.cpp )
ADD_LIBRARY(lib src/expression.cpp src/solver.cpp src/helper.cpp)

target_link_libraries(${PROJECT_NAME} lib)
