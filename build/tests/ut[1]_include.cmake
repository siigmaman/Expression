if(EXISTS "/home/vboxuser/Documents/expression/Expression/build/tests/ut")
  if(NOT EXISTS "/home/vboxuser/Documents/expression/Expression/build/tests/ut[1]_tests.cmake" OR
     NOT "/home/vboxuser/Documents/expression/Expression/build/tests/ut[1]_tests.cmake" IS_NEWER_THAN "/home/vboxuser/Documents/expression/Expression/build/tests/ut" OR
     NOT "/home/vboxuser/Documents/expression/Expression/build/tests/ut[1]_tests.cmake" IS_NEWER_THAN "${CMAKE_CURRENT_LIST_FILE}")
    include("/usr/share/cmake-3.28/Modules/GoogleTestAddTests.cmake")
    gtest_discover_tests_impl(
      TEST_EXECUTABLE [==[/home/vboxuser/Documents/expression/Expression/build/tests/ut]==]
      TEST_EXECUTOR [==[]==]
      TEST_WORKING_DIR [==[/home/vboxuser/Documents/expression/Expression/build/tests]==]
      TEST_EXTRA_ARGS [==[]==]
      TEST_PROPERTIES [==[]==]
      TEST_PREFIX [==[]==]
      TEST_SUFFIX [==[]==]
      TEST_FILTER [==[]==]
      NO_PRETTY_TYPES [==[FALSE]==]
      NO_PRETTY_VALUES [==[FALSE]==]
      TEST_LIST [==[ut_TESTS]==]
      CTEST_FILE [==[/home/vboxuser/Documents/expression/Expression/build/tests/ut[1]_tests.cmake]==]
      TEST_DISCOVERY_TIMEOUT [==[5]==]
      TEST_XML_OUTPUT_DIR [==[]==]
    )
  endif()
  include("/home/vboxuser/Documents/expression/Expression/build/tests/ut[1]_tests.cmake")
else()
  add_test(ut_NOT_BUILT ut_NOT_BUILT)
endif()
