add_library(common common/Logger.cpp)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

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
target_link_libraries(parser PUBLIC common)

add_library(service 
    service/NavigationProcessor.cpp
    service/StorageService.cpp
    service/ExtrapolationService.cpp
)
target_include_directories(service PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(service PUBLIC converter common)

add_library(network 
    network/UdpSender.cpp
    network/UdpReceiver.cpp
)
target_include_directories(network PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(network PUBLIC common)

if(WIN32)
    target_link_libraries(network PUBLIC ws2_32)
endif()

add_executable(leniot_backend main.cpp)
target_include_directories(leniot_backend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(leniot_backend PRIVATE service network parser converter common)
