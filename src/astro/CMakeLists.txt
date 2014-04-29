PROJECT(astro CXX)

SET(astro_lib_src astro.cpp datetime.cpp hd_structs.cpp humandesign.cpp rave.cpp swe_types.cpp swe_wrapper.cpp utilities.cpp)

ADD_LIBRARY(astro STATIC ${astro_lib_src})

TARGET_LINK_LIBRARIES(astro swe)