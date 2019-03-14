#ifndef CLASSFILEPARSER_VM
#define CLASSFILEPARSER_VM

#include <istream>
#include <optional>

#include <data_utils.hpp>
#include "JavaClass.hpp"

class ClassFileParser {
	JavaClass javaClass;
	bool valid = false;

	bool checkMagicValue(std::istream& in) const;
	bool checkClassVersion(std::istream& in) const;
	ConstantPool::Pool parseConstantPool(std::istream& in);
	ConstantPool::Entry parseConstantPoolEntry(std::istream& in);
public:
	ClassFileParser(std::istream& in);
	std::optional<JavaClass> getClass() const;
};

#endif
