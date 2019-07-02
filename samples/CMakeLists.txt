message(STATUS "Generating samples")

add_executable(msabase.example src/example.cpp)
target_link_libraries(msabase.example msabase)

message(STATUS "Generating samples - done")
