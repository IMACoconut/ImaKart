include_directories(include/)
file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
add_executable(template ${SRC_FILES})
target_link_libraries(template ${ALL_LIBRARIES})
