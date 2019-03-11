project(vmlib VERSION 0.1 LANGUAGES CXX)

add_library(vm
	src/JavaClass.cpp
	src/ClassFileParser.cpp
	src/Interpreter.cpp)

target_include_directories(vm PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
	$<INSTALL_INTERFACE:include/>)

target_compile_features(vm
	PUBLIC cxx_std_17)

target_link_libraries(vm
	PUBLIC utils)

add_subdirectory(tests)
