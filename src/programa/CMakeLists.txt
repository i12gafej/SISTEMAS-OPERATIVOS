add_library(programa functions.cpp)
target_include_directories(programa PUBLIC
                          "${CMAKE_CURRENT_LIST_DIR}")
# ${CMAKE_CURRENT_LIST_DIR} dir. de este CMakeLisis.txt

add_executable(main main.cpp)
target_link_libraries(main programa)
