cmake_minimum_required(VERSION 3.19)
project(EcoRide LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)   # <-- Important: enables moc
set(CMAKE_AUTOUIC ON)   # optional, for .ui files
set(CMAKE_AUTORCC ON)   # optional, for .qrc files

add_executable(EcoRide
    main.cpp
    loginwindow.cpp
    mainwindow.cpp
    loginwindow.h
    mainwindow.h
    driverdashboard.h
    driverdashboard.cpp
    riderdashboard.h
    riderdashboard.cpp
)

target_link_libraries(EcoRide
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)
