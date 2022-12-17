# CMake generated Testfile for 
# Source directory: /home/yabiel/Desktop/IS/eq102/tests
# Build directory: /home/yabiel/Desktop/IS/eq102/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(tests_gtests "tests")
set_tests_properties(tests_gtests PROPERTIES  _BACKTRACE_TRIPLES "/home/yabiel/Desktop/IS/eq102/tests/CMakeLists.txt;18;add_test;/home/yabiel/Desktop/IS/eq102/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
