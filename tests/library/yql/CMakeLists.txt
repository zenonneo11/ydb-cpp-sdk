add_ydb_test(NAME library-yql-utils-ut
  SOURCES
  utf8_ut.cpp
  LINK_LIBRARIES
  yutil
  cpp-testing-unittest_main
  library-yql-utils
)

add_ydb_test(NAME yql-public-issue-ut
  SOURCES
  yql_issue_ut.cpp
  LINK_LIBRARIES
  yutil
  cpp-testing-unittest_main
  yql-public-issue
  cpp-unicode_normalization
)

add_ydb_test(NAME yql-public-decimal_ut
  SOURCES
  yql_decimal_ut.cpp
  LINK_LIBRARIES
  yutil
  cpp-testing-unittest_main
  yql-public-decimal
)

add_ydb_test(NAME yql-public-wide_int_ut
  SOURCES
  yql_wide_int_ut.cpp
  LINK_LIBRARIES
  yutil
  cpp-testing-unittest_main
  yql-public-decimal
)
