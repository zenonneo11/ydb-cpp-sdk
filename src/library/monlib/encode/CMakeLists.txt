add_subdirectory(buffered)
add_subdirectory(json)
add_subdirectory(legacy_protobuf)
add_subdirectory(prometheus)
add_subdirectory(spack)
add_subdirectory(text)

add_library(cpp-monlib-encode)
target_link_libraries(cpp-monlib-encode PUBLIC
  yutil
  cpp-monlib-metrics
  tools-enum_parser-enum_serialization_runtime
  cpp-string_utils-misc
)
target_sources(cpp-monlib-encode PRIVATE
  ${YDB_SDK_SOURCE_DIR}/src/library/monlib/encode/encoder.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/monlib/encode/encoder_state.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/monlib/encode/format.cpp
)
generate_enum_serilization(cpp-monlib-encode
  ${YDB_SDK_SOURCE_DIR}/src/library/monlib/encode/encoder_state_enum.h
  GEN_HEADER
  ${YDB_SDK_BINARY_DIR}/src/library/monlib/encode/encoder_state_enum.h_serialized.h
  INCLUDE_HEADERS
  src/library/monlib/encode/encoder_state_enum.h
)


