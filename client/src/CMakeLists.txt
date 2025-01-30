set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt5 REQUIRED COMPONENTS Core Network)

add_executable(client main.cpp
    TcpClient.h TcpClient.cpp)

target_link_libraries(client Qt5::Core Qt5::Network)

set_target_properties(client PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)


