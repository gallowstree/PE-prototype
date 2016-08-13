#[[
cmake_minimum_required(VERSION 3.5)
project(gameplay_prototype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(SFML 2.1 COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIR} ${PROJECT_SOURCE_DIR})
set(SOURCE_FILES main.cpp)
add_executable(gameplay_prototype ${SOURCE_FILES})
]]

cmake_minimum_required(VERSION 3.2)
project(gameplay_prototype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES main.cpp Game.cpp Game.h World.cpp World.h Menu.cpp Menu.h ResourceHolder.cpp ResourceHolder.h Player.cpp Player.h SFUtils.h Entity.cpp Entity.h Area.cpp Area.h)
add_executable(gameplay_prototype ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(gameplay_prototype ${SFML_LIBRARIES})
endif()

