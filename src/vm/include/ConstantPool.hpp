#ifndef CONSTANT_POOL_VM
#define CONSTANT_POOL_VM

#include <vector>
#include <variant>

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

	struct ReferenceInfo {
		Tag tag;
		Index classIndex;
		Index nameAndTypeIndex;
	};

	struct ClassInfo {
		Index nameIndex;
	};

	struct StringInfo {
		Index stringIndex;
	};

	struct NameAndTypeInfo {
		Index nameIndex;
		Index descIndex;
	};

	using ReferenceKind = uint8_t;

	struct MethodHandleInfo {
		ReferenceKind refKind;
		Index refIndex;
	};

	struct MethodTypeInfo {
		Index descIndex;
	};

	struct InvokeDynamicInfo {
		Index bootstrapMethodAttrIndex;
		Index nameAndTypeIndex;
	};

	using Entry = std::variant<uint32_t, uint64_t, float, double, std::string, ClassInfo,
		 					   ReferenceInfo, StringInfo, NameAndTypeInfo, MethodHandleInfo, 
							   MethodTypeInfo, InvokeDynamicInfo>;

	using Pool = std::vector<Entry>;
}
#endif
