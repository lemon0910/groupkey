PROJECT(GROUPKEY)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
set(CMAKE_C_COMPILER "g++")
cmake_policy(SET CMP0015 OLD)

set(SRC_PATH "/home/lin/GroupKey")
set(base_SRCS
${SRC_PATH}/src/BitCompressedVector.cc
${SRC_PATH}/src/Logging.cc
${SRC_PATH}/src/LogStream.cc
${SRC_PATH}/src/Timestamp.cc
)

include_directories(${SRC_PATH}/include ../gtest-1.7.0/include)
link_directories(/home/lin/DC/common/lib /home/lin/gtest-1.7.0)

ADD_SUBDIRECTORY(test)