add_library(monlib-encode-json)

target_link_libraries(monlib-encode-json PUBLIC
  yutil
  cpp-monlib-encode
  monlib-encode-buffered
  cpp-monlib-exception
  library-cpp-json
  cpp-json-writer
)

target_sources(monlib-encode-json PRIVATE
  ${YDB_SDK_SOURCE_DIR}/src/library/monlib/encode/json/json_decoder.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/monlib/encode/json/json_encoder.cpp
)


