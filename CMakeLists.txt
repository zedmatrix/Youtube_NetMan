cmake_minimum_required(VERSION 3.5)

project(Network_Mananager LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

add_executable(NetMan
    main.cpp
    mainwindow.cpp
    networkmanager.cpp
    networkmanager.h
    mainwindow.h
    ui_mainwindow.h
    mainwindow.ui
)

target_link_libraries(NetMan Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)
