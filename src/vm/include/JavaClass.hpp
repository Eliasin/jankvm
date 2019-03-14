#ifndef JAVACLASS_VM
#define JAVACLASS_VM

#include <istream>
#include <vector>
#include <variant>

class JavaClassBuilder;

namespace ConstantPool {
	using Index = uint16_t;

	enum Tag {
		CONSTANT_Class = 7,
		CONSTANT_Fieldref = 9,
		CONSTANT_Methodref = 10,
		CONSTANT_InterfaceMethodref = 11,
		CONSTANT_String = 8,
		CONSTANT_Integer = 3,
		CONSTANT_Float = 4,
		CONSTANT_Long = 5,
		CONSTANT_Double = 6,
		CONSTANT_NameAndType = 12,
		CONSTANT_Utf8 = 1,
		CONSTANT_MethodHandle = 15,
		CONSTANT_MethodType = 16,
		CONSTANT_InvokeDynamic = 18
	};

	struct Reference {
		Tag tag;
		Index classIndex;
		Index nameAndTypeIndex;
	};

	struct ClassInfo {
		Index nameIndex;
	};

	using Entry = std::variant<uint32_t, float, std::string, ClassInfo, Reference>;

	using Pool = std::vector<Entry>;
}

class JavaClass {
	ConstantPool::Pool constantPool;
public:
	JavaClass(const ConstantPool::Pool& constantPool);
	JavaClass(ConstantPool::Pool&& constantPool);
	const ConstantPool::Pool& getConstantPool() const;

};

#endif
