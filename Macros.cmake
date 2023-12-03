macro(catch_add_test TESTNAME)
  add_executable(${TESTNAME} ${ARGN})
  target_link_libraries(${TESTNAME} PRIVATE Catch2::Catch2WithMain)
endmacro()
