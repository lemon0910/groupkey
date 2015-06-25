add_definitions(-g -Wall -std=c++0x )
AUX_SOURCE_DIRECTORY(. test_srcs)
add_executable(main ${test_srcs} ${base_SRCS})
target_link_libraries(main libgtest.a pthread)
