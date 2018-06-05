add_executable(jankvm
	src/main.cpp)

target_compile_features(jankvm
	PUBLIC cxx_static_assert)
target_include_directories(jankvm PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(jankvm
	boost)
