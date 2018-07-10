#ifndef JAVACLASS_VM
#define JAVACLASS_VM

#include <istream>
#include <vector>
#include <variant>

class JavaClassBuilder;

using ConstantPoolEntry = std::variant<int, std::string>;
using ConstantPool = std::vector<ConstantPoolEntry>;

class JavaClass {
	ConstantPool constantPool;

	friend JavaClassBuilder;
	JavaClass(ConstantPool constantPool);
public:
	const ConstantPool& getConstantPool() const;

};

#endif
