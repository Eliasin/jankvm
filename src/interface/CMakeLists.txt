project(interfacelib VERSION 0.1 LANGUAGES CXX)

add_library(interface
	src/ClassFileVerifier.cpp)

target_include_directories(interface PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
	$<INSTALL_INTERFACE:include/>)

target_compile_features(interface
	PUBLIC cxx_static_assert)

target_link_libraries(interface
	PUBLIC utils)
