add_library(argonish-internal-blake2b INTERFACE)

target_link_libraries(argonish-internal-blake2b INTERFACE
  yutil
  argonish-internal-rotations
)
