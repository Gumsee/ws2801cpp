#
# Source
#
file(GLOB_RECURSE SRC "./*.cpp")
add_library(${PROJECT_NAME} STATIC ${SRC})

file(GLOB HEADERS *.h)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}/)
install(FILES ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
