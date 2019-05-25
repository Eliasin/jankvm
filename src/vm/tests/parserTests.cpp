#include "catch.hpp"

#include "ConstantPoolParser.hpp"

#include <fstream>

TEST_CASE("constant pool parsing", "[constant pool]") {
	ConstantPoolParser parser;

	std::ifstream f{"constantPool"};
	REQUIRE(f);

	auto constantPool = parser.parseConstantPool(f);
	REQUIRE(constantPool);

	REQUIRE(std::get<uint32_t>(constantPool->at(0)) == 2);
}
