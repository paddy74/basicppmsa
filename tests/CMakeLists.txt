message(STATUS "Preparing tests")

# Enable construction of test target
enable_testing()

# Create and link the test executables
add_executable(msabase.test_deploy src/test_deploy.cpp)
target_link_libraries(msabase.test_deploy msabase)

# Test definitions
macro(create_test target)
    add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)
endmacro(create_test)

create_test(msabase.test_deploy)

message(STATUS "Preparing tests - done")
