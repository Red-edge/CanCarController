PROJECT(main)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.2)
AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(test ${DIR_SRCS})
