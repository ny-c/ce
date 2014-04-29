SET(check_earthq_src main.cpp main_test.cpp)

ADD_EXECUTABLE(check_earthq ${check_earthq_src})

TARGET_LINK_LIBRARIES(check_earthq astro lists random boost_program_options boost_system)

add_custom_command(TARGET check_earthq POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/src/check_earthq/check_earthq"
		"${CMAKE_SOURCE_DIR}/bin/check_earthq")

add_custom_command(TARGET check_earthq POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/src/check_earthq/check_earthq.exe"
		"${CMAKE_SOURCE_DIR}/bin/check_earthq.exe")