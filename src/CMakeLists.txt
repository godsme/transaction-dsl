FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

include_directories(../../cub/include ../../event/include)

add_library(trans-dsl STATIC ${all_files})

install(TARGETS trans-dsl ARCHIVE DESTINATION lib)

