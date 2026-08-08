cmake_minimum_required(VERSION 3.12)
project(DataStructures VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
	add_compile_options(/utf-8)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

set(PROJECT_SOURCES
	main.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
