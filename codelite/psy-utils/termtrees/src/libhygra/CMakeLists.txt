add_library(hygra dihy.c hygra.h)
add_executable(../../hygra-test test.c)

target_link_libraries(../../hygra-test bstrlib hygra cprops)
