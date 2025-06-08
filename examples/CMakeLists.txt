
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
add_executable(quad
  ${CMAKE_CURRENT_SOURCE_DIR}/quad.c
)

target_link_libraries(quad PRIVATE
  Radiant::Radiant
)
