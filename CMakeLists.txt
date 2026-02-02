#The root CMakeLists.txt file.
cmake_minimum_required(VERSION 3.28)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

#The project name is set here. In this case it's Rocket, but you can change it to whatever you want.
project(Rocket  VERSION 1.0.0 LANGUAGES CXX)

#Require C++23
set(CXX_STANDARD_REQUIRED ON) #Make C++23 a hard requirement
set(CMAKE_CXX_STANDARD 23) # Default C++ standard for targets
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

find_package(fmt CONFIG REQUIRED)

#We're using the project name as the target name, but you can change it to make them different.
#With this setup, the name of the executable will be the same as the project name.
add_executable(${PROJECT_NAME}
        src/main.cpp
        src/engine/EthernetMedium.cpp
        src/engine/Event.cpp
        src/engine/EventQueue.cpp
        src/engine/Node.cpp
        src/engine/SimulatedSocket.cpp
        src/engine/SimulationClock.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        src
)

target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET CXX_MODULES FILES
)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)