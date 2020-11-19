cmake_minimum_required(VERSION 3.16)

project(fx_converter)

set(CMAKE_BUILD_TYPE Debug)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories (/home/stephen/projects/back-to-cpp/sr/fx_converter/include)

file(GLOB SOURCES "/home/stephen/projects/back-to-cpp/sr/fx_converter/test/exchangeTests.cpp")

add_executable(exchangeTests.exe ${SOURCES})

target_link_libraries(exchangeTests.exe ${Boost_FILESYSTEM_LIBRARY}
                               ${Boost_SYSTEM_LIBRARY}
                               ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})