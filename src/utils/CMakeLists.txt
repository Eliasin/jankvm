project(utilslib VERSION 0.1 LANGUAGES CXX)

add_library(utils
	INTERFACE)

target_compile_features(utils
	INTERFACE cxx_static_assert)

set(header_files
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/data_utils.hpp>)

target_sources(utils INTERFACE $<BUILD_INTERFACE:${header_files}>)

target_include_directories(utils INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
	$<INSTALL_INTERFACE:include/>)

target_link_libraries(utils
	INTERFACE boost)

