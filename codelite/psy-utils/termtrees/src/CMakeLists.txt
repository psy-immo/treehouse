add_subdirectory(bstrlib)
add_executable(../termtrees main.c op_signature.c cli.c terms.c termtrees.c)
target_link_libraries(../termtrees bstrlib confuse cprops)

add_executable(../termtrees-test test.c op_signature.c cli.c terms.c termtrees.c)

target_link_libraries(../termtrees-test bstrlib confuse cprops)