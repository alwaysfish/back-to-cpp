cmake_minimum_required(VERSION 3.16)

project(fx_converter)

set(CMAKE_BUILD_TYPE Debug)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories (../include)

file(GLOB SOURCES "../src/currencyList.cpp"
                "../src/exchangeBoard.cpp"
                "../test/exchangeTests.cpp")

add_executable(exchangeTests ${SOURCES})

target_link_libraries(exchangeTests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})