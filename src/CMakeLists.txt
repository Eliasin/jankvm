cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(jankvm VERSION 0.1 LANGUAGES CXX)


include(GNUInstallDirs)

find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
	INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

enable_testing()
add_subdirectory(jankvm)
add_subdirectory(utils)
