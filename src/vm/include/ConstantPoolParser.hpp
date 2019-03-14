#ifndef CONSTANT_POOL_PARSER_VM
#define CONSTANT_POOL_PARSER_VM

#include <istream>
#include <optional>

#include "ConstantPool.hpp"

class ConstantPoolParser {
	bool valid = true;
	ConstantPool::Entry parseEntry(std::istream& in);
public:
	std::optional<ConstantPool::Pool> parseConstantPool(std::istream& in);
};

#endif
