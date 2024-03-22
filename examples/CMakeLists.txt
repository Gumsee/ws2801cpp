message(STATUS "Examples: CXXFLAGS: ${CMAKE_CXX_FLAGS}")

list(APPEND LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
list(APPEND LIBRARIES ${PROJECT_NAME}) 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)

link_directories(${CMAKE_BINARY_DIR}/src/)

add_executable(led_test "./led_test.cpp")
target_link_libraries(led_test "${LIBRARIES}")
