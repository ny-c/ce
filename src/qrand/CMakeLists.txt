SET(qrand_src src/QRBG.cpp src/CmdLineParser.cpp src/main.cpp)

ADD_EXECUTABLE(qrand ${qrand_src})

add_custom_command(TARGET qrand POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/src/qrand/qrand"
		"${CMAKE_SOURCE_DIR}/bin/qrand")

add_custom_command(TARGET qrand POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/src/qrand/qrand.exe"
		"${CMAKE_SOURCE_DIR}/bin/qrand.exe")