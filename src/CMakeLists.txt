add_library(common common/Logger.cpp)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)

add_executable(leniot_backend main.cpp)
target_include_directories(leniot_backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(leniot_backend PRIVATE common)
