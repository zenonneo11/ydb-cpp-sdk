add_library(cpp-json-writer)

target_link_libraries(cpp-json-writer PUBLIC
  
  yutil
  cpp-json-common
  tools-enum_parser-enum_serialization_runtime
  cpp-string_utils-misc
)

target_sources(cpp-json-writer PRIVATE
  ${YDB_SDK_SOURCE_DIR}/src/library/json/writer/json_value.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/json/writer/json.cpp
)

generate_enum_serilization(cpp-json-writer
  ${YDB_SDK_SOURCE_DIR}/include/ydb-cpp-sdk/library/json/writer/json_value.h
  INCLUDE_HEADERS
  include/ydb-cpp-sdk/library/json/writer/json_value.h
)


