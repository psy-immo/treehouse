add_library(hygra hygra.h dihy.c patf.c bundles.c math.c)
add_executable(../../hygra-test test.c)

target_link_libraries(../../hygra-test bstrlib hygra cprops)
