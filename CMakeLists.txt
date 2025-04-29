cmake_minimum_required(VERSION 3.10)
project(FrontEnd)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files for your project
add_executable(FrontEnd 
    src/main.cpp
    src/implementation/Pokemon.cpp
    src/implementation/Entraineur.cpp 
    src/implementation/Type.cpp  
)

# Include directories (only needed if headers are not found automatically)
include_directories(/usr/local/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Link FTXUI libraries correctly
target_link_libraries(FrontEnd /usr/local/lib/libftxui-component.a)
target_link_libraries(FrontEnd /usr/local/lib/libftxui-dom.a)
target_link_libraries(FrontEnd /usr/local/lib/libftxui-screen.a)
