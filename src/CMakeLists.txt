add_library(common common/Logger.cpp)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/common)

add_library(converter converter/UnitConverter.cpp)
target_include_directories(converter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(parser 
    parser/ChecksumValidator.cpp
    parser/GpParser.cpp
    parser/GsParser.cpp
    parser/HeParser.cpp
    parser/VeParser.cpp
    parser/PaParser.cpp
    parser/LeniotParserFactory.cpp
)
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(service 
    service/NavigationProcessor.cpp
    service/StorageService.cpp
)
target_include_directories(service PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(leniot_backend main.cpp)
target_include_directories(leniot_backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(leniot_backend PRIVATE common parser converter service)
