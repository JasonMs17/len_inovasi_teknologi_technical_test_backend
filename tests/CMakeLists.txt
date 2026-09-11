include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_checksum test_checksum.cpp)
target_include_directories(test_checksum PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_checksum PRIVATE GTest::gtest_main parser)
add_test(NAME ChecksumValidatorTest COMMAND test_checksum)
