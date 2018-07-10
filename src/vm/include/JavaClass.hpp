#ifndef JAVACLASS_VM
#define JAVACLASS_VM

#include <istream>
#include <vector>
#include <variant>

using ConstantPoolEntry = std::variant<int, std::string>;
using ConstantPool = std::vector<ConstantPoolEntry>;

class JavaClass {
	ConstantPool constantPool;
public:
	JavaClass(std::istream& in);
	const ConstantPool& getConstantPool() const;

};

#endif
