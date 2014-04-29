PROJECT(shdt C)

SET(swe_src src/swedate.c src/swehouse.c src/swejpl.c src/swemmoon.c src/swemplan.c src/swepcalc.c src/sweph.c	src/swepdate.c src/swephlib.c src/swecl.c src/swehel.c)
ADD_LIBRARY(swe STATIC ${swe_src})

set(TEMP "-O3 -Wall -Wno-char-subscripts -Wno-unused-but-set-variable -Wno-maybe-uninitialized")
set_target_properties(swe PROPERTIES COMPILE_FLAGS ${TEMP})



