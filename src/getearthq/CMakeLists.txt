SET(getearthq_src main.cpp network.cpp)

ADD_EXECUTABLE(getearthq ${getearthq_src})

TARGET_LINK_LIBRARIES(getearthq boost_program_options boost_system)

add_custom_command(TARGET getearthq POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/src/getearthq/getearthq"
		"${CMAKE_SOURCE_DIR}/bin/getearthq")

add_custom_command(TARGET getearthq POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/src/getearthq/getearthq.exe"
		"${CMAKE_SOURCE_DIR}/bin/getearthq.exe")