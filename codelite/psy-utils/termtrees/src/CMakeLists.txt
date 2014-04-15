add_subdirectory(bstrlib)
add_subdirectory(libhygra)
add_executable(../termtrees main.c op_signature.c cli.c terms.c termtrees.c termtrees.h)
target_link_libraries(../termtrees bstrlib confuse cprops hygra)

add_executable(../termtrees-test test.c op_signature.c cli.c terms.c termtrees.c termtrees.h)

target_link_libraries(../termtrees-test bstrlib confuse cprops hygra)