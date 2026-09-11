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

add_executable(test_unit_converter test_unit_converter.cpp)
target_include_directories(test_unit_converter PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_unit_converter PRIVATE GTest::gtest_main converter)
add_test(NAME UnitConverterTest COMMAND test_unit_converter)

add_executable(test_parsers test_parsers.cpp)
target_include_directories(test_parsers PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_parsers PRIVATE GTest::gtest_main parser)
add_test(NAME ParsersTest COMMAND test_parsers)

add_executable(test_navigation_processor test_navigation_processor.cpp)
target_include_directories(test_navigation_processor PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_navigation_processor PRIVATE GTest::gtest_main service converter)
add_test(NAME NavigationProcessorTest COMMAND test_navigation_processor)

add_executable(test_storage test_storage.cpp)
target_include_directories(test_storage PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_storage PRIVATE GTest::gtest_main service)
add_test(NAME StorageTest COMMAND test_storage)
