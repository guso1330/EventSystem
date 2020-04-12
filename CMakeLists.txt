# Project definition
cmake_minimum_required(VERSION 3.9.1)
project(EventSystem)

# Project definition
cmake_minimum_required(VERSION 3.12.0)
project(EventSystemLib VERSION 0.0.1 DESCRIPTION "Simple C++ event system library")

# Source Files
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/tests")
set(SRC_FILES
	"${SRC_DIR}/EventManager.cpp"
)

# library
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_include_directories(${PROJECT_NAME} PRIVATE "${INCLUDE_DIR}")

MESSAGE(STATUS "===============================================")
MESSAGE(STATUS "=          EventSystem CMake Building         =")
MESSAGE(STATUS "===============================================")
MESSAGE(STATUS "Header Directory: " ${INCLUDE_DIR})
MESSAGE(STATUS "Source files[directory: " ${SRC_DIR} "]: ")
foreach(src_file ${SRC_FILES})
	MESSAGE(STATUS "SOURCE FILE: " ${src_file})
endforeach(src_file)

# Tests
MESSAGE(STATUS "===============================================")
MESSAGE(STATUS "=             Tests CMake Buidling            =")
MESSAGE(STATUS "===============================================")
option(EVENT_SYSTEM_BUILD_TESTS "Build event system tests" ON)
if(EVENT_SYSTEM_BUILD_TESTS)
	add_subdirectory(tests)
endif()

# Main Executable
MESSAGE(STATUS "===============================================")
MESSAGE(STATUS "=              Main CMake Buidling            =")
MESSAGE(STATUS "===============================================")
option(EVENT_SYSTEM_BUILD_MAIN "Build event system main file" ON)
if(EVENT_SYSTEM_BUILD_MAIN)
	set(MAIN_BINARY EventSystemMain)
	add_executable(${MAIN_BINARY} "${PROJECT_SOURCE_DIR}/main.cpp")
	set_property(TARGET ${MAIN_BINARY} PROPERTY CXX_STANDARD 11)
	target_link_libraries(${MAIN_BINARY} ${PROJECT_NAME})
	target_include_directories(${MAIN_BINARY} PRIVATE "${INCLUDE_DIR}")
endif()
