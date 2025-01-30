
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(Boost REQUIRED COMPONENTS system json)

add_executable(server
    main.cpp
    server/session.cpp
    server/tcp_server.cpp

    algorithm/json_convertor.cpp
    algorithm/words_counter.cpp
    logging/utils.cpp
)

target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(server Boost::system Boost::json)


