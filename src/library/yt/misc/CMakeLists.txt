add_library(cpp-yt-misc)

target_compile_options(cpp-yt-misc PRIVATE
  -Wdeprecated-this-capture
)

target_link_libraries(cpp-yt-misc PUBLIC
  yutil
  cpp-yt-exception
  tools-enum_parser-enum_serialization_runtime
  cpp-string_utils-misc
)

target_sources(cpp-yt-misc PRIVATE
  ${YDB_SDK_SOURCE_DIR}/src/library/yt/misc/guid.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/yt/misc/source_location.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/yt/misc/thread_name.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/yt/misc/variant.cpp
)


