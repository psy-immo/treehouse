add_subdirectory(bstrlib)
add_executable(../termtrees main.c)
target_link_libraries(../termtrees bstrlib confuse cprops)