add_executable(TestDeploy src/testDeploy.cc)

target_link_libraries(TestDeploy cppmsa)

enable_testing()
add_test(test_deploy TestDeploy)
