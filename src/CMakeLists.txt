FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

include_directories(../../cub/include ../../event/include)

add_library(trans-dsl STATIC ${all_files} ../include/trans-dsl/sched/concept/Unknow.h)

install(TARGETS trans-dsl ARCHIVE DESTINATION lib)

