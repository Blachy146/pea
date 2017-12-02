cmake_minimum_required(VERSION 3.0)

project(pea_zadanie2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface)

set(SOURCES
    ${SOURCE_DIR}/TabuSearch.cpp
    ${SOURCE_DIR}/Parser.cpp
)

set(EXEC_ONLY_SRCS
    ${SOURCE_DIR}/main.cpp
)

set(INCLUDES
    ${INCLUDE_DIR}/TabuSearch.hpp
    ${INCLUDE_DIR}/Parser.hpp
)

set(INTERFACES
)

set(TARGET_LIBRARY_NAME ${PROJECT_NAME}-lib)

add_library(${TARGET_LIBRARY_NAME} ${SOURCES} ${INCLUDES} ${INTERFACES})
target_include_directories(${TARGET_LIBRARY_NAME} PUBLIC ${INCLUDE_DIR} ${INTERFACE_DIR})
target_link_libraries(${TARGET_LIBRARY_NAME} PUBLIC ${BOOST_LIBRARIES})
set_target_properties(${TARGET_LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_executable(${PROJECT_NAME} ${EXEC_ONLY_SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${TARGET_LIBRARY_NAME})