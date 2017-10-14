cmake_minimum_required(VERSION 3.0)

project(pea_zadanie1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

enable_testing()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

add_subdirectory(googletest)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INTERFACE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/interface)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(SOURCES
        ${SOURCE_DIR}/TravellingSalesmanBruteForce.cpp
)

set(EXEC_ONLY_SRCS
        ${SOURCE_DIR}/main.cpp
)

set(INCLUDES
        ${INCLUDE_DIR}/TravellingSalesmanBruteForce.h
)

set(INTERFACES
        ${INTERFACE_DIR}/TravellingSalesman.h
)

set(TESTS
        ${TEST_DIR}/TravellingSalesmanBruteForceTestSuite.cpp
)

set(TARGET_LIBRARY_NAME ${PROJECT_NAME}-lib)

add_library(${TARGET_LIBRARY_NAME} ${SOURCES} ${INCLUDES} ${INTERFACES})
target_include_directories(${TARGET_LIBRARY_NAME} PUBLIC ${INCLUDE_DIR} ${INTERFACE_DIR})
target_link_libraries(${TARGET_LIBRARY_NAME} PUBLIC ${BOOST_LIBRARIES})

add_executable(${PROJECT_NAME} ${EXEC_ONLY_SRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${TARGET_LIBRARY_NAME})

set(TEST_NAME ${PROJECT_NAME}-unittests)

add_executable(${TEST_NAME} ${TESTS})
target_include_directories(${TEST_NAME} PRIVATE ${TEST_DIR})
target_link_libraries(${TEST_NAME} PRIVATE
        ${TARGET_LIBRARY_NAME}
        gtest
        gtest_main
        gmock
        gmock_main
        ${Boost_LIBRARIES}
)

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
add_dependencies(check ${TEST_NAME})