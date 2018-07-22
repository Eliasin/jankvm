#include "ClassFileParser.hpp"

ClassFileParser::ClassFileParser(std::istream& in) : javaClass({}) {
	if (!in) {
		valid = false;
		return;
	}

	if (!checkMagicValue(in) || !checkClassVersion(in)) {
		valid = false;
		return;
	}

	ConstantPool constantPool = parseConstantPool(in);
	javaClass = JavaClass(constantPool);
}

std::optional<JavaClass> ClassFileParser::getClass() const {
	if (valid)
		return javaClass;
	return {};
}

bool ClassFileParser::checkMagicValue(std::istream& in) {
	constexpr uint32_t magic = 0xCAFEBABE;
	char buffer[4];
	if (!tryRead(in, buffer, 4)) {
		return false;
	}
	else if (bytesToType<uint32_t, 4>(buffer) == magic) {
		return true;
	}
	else {
		std::cerr << "Error: Invalid file format " << std::endl;
		return false;
	}

}


bool ClassFileParser::checkClassVersion(std::istream& in) {
	constexpr unsigned int minimumSupportedMajorVersion = 52;
	char minorVersion[2];
	char majorVersion[2];

	bool minorVersionReadSuccess = tryRead(in, minorVersion, 2);
	bool majorVersionReadSuccess = tryRead(in, majorVersion, 2);
	bool versionReadSuccess = minorVersionReadSuccess && majorVersionReadSuccess;
	if (versionReadSuccess && bytesToType<uint16_t, 2>(majorVersion) <= minimumSupportedMajorVersion) {
		return true;
	}
	std::cerr << "Error: Class file version not supported" << std::endl;
	return false;
}

ConstantPool ClassFileParser::parseConstantPool(std::istream& in) {
	ConstantPool constantPool;
	char numEntriesBuffer[2];

	if (!tryRead(in, numEntriesBuffer, 2))
		valid = false;
	return {};

	ConstantPool::size_type numEntries = bytesToType<uint16_t, 2>(numEntriesBuffer);
	for (ConstantPool::size_type entryNumber = 0; entryNumber < numEntries; entryNumber++) {
		constantPool.push_back(parseConstantPoolEntry(in));
	}

	return constantPool;
}

ConstantPoolEntry ClassFileParser::parseConstantPoolEntry(std::istream& in) {
	char tagBuffer[1];
	if (!tryRead(in, tagBuffer, 1))
		valid = false;
	return {};
	unsigned char tag = bytesToType<unsigned char, 1>(tagBuffer);

	enum ConstantPoolTags {
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

	switch(tag) {
		case CONSTANT_Class:
			break;
		case CONSTANT_Fieldref:
			break;
		case CONSTANT_Methodref:
			break;
		case CONSTANT_InterfaceMethodref:
			break;
		case CONSTANT_String:
			break;
		case CONSTANT_Integer:
			break;
		case CONSTANT_Float:
			break;
		case CONSTANT_Long:
			break;
		case CONSTANT_Double:
			break;
		case CONSTANT_NameAndType:
			break;
		case CONSTANT_Utf8:
			break;
		case CONSTANT_MethodHandle:
			break;
		case CONSTANT_MethodType:
			break;
		case CONSTANT_InvokeDynamic:
			break;
		default:
			valid = false;
			std::cerr << "Error: Unkown/Invalid constant pool entry tag" << std::endl;
			break;
	}

	return {};
}

