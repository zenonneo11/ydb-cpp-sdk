add_library(library-cpp-cache)

target_link_libraries(library-cpp-cache PUBLIC
  yutil
)

target_sources(library-cpp-cache PRIVATE
  ${YDB_SDK_SOURCE_DIR}/src/library/cache/cache.cpp
  ${YDB_SDK_SOURCE_DIR}/src/library/cache/thread_safe_cache.cpp
)
