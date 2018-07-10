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
public:
	JavaClass(ConstantPool constantPool);
	const ConstantPool& getConstantPool() const;

};

#endif
