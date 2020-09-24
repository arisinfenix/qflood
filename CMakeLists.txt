cmake_minimum_required(VERSION 3.8)

project(qflood LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
add_compile_options(-Wall -Wextra)

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)

add_executable(qflood
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/view.cpp
    src/view.h
    src/boarditem.cpp
    src/boarditem.h
    src/starfield.cpp
    src/starfield.h
    src/resources.qrc
)

target_link_libraries(qflood PRIVATE Qt5::Widgets Qt5::Multimedia)
