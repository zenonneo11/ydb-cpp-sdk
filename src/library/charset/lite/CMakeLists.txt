add_library(cpp-charset-lite)

target_link_libraries(cpp-charset-lite PUBLIC
  cpp-string_utils-misc
  yutil
)

target_sources(cpp-charset-lite PRIVATE
  ${YDB_SDK_SOURCE_DIR}/src/library/charset/generated/cp_data.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/charset/generated/encrec_data.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/charset/codepage.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/charset/cp_encrec.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/charset/doccodes.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/charset/ci_string.cpp
)
