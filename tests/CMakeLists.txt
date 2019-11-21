message(STATUS "Generating tests")

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

message(STATUS "Generating tests - done")

# -----------------------------------------------------------------------------
# Code Coverage report
# -----------------------------------------------------------------------------
# cmake .. -DENABLE_CODECOV=ON
# cmake --build .
# cmake --target target
if (ENABLE_COVERAGE)
    include(CodeCoverage)
    set(COVERAGE_LCOV_EXCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/../libs/*")

    APPEND_COVERAGE_COMPILER_FLAGS()

    include(ProcessorCount)
    ProcessorCount(N_CORES)

    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME lowletorfeats.coverage
        EXECUTABLE cd tests/ && ctest -j ${N_CORES}
        DEPENDENCIES
            msabase.test_deploy
    )
endif()
