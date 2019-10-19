cmake_minimum_required (VERSION 3.5)
project(EngineSavage)

add_compile_options(-std=c++11)
include_directories(
	headers
)
aux_source_directory(
	sources DIR_SRCS
)
add_executable (${PROJECT_NAME} ${DIR_SRCS})

