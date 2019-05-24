#include "ConstantPoolParser.hpp"

#include <data_utils.hpp>

std::optional<ConstantPool::Pool> ConstantPoolParser::parseConstantPool(std::istream& in) {
	using namespace ConstantPool;
	Pool constantPool;
	char numEntriesBuffer[2];

	if (!tryRead(in, numEntriesBuffer, 2))
		valid = false;
	return {};

	ConstantPool::Pool::size_type numEntries = bytesToType<uint16_t, 2>(numEntriesBuffer);
	for (ConstantPool::Pool::size_type entryNumber = 0; entryNumber < numEntries; entryNumber++) {
		constantPool.push_back(parseEntry(in));
	}

	return valid ? Pool{constantPool} : Pool{};
}

ConstantPool::Entry ConstantPoolParser::parseEntry(std::istream& in) {
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
				return {ReferenceInfo{static_cast<Tag>(tag), classIndex, nameAndTypeIndex}};
				break;
			}
		case CONSTANT_String:
			{
				char buf[2];
				if (!tryRead(in, buf, 2)) {
					valid = false;
					return {};
				}

				Index stringIndex = bytesToType<Index, 2>(buf);
				return {StringInfo{stringIndex}};
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
				char buf[8];

				if (!tryRead(in, buf, 8)) {
					valid = false;
					return {};
				}
				
				uint64_t data = bytesToType<uint64_t, 8>(buf);
				return {data};
				break;
			}
		case CONSTANT_Double:
			{
				char buf[8];

				if (!tryRead(in, buf, 8)) {
					valid = false;
					return {};
				}

				double data = bytesToType<double, 8>(buf);
			   	return {data};	
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

