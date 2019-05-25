#include "catch.hpp"

#include "ConstantPoolParser.hpp"

#include <fstream>

TEST_CASE("constant pool parsing", "[constant pool]") {
	ConstantPoolParser parser;

	std::ifstream f{"constantPool"};
	REQUIRE(f);

	auto constantPool = parser.parseConstantPool(f);
	REQUIRE(constantPool);

	REQUIRE(std::get<int32_t>(constantPool->at(0)) == 2);
	REQUIRE(std::get<float>(constantPool->at(1)) - 16.f < 0.001);
	REQUIRE(std::get<int64_t>(constantPool->at(2)) == 42949672970);	
}
