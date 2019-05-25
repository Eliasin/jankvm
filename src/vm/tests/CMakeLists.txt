add_executable(vmlibtests main.cpp parserTests.cpp)

target_include_directories(vmlibtests PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(vmlibtests vm)
