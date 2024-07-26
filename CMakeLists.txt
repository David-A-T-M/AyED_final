#Versión de CMake
cmake_minimum_required(VERSION 3.28)

#Nombre del proyecto
project(AyEdD_Routers)

#Versión de C++
set(CMAKE_CXX_STANDARD 14)

#Archivos fuente
add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(lib/googletest)

