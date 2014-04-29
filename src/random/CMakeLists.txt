SET(random_lib_src randomgen.cpp tester.cpp)

ADD_LIBRARY(random STATIC ${random_lib_src})

TARGET_LINK_LIBRARIES(random astro)