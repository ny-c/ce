SET(check_dice_src main.cpp main_test.cpp)

ADD_EXECUTABLE(check_dice ${check_dice_src})

TARGET_LINK_LIBRARIES(check_dice random boost_program_options boost_system)

add_custom_command(TARGET check_dice POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/src/check_dice/check_dice"
		"${CMAKE_SOURCE_DIR}/bin/check_dice")

add_custom_command(TARGET check_dice POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/src/check_dice/check_dice.exe"
		"${CMAKE_SOURCE_DIR}/bin/check_dice.exe")