include_directories(include/)
file(GLOB_RECURSE SRC_FILES src/*.cpp include/*.hpp)

add_executable(game ${SRC_FILES} game.cpp)
target_link_libraries(game ${ALL_LIBRARIES})

#add_executable(server ${SRC_FILES} server.cpp)
#target_link_libraries(server ${ALL_LIBRARIES})

#add_executable(client ${SRC_FILES} client.cpp)
#target_link_libraries(client ${ALL_LIBRARIES})
