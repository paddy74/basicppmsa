message(STATUS "Generating samples")

add_executable(basicppmsa.example src/example.cpp)
target_link_libraries(basicppmsa.example basicppmsa)

message(STATUS "Generating samples - done")
