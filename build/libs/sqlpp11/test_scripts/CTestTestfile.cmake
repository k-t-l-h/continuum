# CMake generated Testfile for 
# Source directory: /home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts
# Build directory: /home/evgeny/CI-SERVER/build/libs/sqlpp11/test_scripts
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(sqlpp11.test.ddl2cpp.bad_will_fail "/usr/bin/python3.7" "/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/../scripts/ddl2cpp" "-fail-on-parse" "/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/ddl2cpp_sample_bad.sql" "/home/evgeny/CI-SERVER/build/libs/sqlpp11/test_scripts/fail" "test")
set_tests_properties(sqlpp11.test.ddl2cpp.bad_will_fail PROPERTIES  WILL_FAIL "1" _BACKTRACE_TRIPLES "/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/CMakeLists.txt;41;add_test;/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/CMakeLists.txt;0;")
add_test(sqlpp11.test.ddl2cpp.bad_has_parse_error "/usr/bin/python3.7" "/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/../scripts/ddl2cpp" "-fail-on-parse" "/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/ddl2cpp_sample_bad.sql" "/home/evgeny/CI-SERVER/build/libs/sqlpp11/test_scripts/fail" "test")
set_tests_properties(sqlpp11.test.ddl2cpp.bad_has_parse_error PROPERTIES  PASS_REGULAR_EXPRESSION "Parsing error,.*" _BACKTRACE_TRIPLES "/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/CMakeLists.txt;48;add_test;/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/CMakeLists.txt;0;")
add_test(sqlpp11.test.ddl2cpp.good_succeeds "/usr/bin/python3.7" "/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/../scripts/ddl2cpp" "-fail-on-parse" "/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/ddl2cpp_sample_good.sql" "/home/evgeny/CI-SERVER/build/libs/sqlpp11/test_scripts/fail" "test")
set_tests_properties(sqlpp11.test.ddl2cpp.good_succeeds PROPERTIES  _BACKTRACE_TRIPLES "/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/CMakeLists.txt;55;add_test;/home/evgeny/CI-SERVER/libs/sqlpp11/test_scripts/CMakeLists.txt;0;")
