message(STATUS "Preparing tests")

# Enable construction of test target
enable_testing()

# Create and link the test executables
add_executable(basicppmsa.test_deploy src/testDeploy.cc)
target_link_libraries(basicppmsa.test_deploy basicppmsa)

# Test definitions
macro(create_test target)
    add_test(NAME ${target} COMMAND $<TARGET_FILE:${target}>)
endmacro(create_test)

create_test(basicppmsa.test_deploy)

message(STATUS "Preparing tests - done")
