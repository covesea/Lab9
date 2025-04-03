cmake_minimum_required(VERSION 3.10)

project(JsonFileHandler)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(nlohmann_json 3.2.0 REQUIRED)

find_package(json-schema-validator REQUIRED)

set(SOURCES
    main.cpp
    configuration.cpp
)

add_executable(JsonFileHandler ${SOURCES})

target_link_libraries(JsonFileHandler nlohmann_json::nlohmann_json json-schema-validator)