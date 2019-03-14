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

	ConstantPool::Pool constantPool = parseConstantPool(in);
	javaClass = JavaClass(constantPool);
}

std::optional<JavaClass> ClassFileParser::getClass() const {
	if (valid)
		return javaClass;
	return {};
}

bool ClassFileParser::checkMagicValue(std::istream& in) const {
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

bool ClassFileParser::checkClassVersion(std::istream& in) const {
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

ConstantPool::Pool ClassFileParser::parseConstantPool(std::istream& in) {
	using namespace ConstantPool;
	Pool constantPool;
	char numEntriesBuffer[2];

	if (!tryRead(in, numEntriesBuffer, 2))
		valid = false;
	return {};

	ConstantPool::Pool::size_type numEntries = bytesToType<uint16_t, 2>(numEntriesBuffer);
	for (ConstantPool::Pool::size_type entryNumber = 0; entryNumber < numEntries; entryNumber++) {
		constantPool.push_back(parseConstantPoolEntry(in));
	}

	return constantPool;
}

ConstantPool::Entry ClassFileParser::parseConstantPoolEntry(std::istream& in) {
	using namespace ConstantPool;
	char tagBuffer[1];
	if (!tryRead(in, tagBuffer, 1))
		valid = false;
	return {};
	unsigned char tag = bytesToType<unsigned char, 1>(tagBuffer);
	
	switch(tag) {
		case CONSTANT_Class:
			{
				char buf[2];
				if (!tryRead(in, buf, 2)) {
					valid = false;
					return {};
				}

				Index index = bytesToType<Index, 2>(buf);
				return {ClassInfo{index}};
				break;
			}
		case CONSTANT_Fieldref:	
		case CONSTANT_Methodref:	
		case CONSTANT_InterfaceMethodref:
			{
				char classIndexBuf[2];
				char nameAndTypeIndexBuf[2];
				if (!tryRead(in, classIndexBuf, 2) || !tryRead(in, nameAndTypeIndexBuf, 2)) {
					valid = false;
					return {};
				}

				Index classIndex = bytesToType<Index, 2>(classIndexBuf);
				Index nameAndTypeIndex = bytesToType<Index, 2>(nameAndTypeIndexBuf);
				return {Reference{static_cast<Tag>(tag), classIndex, nameAndTypeIndex}};
				break;
			}
		case CONSTANT_String:
			{
				break;
			}
		case CONSTANT_Integer:
			{
				char buf[4];
				if (!tryRead(in, buf, 4)) {
					valid = false;
					return {};
				}

				uint32_t data = bytesToType<uint32_t, 4>(buf);
				return {data};
				break;
			}
		case CONSTANT_Float:
			{
				char buf[4];
				if (!tryRead(in, buf, 4)) {
					valid = false;
					return {};
				}

				float data = bytesToType<float, 4>(buf);
				return {data};
				break;
			}
		case CONSTANT_Long:
			{
				break;
			}
		case CONSTANT_Double:
			{
				break;
			}
		case CONSTANT_NameAndType:
			{
				break;
			}
		case CONSTANT_Utf8:
			{
				char lenBuf[2];
				if (!tryRead(in, lenBuf, 2)) {
					valid = false;
					return {};
				}

				uint16_t len = bytesToType<uint16_t, 2>(lenBuf);

				char strBuf[len];
				if (!tryRead(in, strBuf, len)) {
					valid = false;
					return {};
				}

				return {std::string{strBuf}};
				break;
			}
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

